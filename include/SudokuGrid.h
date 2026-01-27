// ============================================================================
// SudokuGrid.h
// Gestion de la grille Sudoku et de sa logique
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include <vector>
#include "Utils.h"

class SudokuGrid
{
private:
    // Grille principale (valeurs actuelles)
    std::vector<std::vector<int>> mGrid;
    
    // Grille des cases initiales (non modifiables)
    std::vector<std::vector<bool>> mInitialGrid;
    
    // Vérifie si un placement est valide selon les règles du Sudoku
    bool IsValidPlacement(int row, int col, int num);

public:
    // Constructeur
    SudokuGrid();
    
    // Initialise une nouvelle grille
    void Initialize();
    
    // Génère une grille aléatoire
    void GenerateGrid();
    
    // Place un chiffre dans une cellule
    bool SetCell(int row, int col, int num);
    
    // Obtient la valeur d'une cellule
    int GetCell(int row, int col) const;
    
    // Vérifie si une cellule est une case initiale
    bool IsInitialCell(int row, int col) const;
    
    // Vérifie si la grille est complétée
    bool CheckWin() const;
    
    // Vide la grille
    void Clear();
};

#endif // SUDOKUGRID_H