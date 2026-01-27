// ============================================================================
// Renderer.h
// Gestion de l'affichage graphique du jeu
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include "SudokuGrid.h"

class Renderer
{
private:
    SDL_Renderer* mRenderer; // Pointeur vers le renderer SDL

public:
    // Constructeur
    Renderer(SDL_Renderer* renderer);
    
    // Efface l'écran
    void Clear();
    
    // Dessine la grille Sudoku
    void DrawGrid();
    
    // Dessine les chiffres de la grille
    void DrawNumbers(SudokuGrid* grid);
    
    // Dessine la sélection de cellule
    void DrawSelection(int row, int col);
    
    // Dessine les surlignages (ligne, colonne, bloc 3x3)
    void DrawHighlights(int selectedRow, int selectedCol);
    
    // Affiche le rendu à l'écran
    void Present();
};

#endif // RENDERER_H