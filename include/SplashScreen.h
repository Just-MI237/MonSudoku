// ============================================================================
// SplashScreen.h
// Écran de démarrage "JUST MAX IT, Everyday"
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <SDL3/SDL.h>
#include <string>

class SplashScreen
{
private:
    SDL_Renderer* mRenderer;
    
    // Durées des animations (en millisecondes)
    const unsigned long long FADE_IN_DURATION = 1000;   // Apparition
    const unsigned long long HOLD_DURATION = 1500;      // Maintien
    const unsigned long long FADE_OUT_DURATION = 800;   // Disparition
    const unsigned long long TOTAL_DURATION = 4000;     // Durée totale
    
    unsigned long long mStartTime;  // Temps de démarrage
    bool mIsFinished;               // Animation terminée ?
    
    // Calcule l'opacité en fonction du temps
    int CalculateAlpha(unsigned long long currentTime);
    
    // Dessine du texte à l'écran
    void DrawText(const std::string& text, int y, int alpha, bool large = false);
    
    // Dessine le logo complet
    void DrawLogo(int alpha);

public:
    // Constructeur
    SplashScreen(SDL_Renderer* renderer);
    
    // Démarre l'animation
    void Start();
    
    // Met à jour l'animation
    void Update();
    
    // Affiche l'animation
    void Render();
    
    // Vérifie si l'animation est terminée
    bool IsFinished() const;
};

#endif // SPLASHSCREEN_H