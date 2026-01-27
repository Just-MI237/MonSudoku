// ============================================================================
// UI.h
// Interface utilisateur avec ImGui
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#ifndef UI_H
#define UI_H

#include <SDL3/SDL.h>
#include <string>

class SudokuGrid; // Déclaration forward

class UI
{
private:
    bool mShowWinMessage;           // Afficher le message de victoire ?
    std::string mStatusMessage;     // Message temporaire
    unsigned long long mMessageTime; // Temps d'affichage du message

public:
    // Constructeur et destructeur
    UI();
    ~UI();
    
    // Initialise ImGui
    void Initialize(SDL_Window* window, SDL_Renderer* renderer);
    
    // Ferme ImGui
    void Shutdown();
    
    // Démarre une nouvelle frame ImGui
    void NewFrame();
    
    // Affiche le rendu ImGui
    void Render();
    
    // Dessine le menu principal
    void DrawMainMenu(SudokuGrid* grid);
    
    // Dessine la barre de statut
    void DrawStatusBar(SudokuGrid* grid);
    
    // Affiche un message temporaire
    void ShowMessage(const std::string& message);
    
    // Vérifie si ImGui capture la souris
    bool WantsMouseCapture() const;
    
    // Vérifie si ImGui capture le clavier
    bool WantsKeyboardCapture() const;
};

#endif // UI_H