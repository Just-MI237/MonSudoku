// ============================================================================
// Game.h
// Classe principale du jeu - Gère la boucle de jeu
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include "SudokuGrid.h"
#include "Renderer.h"
#include "UI.h"
#include "SplashScreen.h"

class Game
{
private:
    // État du jeu
    bool mIsRunning;
    
    // Composants SDL
    SDL_Window* mWindow;
    SDL_Renderer* mSDLRenderer;
    
    // Composants du jeu
    SudokuGrid mGrid;
    Renderer* mRenderer;
    UI* mUI;
    SplashScreen* mSplashScreen;
    
    // État du splash screen
    bool mShowingSplash;
    
    // Sélection de cellule
    int mSelectedRow;
    int mSelectedCol;

public:
    // Constructeur et destructeur
    Game();
    ~Game();
    
    // Initialise le jeu
    bool Initialize();
    
    // Lance la boucle de jeu
    void Run();
    
    // Ferme proprement le jeu
    void Shutdown();
    
private:
    // Gère les événements (clavier, souris)
    void HandleEvents();
    
    // Met à jour la logique du jeu
    void Update();
    
    // Affiche le jeu
    void Render();
    
    // Gère les clics de souris
    void HandleMouseClick(int x, int y);
    
    // Gère les touches du clavier
    void HandleKeyPress(SDL_Keycode key);
    
    // Convertit les coordonnées souris en cellule
    bool GetCellFromMouse(int mouseX, int mouseY, int* row, int* col);
};

#endif // GAME_H