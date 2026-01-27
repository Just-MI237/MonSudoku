// ============================================================================
// Game.cpp
// Implémentation de la boucle de jeu principale
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#include "../include/Game.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include <iostream>

// ============================================================================
// Constructeur
// ============================================================================
Game::Game() : mIsRunning(false), 
               mWindow(nullptr), 
               mSDLRenderer(nullptr),
               mRenderer(nullptr),
               mUI(nullptr),
               mSplashScreen(nullptr),
               mShowingSplash(true),
               mSelectedRow(-1),
               mSelectedCol(-1)
{
}

// ============================================================================
// Destructeur
// ============================================================================
Game::~Game()
{
    Shutdown();
}

// ============================================================================
// Initialise le jeu
// ============================================================================
bool Game::Initialize()
{
    // Initialise SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Erreur SDL_Init: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Crée la fenêtre
    mWindow = SDL_CreateWindow(
        "Sudoku - Just Max It",
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );
    
    if (!mWindow)
    {
        std::cerr << "Erreur fenetre: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    
    // Crée le renderer
    mSDLRenderer = SDL_CreateRenderer(mWindow, nullptr);
    if (!mSDLRenderer)
    {
        std::cerr << "Erreur renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return false;
    }
    
    // Initialise les composants
    mRenderer = new Renderer(mSDLRenderer);
    mUI = new UI();
    mSplashScreen = new SplashScreen(mSDLRenderer);
    
    mUI->Initialize(mWindow, mSDLRenderer);
    mSplashScreen->Start();
    mGrid.Initialize();
    
    std::cout << "======================================" << std::endl;
    std::cout << "  SUDOKU - Just Max It, Everyday" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "Initialisation reussie !" << std::endl;
    
    mIsRunning = true;
    return true;
}

// ============================================================================
// Ferme proprement le jeu
// ============================================================================
void Game::Shutdown()
{
    if (mSplashScreen)
    {
        delete mSplashScreen;
        mSplashScreen = nullptr;
    }
    
    if (mUI)
    {
        mUI->Shutdown();
        delete mUI;
        mUI = nullptr;
    }
    
    if (mRenderer)
    {
        delete mRenderer;
        mRenderer = nullptr;
    }
    
    if (mSDLRenderer)
    {
        SDL_DestroyRenderer(mSDLRenderer);
        mSDLRenderer = nullptr;
    }
    
    if (mWindow)
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }
    
    SDL_Quit();
}

// ============================================================================
// Convertit les coordonnées souris en cellule
// ============================================================================
bool Game::GetCellFromMouse(int mouseX, int mouseY, int* row, int* col)
{
    if (mouseX < GRID_OFFSET_X || 
        mouseX > GRID_OFFSET_X + GRID_SIZE * CELL_SIZE)
        return false;
    
    if (mouseY < GRID_OFFSET_Y || 
        mouseY > GRID_OFFSET_Y + GRID_SIZE * CELL_SIZE)
        return false;
    
    *col = (mouseX - GRID_OFFSET_X) / CELL_SIZE;
    *row = (mouseY - GRID_OFFSET_Y) / CELL_SIZE;
    
    if (*row < 0 || *row >= GRID_SIZE || *col < 0 || *col >= GRID_SIZE)
        return false;
    
    return true;
}

// ============================================================================
// Gère les clics de souris
// ============================================================================
void Game::HandleMouseClick(int x, int y)
{
    std::cout << "[DEBUG] Clic souris a (" << x << "," << y << ")" << std::endl;
    
    int row, col;
    if (GetCellFromMouse(x, y, &row, &col))
    {
        mSelectedRow = row;
        mSelectedCol = col;
        std::cout << "[DEBUG] Cellule selectionnee: (" << row << "," << col << ")" << std::endl;
    }
    else
    {
        mSelectedRow = -1;
        mSelectedCol = -1;
        std::cout << "[DEBUG] Clic hors grille" << std::endl;
    }
}

