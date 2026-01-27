// ============================================================================
// SudokuGrid.cpp
// Implémentation de la logique Sudoku
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#include "../include/SudokuGrid.h"
#include <cstdlib>
#include <ctime>

// ============================================================================
// Constructeur
// ============================================================================
SudokuGrid::SudokuGrid()
{
    // Initialise le générateur aléatoire
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Initialise les grilles 9x9
    mGrid.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
    mInitialGrid.resize(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));
}

// ============================================================================
// Initialise une nouvelle grille
// ============================================================================
void SudokuGrid::Initialize()
{
    Clear();        // Vide d'abord la grille
    GenerateGrid(); // Génère une nouvelle grille
}

// ============================================================================
// Vérifie si un placement est valide
// ============================================================================
bool SudokuGrid::IsValidPlacement(int row, int col, int num)
{
    // Vérifie la ligne
    for (int x = 0; x < GRID_SIZE; x++)
    {
        if (mGrid[row][x] == num && x != col)
            return false;
    }
    
    // Vérifie la colonne
    for (int y = 0; y < GRID_SIZE; y++)
    {
        if (mGrid[y][col] == num && y != row)
            return false;
    }
    
    // Vérifie le bloc 3x3
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int checkRow = startRow + i;
            int checkCol = startCol + j;
            if (mGrid[checkRow][checkCol] == num && 
                (checkRow != row || checkCol != col))
                return false;
        }
    }
    
    return true;
}

// ============================================================================
// Génère une grille aléatoire
// ============================================================================
void SudokuGrid::GenerateGrid()
{
    int placed = 0;
    int attempts = 0;
    const int MAX_ATTEMPTS = 1000;
    const int TARGET_CELLS = 22; // Nombre de cases pré-remplies
    
    // Place aléatoirement des chiffres valides
    while (placed < TARGET_CELLS && attempts < MAX_ATTEMPTS)
    {
        int row = rand() % GRID_SIZE;
        int col = rand() % GRID_SIZE;
        int num = (rand() % 9) + 1;
        
        if (mGrid[row][col] == 0 && IsValidPlacement(row, col, num))
        {
            mGrid[row][col] = num;
            mInitialGrid[row][col] = true; // Marque comme case initiale
            placed++;
        }
        
        attempts++;
    }
}

// ============================================================================
// Place un chiffre dans une cellule
// ============================================================================
bool SudokuGrid::SetCell(int row, int col, int num)
{
    // Ne peut pas modifier une case initiale
    if (mInitialGrid[row][col])
        return false;
    
    // Efface la cellule si num == 0
    if (num == 0)
    {
        mGrid[row][col] = 0;
        return true;
    }
    
    // Vérifie la validité du placement
    if (IsValidPlacement(row, col, num))
    {
        mGrid[row][col] = num;
        return true;
    }
    
    return false;
}

// ============================================================================
// Obtient la valeur d'une cellule
// ============================================================================
int SudokuGrid::GetCell(int row, int col) const
{
    return mGrid[row][col];
}

// ============================================================================
// Vérifie si une cellule est initiale
// ============================================================================
bool SudokuGrid::IsInitialCell(int row, int col) const
{
    return mInitialGrid[row][col];
}

// ============================================================================
// Vérifie si la grille est complétée
// ============================================================================
bool SudokuGrid::CheckWin() const
{
    // Vérifie qu'il n'y a aucune case vide
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (mGrid[i][j] == 0)
                return false;
        }
    }
    return true;
}

// ============================================================================
// Vide la grille
// ============================================================================
void SudokuGrid::Clear()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            mGrid[i][j] = 0;
            mInitialGrid[i][j] = false;
        }
    }
}