// ============================================================================
// Renderer.cpp
// Implémentation du rendu graphique
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#include "../include/Renderer.h"

// ============================================================================
// Constructeur
// ============================================================================
Renderer::Renderer(SDL_Renderer* renderer) : mRenderer(renderer)
{
}

// ============================================================================
// Efface l'écran (fond blanc)
// ============================================================================
void Renderer::Clear()
{
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_RenderClear(mRenderer);
}

// ============================================================================
// Dessine les surlignages (ligne, colonne, bloc 3x3)
// ============================================================================
void Renderer::DrawHighlights(int selectedRow, int selectedCol)
{
    if (selectedRow == -1 || selectedCol == -1)
        return;
    
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            int x = GRID_OFFSET_X + col * CELL_SIZE;
            int y = GRID_OFFSET_Y + row * CELL_SIZE;
            
            SDL_Color bgColor = COLOR_WHITE;
            
            // Surligne la ligne et la colonne
            if (row == selectedRow || col == selectedCol)
                bgColor = COLOR_VERY_LIGHT_BLUE;
            
            // Surligne le bloc 3x3
            int selStartRow = (selectedRow / 3) * 3;
            int selStartCol = (selectedCol / 3) * 3;
            int cellStartRow = (row / 3) * 3;
            int cellStartCol = (col / 3) * 3;
            
            if (selStartRow == cellStartRow && selStartCol == cellStartCol)
                bgColor = COLOR_VERY_LIGHT_BLUE;
            
            SDL_SetRenderDrawColor(mRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
            SDL_FRect rect = {(float)x, (float)y, (float)CELL_SIZE, (float)CELL_SIZE};
            SDL_RenderFillRect(mRenderer, &rect);
        }
    }
}

// ============================================================================
// Dessine la sélection de cellule (bleu clair)
// ============================================================================
void Renderer::DrawSelection(int row, int col)
{
    if (row == -1 || col == -1)
        return;
    
    int x = GRID_OFFSET_X + col * CELL_SIZE;
    int y = GRID_OFFSET_Y + row * CELL_SIZE;
    
    SDL_SetRenderDrawColor(mRenderer, COLOR_LIGHT_BLUE.r, COLOR_LIGHT_BLUE.g,
                           COLOR_LIGHT_BLUE.b, COLOR_LIGHT_BLUE.a);
    SDL_FRect rect = {(float)x, (float)y, (float)CELL_SIZE, (float)CELL_SIZE};
    SDL_RenderFillRect(mRenderer, &rect);
}

// ============================================================================
// Dessine la grille Sudoku (lignes et colonnes)
// ============================================================================
void Renderer::DrawGrid()
{
    // Lignes verticales
    for (int i = 0; i <= GRID_SIZE; i++)
    {
        int x = GRID_OFFSET_X + i * CELL_SIZE;
        int y1 = GRID_OFFSET_Y;
        int y2 = GRID_OFFSET_Y + GRID_SIZE * CELL_SIZE;
        
        if (i % 3 == 0) // Lignes épaisses
        {
            SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
            for (int offset = -1; offset <= 1; offset++)
            {
                SDL_RenderLine(mRenderer, x + offset, y1, x + offset, y2);
            }
        }
        else // Lignes fines
        {
            SDL_SetRenderDrawColor(mRenderer, 200, 200, 200, 255);
            SDL_RenderLine(mRenderer, x, y1, x, y2);
        }
    }
    
    // Lignes horizontales
    for (int i = 0; i <= GRID_SIZE; i++)
    {
        int x1 = GRID_OFFSET_X;
        int x2 = GRID_OFFSET_X + GRID_SIZE * CELL_SIZE;
        int y = GRID_OFFSET_Y + i * CELL_SIZE;
        
        if (i % 3 == 0) // Lignes épaisses
        {
            SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
            for (int offset = -1; offset <= 1; offset++)
            {
                SDL_RenderLine(mRenderer, x1, y + offset, x2, y + offset);
            }
        }
        else // Lignes fines
        {
            SDL_SetRenderDrawColor(mRenderer, 200, 200, 200, 255);
            SDL_RenderLine(mRenderer, x1, y, x2, y);
        }
    }
}