// ============================================================================
// Gère les touches du clavier
// ============================================================================
void Game::HandleKeyPress(SDL_Keycode key)
{
    std::cout << "[DEBUG] Touche pressee: " << (int)key << std::endl;
    
    // Nouvelle grille avec N
    if (key == SDLK_N)
    {
        std::cout << "[DEBUG] Nouvelle grille demandee" << std::endl;
        mGrid.Initialize();
        mSelectedRow = -1;
        mSelectedCol = -1;
        mUI->ShowMessage("Nouvelle grille");
        return;
    }
    // Réinitialiser avec R
    else if (key == SDLK_R)
    {
        std::cout << "[DEBUG] Reinitialisation demandee" << std::endl;
        mGrid.Clear();
        mGrid.Initialize();
        mSelectedRow = -1;
        mSelectedCol = -1;
        mUI->ShowMessage("Reinitialise");
        return;
    }
    
    // Vérifie qu'une cellule est sélectionnée
    if (mSelectedRow == -1 || mSelectedCol == -1)
    {
        std::cout << "[DEBUG] Aucune cellule selectionnee" << std::endl;
        return;
    }
    
    int num = 0;
    
    // Détecte le chiffre - TOUCHES NORMALES (rangée principale)
    if (key >= SDLK_1 && key <= SDLK_9)
    {
        num = key - SDLK_0;
        std::cout << "[DEBUG] Chiffre detecte (touches principales): " << num << std::endl;
    }
    // PAVÉ NUMÉRIQUE - Correction du calcul
    else if (key >= SDLK_KP_1 && key <= SDLK_KP_9)
    {
        // Les touches du pavé numérique ont des codes spéciaux
        // SDLK_KP_1 = 1073741913, SDLK_KP_9 = 1073741921
        num = (key - SDLK_KP_1) + 1;
        std::cout << "[DEBUG] Chiffre detecte (pave numerique): " << num << std::endl;
    }
    // Effacer
    else if (key == SDLK_BACKSPACE || key == SDLK_DELETE || 
             key == SDLK_0 || key == SDLK_KP_0)
    {
        num = 0;
        std::cout << "[DEBUG] Effacement demande" << std::endl;
    }
    else
    {
        std::cout << "[DEBUG] Touche non reconnue pour placement (code: " << (int)key << ")" << std::endl;
        return;
    }
    
    std::cout << "[DEBUG] Tentative placement: " << num << " a (" << mSelectedRow << "," << mSelectedCol << ")" << std::endl;
    
    // Tente le placement
    bool success = mGrid.SetCell(mSelectedRow, mSelectedCol, num);
    
    if (success)
    {
        std::cout << "[DEBUG] Placement reussi !" << std::endl;
        if (num == 0)
            mUI->ShowMessage("Efface");
        else
            mUI->ShowMessage("Place !");
        
        if (mGrid.CheckWin())
        {
            std::cout << "[DEBUG] VICTOIRE DETECTEE !" << std::endl;
        }
    }
    else
    {
        std::cout << "[DEBUG] Placement echoue" << std::endl;
        if (mGrid.IsInitialCell(mSelectedRow, mSelectedCol))
            mUI->ShowMessage("Case fixe");
        else
            mUI->ShowMessage("Invalide");
    }
}

// ============================================================================
// Gère les événements
// ============================================================================
void Game::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
        
        if (event.type == SDL_EVENT_QUIT)
        {
            std::cout << "[DEBUG] Fermeture demandee" << std::endl;
            mIsRunning = false;
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                std::cout << "[DEBUG] Clic gauche detecte" << std::endl;
                std::cout << "[DEBUG] Splash: " << mShowingSplash << ", ImGui capture: " << mUI->WantsMouseCapture() << std::endl;
                
                if (!mShowingSplash && !mUI->WantsMouseCapture())
                {
                    HandleMouseClick(
                        static_cast<int>(event.button.x),
                        static_cast<int>(event.button.y)
                    );
                }
                else
                {
                    std::cout << "[DEBUG] Clic ignore (splash ou ImGui)" << std::endl;
                }
            }
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            std::cout << "[DEBUG] Touche detectee" << std::endl;
            std::cout << "[DEBUG] Splash: " << mShowingSplash << ", ImGui capture: " << mUI->WantsKeyboardCapture() << std::endl;
            
            if (!mShowingSplash && !mUI->WantsKeyboardCapture())
            {
                if (event.key.key == SDLK_ESCAPE)
                {
                    std::cout << "[DEBUG] Echap -> Quitter" << std::endl;
                    mIsRunning = false;
                }
                else
                {
                    HandleKeyPress(event.key.key);
                }
            }
            else
            {
                std::cout << "[DEBUG] Touche ignoree (splash ou ImGui)" << std::endl;
            }
        }
    }
}

// ============================================================================
// Met à jour la logique
// ============================================================================
void Game::Update()
{
}

// ============================================================================
// Affiche le jeu
// ============================================================================
void Game::Render()
{
    mRenderer->Clear();
    mRenderer->DrawHighlights(mSelectedRow, mSelectedCol);
    mRenderer->DrawSelection(mSelectedRow, mSelectedCol);
    mRenderer->DrawGrid();
    mRenderer->DrawNumbers(&mGrid);
    
    mUI->NewFrame();
    mUI->DrawMainMenu(&mGrid);
    mUI->DrawStatusBar(&mGrid);
    mUI->Render();
    
    mRenderer->Present();
}

// ============================================================================
// Boucle de jeu principale
// ============================================================================
void Game::Run()
{
    std::cout << "[DEBUG] Demarrage boucle de jeu" << std::endl;
    
    while (mIsRunning)
    {
        HandleEvents();
        
        if (mShowingSplash)
        {
            mSplashScreen->Update();
            mSplashScreen->Render();
            SDL_RenderPresent(mSDLRenderer);
            
            if (mSplashScreen->IsFinished())
            {
                std::cout << "[DEBUG] Splash screen termine - Passage au jeu" << std::endl;
                mShowingSplash = false;
            }
        }
        else
        {
            Update();
            Render();
        }
        
        SDL_Delay(16);
    }
    
    std::cout << "[DEBUG] Fin boucle de jeu" << std::endl;
}