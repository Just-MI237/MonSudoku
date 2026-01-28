#  SUDOKU - Just Max It, Everyday

Projet Sudoku réalisé en C++ avec SDL3 et ImGui dans le cadre du cours de Game Programming.

##  Description

Un jeu de Sudoku complet avec :
- Splash screen animé "JUST MAX IT, Everyday"
- Interface graphique avec ImGui
- Génération aléatoire de grilles
- Vérification des règles du Sudoku
- Détection de victoire

##  Technologies utilisées

- **Langage** : C++17
- **Bibliothèque graphique** : SDL3
- **Interface utilisateur** : ImGui
- **Compilateur** : Clang++
- **Système** : Ubuntu 22.04 (WSL2)

##  Prérequis

- Ubuntu 22.04 (ou WSL2)
- SDL3 installé
- Clang++ installé
- Python 3 (pour le script de build)

##  Compilation

Pour compiler le projet :
```bash
python3 build.py
```

##  Lancement

Pour lancer le jeu :
```bash
./sudoku
```

##  Contrôles

- **Clic gauche** : Sélectionner une case
- **1-9** : Placer un chiffre
- **Retour / Suppr / 0** : Effacer une case
- **N** : Nouvelle grille
- **R** : Réinitialiser la grille
- **Échap** : Quitter le jeu

##  Règles du Sudoku

- Chaque ligne doit contenir les chiffres 1-9 une seule fois
- Chaque colonne doit contenir les chiffres 1-9 une seule fois
- Chaque carré 3x3 doit contenir les chiffres 1-9 une seule fois

##  Légende des couleurs

- **Noir** : Cases initiales (non modifiables)
- **Bleu** : Chiffres placés par le joueur
- **Bleu clair** : Case sélectionnée
- **Bleu très clair** : Ligne, colonne et carré 3x3 surlignés

##  Auteur

Vivien Yann Nka - École Nationale Supérieure Polytechnique de Yaoundé 1 - ANI 1 - 25P913

##  Date

Janvier 2026

##  Licence

Projet académique - Cours de Game Programming