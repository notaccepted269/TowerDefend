# 🏰 TowerDefend

> Jeu de Tower Defense développé en **C** avec la bibliothèque graphique **SDL2**.  
> Défendez la Tour du Roi contre une horde d'ennemis sur un chemin généré procéduralement.

![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)
![Library](https://img.shields.io/badge/Library-SDL2-red?style=flat-square)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-lightgrey?style=flat-square)
![Status](https://img.shields.io/badge/Status-Fonctionnel-brightgreen?style=flat-square)

**Auteur :** MOHAMED Rayane

---

## 📚 Table des Matières

- [Description](#-description)
- [Fonctionnalités](#-fonctionnalités)
- [Prérequis & Installation](#️-prérequis--installation)
- [Compilation & Exécution](#-compilation--exécution)
- [Contrôles](#-contrôles)
- [Architecture](#-architecture-du-projet)
- [Ressources graphiques](#️-ressources-graphiques)

---

## 📝 Description

**TowerDefend** est un jeu de type *Tower Defense* où le joueur doit défendre sa forteresse contre une horde d'ennemis variés — Dragons 🐉, Gargouilles, Archers et Chevaliers — qui avancent le long d'un chemin **généré aléatoirement**.

Le jeu repose sur :
- Un moteur de **combat automatisé** avec gestion des portées et types de cibles
- Des **apparitions aléatoires** de tours de défense (Sol / Air)
- Un **système de sauvegarde double format** (binaire et séquentiel)

---

## ✨ Fonctionnalités

### 🗺️ Génération de Chemin Dynamique
Le parcours ennemi est généré aléatoirement à chaque partie avec un algorithme **anti-zigzag**, garantissant un chemin cohérent et jouable jusqu'à la Tour du Roi.

### ⚔️ Système de Combat
| Aspect | Détail |
|---|---|
| Types d'unités | Aériennes 🐉 et terrestres 🧙 |
| Portée d'attaque | Chaque tour a une portée définie |
| Ciblage | Les tours au sol ne peuvent **pas** attaquer les unités volantes |
| Priorité | Attaque en priorité les ennemis avec le **moins de PV** (tri par sélection) |

### 🧠 Gestion Dynamique de la Mémoire
Les unités (ennemis et tours) sont gérées via des **listes chaînées** (`TListePlayer`), permettant des apparitions, déplacements et suppressions en temps réel sans réallocation massive.

### 💾 Sauvegarde & Restauration
| Format | Extension | Description |
|---|---|---|
| Binaire | `.tdb` | Sauvegarde rapide et compacte de l'état mémoire |
| Séquentiel | `.tds` | Sauvegarde lisible au format texte |

---

## 🛠️ Prérequis & Installation

Vous devez disposer de : `gcc`, `make`, et les bibliothèques **SDL2**.

### Linux (Debian / Ubuntu / Arch)

```bash
# Debian / Ubuntu
sudo apt-get update
sudo apt-get install gcc make pkg-config libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev

# Arch Linux
sudo pacman -S gcc make pkg-config sdl2 sdl2_image sdl2_ttf sdl2_mixer
```

### macOS (Homebrew)

```bash
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer pkg-config
```

---

## 🚀 Compilation & Exécution

Clonez le projet et placez-vous à sa racine :

```bash
git clone <url-du-repo>
cd TowerDefend
```

| Commande | Action |
|---|---|
| `make` | Compile le projet |
| `make run` | Lance le jeu |
| `make clean` | Supprime les fichiers `.o` |
| `make fclean` | Supprime `.o` **et** l'exécutable |

Ou manuellement après compilation :

```bash
./tower_defend
```

---

## 🎮 Contrôles

| Touche | Action |
|:---:|---|
| `ÉCHAP` | Quitter le jeu |
| `S` | 💾 Sauvegarder en **binaire** → `partiebin.tdb` |
| `C` | 📂 Charger la sauvegarde **binaire** |
| `D` | 💾 Sauvegarder en **séquentiel** → `partieseq.tds` |
| `V` | 📂 Charger la sauvegarde **séquentielle** |

---

## 📁 Architecture du Projet

```
TowerDefend/
│
├── main.c            # Point d'entrée : init SDL2, boucle de jeu, input clavier
├── towerdefend.h     # Structures (Tunite, T_cell), énumérations, signatures
├── towerdefend.c     # Logique IA, listes chaînées, génération de chemin, sérialisation
├── Makefile          # Script de compilation et liaison des bibliothèques
│
└── data/             # Ressources graphiques (.bmp)
    ├── TourSol.bmp
    ├── Dragon.bmp
    ├── Herbe.bmp
    └── ...
```

---

## ⚠️ Ressources Graphiques

> **Important :** Le dossier `./data/` doit être présent à la racine de l'exécutable.  
> Sans lui, la SDL2 échouera au chargement des sprites et la fenêtre ne s'ouvrira pas.

Vérifiez sa présence avant de lancer le jeu :

```bash
ls ./data/
```