// ============================================================================
// Dessine les chiffres dans la grille (VERSION AVEC TRAITS ÉPAIS)
// ============================================================================
void Renderer::DrawNumbers(SudokuGrid* grid)
{
    const int SIZE = 15; // Taille des segments
    const int THICKNESS = 3; // Épaisseur
    
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            int num = grid->GetCell(row, col);
            if (num == 0) continue;
            
            // Centre de la cellule
            int x = GRID_OFFSET_X + col * CELL_SIZE + CELL_SIZE / 2;
            int y = GRID_OFFSET_Y + row * CELL_SIZE + CELL_SIZE / 2;
            
            // Couleur : noir pour initial, bleu pour joueur
            SDL_Color color = grid->IsInitialCell(row, col) ? COLOR_BLACK : COLOR_BLUE;
            SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
            
            // Fonction lambda pour dessiner des lignes épaisses
            auto drawThickLine = [this, THICKNESS](int x1, int y1, int x2, int y2) {
                for (int i = -THICKNESS/2; i <= THICKNESS/2; i++) {
                    if (x1 == x2) { // Ligne verticale
                        SDL_RenderLine(mRenderer, x1 + i, y1, x2 + i, y2);
                    } else { // Ligne horizontale
                        SDL_RenderLine(mRenderer, x1, y1 + i, x2, y2 + i);
                    }
                }
            };
            
            // Dessine le chiffre
            switch (num)
            {
                case 1:
                    drawThickLine(x, y - SIZE, x, y + SIZE);
                    break;
                    
                case 2:
                    drawThickLine(x - SIZE, y - SIZE, x + SIZE, y - SIZE);
                    drawThickLine(x + SIZE, y - SIZE, x + SIZE, y);
                    drawThickLine(x - SIZE, y, x + SIZE, y);
                    drawThickLine(x - SIZE, y, x - SIZE, y + SIZE);
                    drawThickLine(x - SIZE, y + SIZE, x + SIZE, y + SIZE);
                    break;
                    
                case 3:
                    drawThickLine(x - SIZE, y - SIZE, x + SIZE, y - SIZE);
                    drawThickLine(x + SIZE, y - SIZE, x + SIZE, y + SIZE);
                    drawThickLine(x - SIZE, y, x + SIZE, y);
                    drawThickLine(x - SIZE, y + SIZE, x + SIZE, y + SIZE);
                    break;
                    
                case 4:
                    drawThickLine(x - SIZE, y - SIZE, x - SIZE, y);
                    drawThickLine(x - SIZE, y, x + SIZE, y);
                    drawThickLine(x + SIZE, y - SIZE, x + SIZE, y + SIZE);
                    break;
                    
                case 5:
                    drawThickLine(x - SIZE, y - SIZE, x + SIZE, y - SIZE);
                    drawThickLine(x - SIZE, y - SIZE, x - SIZE, y);
                    drawThickLine(x - SIZE, y, x + SIZE, y);
                    drawThickLine(x + SIZE, y, x + SIZE, y + SIZE);
                    drawThickLine(x - SIZE, y + SIZE, x + SIZE, y + SIZE);
                    break;
                    
                case 6:
                    drawThickLine(x - SIZE, y - SIZE, x + SIZE, y - SIZE);
                    drawThickLine(x - SIZE, y - SIZE, x - SIZE, y + SIZE);
                    drawThickLine(x - SIZE, y, x + SIZE, y);
                    drawThickLine(x + SIZE, y, x + SIZE, y + SIZE);
                    drawThickLine(x - SIZE, y + SIZE, x + SIZE, y + SIZE);
                    break;
                    
                case 7:
                    drawThickLine(x - SIZE, y - SIZE, x + SIZE, y - SIZE);
                    drawThickLine(x + SIZE, y - SIZE, x + SIZE, y + SIZE);
                    break;
                    
                case 8:
                    drawThickLine(x - SIZE, y - SIZE, x + SIZE, y - SIZE);
                    drawThickLine(x - SIZE, y - SIZE, x - SIZE, y + SIZE);
                    drawThickLine(x + SIZE, y - SIZE, x + SIZE, y + SIZE);
                    drawThickLine(x - SIZE, y, x + SIZE, y);
                    drawThickLine(x - SIZE, y + SIZE, x + SIZE, y + SIZE);
                    break;
                    
                case 9:
                    drawThickLine(x - SIZE, y - SIZE, x + SIZE, y - SIZE);
                    drawThickLine(x - SIZE, y - SIZE, x - SIZE, y);
                    drawThickLine(x + SIZE, y - SIZE, x + SIZE, y + SIZE);
                    drawThickLine(x - SIZE, y, x + SIZE, y);
                    drawThickLine(x - SIZE, y + SIZE, x + SIZE, y + SIZE);
                    break;
            }
        }
    }
}

// ============================================================================
// Affiche le rendu à l'écran
// ============================================================================
void Renderer::Present()
{
    SDL_RenderPresent(mRenderer);
}