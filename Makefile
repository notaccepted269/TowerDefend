# ==============================================================================
# Makefile — Projet TowerDefend
# Compatible Linux (pkg-config) et Windows (MinGW/MSYS2)
# ==============================================================================

CC     := gcc
CFLAGS := -Wall -Wextra -g -std=c99
TARGET := tower_defend

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

SDL_LIBS := sdl2 SDL2_image SDL2_ttf SDL2_mixer

# --- Détection OS ---
ifeq ($(OS), Windows_NT)
    CFLAGS  += -IC:/msys64/mingw64/include/SDL2
    LDFLAGS := -LC:/msys64/mingw64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    TARGET  := tower_defend.exe
else
    CFLAGS  += $(shell pkg-config --cflags $(SDL_LIBS))
    LDFLAGS := $(shell pkg-config --libs $(SDL_LIBS))
endif

# ==============================================================================
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all run clean fclean re
