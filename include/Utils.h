// ============================================================================
// Utils.h
// Constantes globales et configurations pour le jeu Sudoku
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#ifndef UTILS_H
#define UTILS_H

#include <SDL3/SDL.h>

// Dimensions de la fenêtre
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 650;

// Dimensions de la grille Sudoku
const int GRID_SIZE = 9;           // Grille 9x9
const int CELL_SIZE = 50;          // Taille d'une cellule en pixels
const int GRID_OFFSET_X = 100;     // Décalage horizontal de la grille
const int GRID_OFFSET_Y = 80;      // Décalage vertical de la grille

// Palette de couleurs du jeu
const SDL_Color COLOR_WHITE = {255, 255, 255, 255};
const SDL_Color COLOR_BLACK = {0, 0, 0, 255};
const SDL_Color COLOR_GRAY = {200, 200, 200, 255};
const SDL_Color COLOR_LIGHT_BLUE = {200, 220, 255, 255};
const SDL_Color COLOR_VERY_LIGHT_BLUE = {240, 245, 255, 255};
const SDL_Color COLOR_BLUE = {70, 130, 220, 255};

#endif // UTILS_H