# ==============================================================================
# Makefile — Projet TowerDefend
# Objectif   : Compiler un projet C avec SDL2
# Outil      : gcc + pkg-config pour détecter automatiquement les flags SDL2
# ==============================================================================

# --- Compilateur & standard ---
CC      := gcc
CFLAGS  := -Wall -Wextra -g -std=c99

# --- Binaire de sortie ---
TARGET  := tower_defend

# --- Sources & objets ---
SRCS    := $(wildcard *.c)
OBJS    := $(SRCS:.c=.o)          

# --- Flags SDL2 via pkg-config ---

SDL_LIBS := sdl2 SDL2_image SDL2_ttf SDL2_mixer

CFLAGS  += $(shell pkg-config --cflags $(SDL_LIBS))
LDFLAGS := $(shell pkg-config --libs   $(SDL_LIBS))

# ==============================================================================
# Règles
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
