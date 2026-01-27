// ============================================================================
// SplashScreen.cpp
// Implémentation de l'écran de démarrage "JUST MAX IT, Everyday"
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#include "../include/SplashScreen.h"
#include "../include/Utils.h"
#include <cmath>

// ============================================================================
// Constructeur
// ============================================================================
SplashScreen::SplashScreen(SDL_Renderer* renderer) 
    : mRenderer(renderer), mStartTime(0), mIsFinished(false)
{
}

// ============================================================================
// Démarre l'animation
// ============================================================================
void SplashScreen::Start()
{
    mStartTime = SDL_GetTicks();
    mIsFinished = false;
}

// ============================================================================
// Calcule l'opacité en fonction du temps (fade in/hold/fade out)
// ============================================================================
int SplashScreen::CalculateAlpha(unsigned long long currentTime)
{
    unsigned long long elapsed = currentTime - mStartTime;
    
    if (elapsed < FADE_IN_DURATION)
    {
        float progress = (float)elapsed / (float)FADE_IN_DURATION;
        return (int)(progress * 255.0f);
    }
    else if (elapsed < FADE_IN_DURATION + HOLD_DURATION)
    {
        return 255;
    }
    else if (elapsed < TOTAL_DURATION)
    {
        unsigned long long fadeOutStart = FADE_IN_DURATION + HOLD_DURATION;
        unsigned long long fadeOutElapsed = elapsed - fadeOutStart;
        float progress = 1.0f - ((float)fadeOutElapsed / (float)FADE_OUT_DURATION);
        return (int)(progress * 255.0f);
    }
    else
    {
        mIsFinished = true;
        return 0;
    }
}

// ============================================================================
// Fonction pour dessiner une lettre en style "7 segments" agrandi
// ============================================================================
void DrawLetter(SDL_Renderer* renderer, char letter, int x, int y, int size, int thickness)
{
    auto drawThickHLine = [renderer, thickness](int x1, int x2, int y) {
        for (int i = 0; i < thickness; i++) {
            SDL_RenderLine(renderer, x1, y + i, x2, y + i);
        }
    };
    
    auto drawThickVLine = [renderer, thickness](int x, int y1, int y2) {
        for (int i = 0; i < thickness; i++) {
            SDL_RenderLine(renderer, x + i, y1, x + i, y2);
        }
    };
    
    switch(letter)
    {
        case 'J':
            drawThickHLine(x, x + size, y); // Haut
            drawThickVLine(x + size/2, y, y + size); // Milieu
            drawThickVLine(x, y + size/2, y + size); // Bas gauche
            drawThickHLine(x, x + size/2, y + size); // Bas
            break;
            
        case 'U':
            drawThickVLine(x, y, y + size); // Gauche
            drawThickVLine(x + size, y, y + size); // Droite
            drawThickHLine(x, x + size, y + size); // Bas
            break;
            
        case 'S':
            drawThickHLine(x, x + size, y); // Haut
            drawThickVLine(x, y, y + size/2); // Haut gauche
            drawThickHLine(x, x + size, y + size/2); // Milieu
            drawThickVLine(x + size, y + size/2, y + size); // Bas droite
            drawThickHLine(x, x + size, y + size); // Bas
            break;
            
        case 'T':
            drawThickHLine(x, x + size, y); // Haut
            drawThickVLine(x + size/2, y, y + size); // Milieu vertical
            break;
            
        case 'M':
            drawThickVLine(x, y, y + size); // Gauche
            drawThickVLine(x + size, y, y + size); // Droite
            drawThickVLine(x + size/2, y, y + size/2); // Milieu
            SDL_RenderLine(renderer, x, y, x + size/2, y + size/3); // Diagonale gauche
            SDL_RenderLine(renderer, x + size, y, x + size/2, y + size/3); // Diagonale droite
            break;
            
        case 'A':
            drawThickHLine(x, x + size, y); // Haut
            drawThickVLine(x, y, y + size); // Gauche
            drawThickVLine(x + size, y, y + size); // Droite
            drawThickHLine(x, x + size, y + size/2); // Milieu
            break;
            
        case 'X':
            // Diagonale 1
            for (int i = 0; i < thickness; i++) {
                SDL_RenderLine(renderer, x + i, y, x + size + i, y + size);
            }
            // Diagonale 2
            for (int i = 0; i < thickness; i++) {
                SDL_RenderLine(renderer, x + size - i, y, x - i, y + size);
            }
            break;
            
        case 'I':
            drawThickHLine(x, x + size, y); // Haut
            drawThickVLine(x + size/2, y, y + size); // Milieu
            drawThickHLine(x, x + size, y + size); // Bas
            break;
            
        case 'E':
            drawThickVLine(x, y, y + size); // Gauche
            drawThickHLine(x, x + size, y); // Haut
            drawThickHLine(x, x + size, y + size/2); // Milieu
            drawThickHLine(x, x + size, y + size); // Bas
            break;
            
        case 'v':
        case 'V':
            SDL_RenderLine(renderer, x, y, x + size/2, y + size);
            SDL_RenderLine(renderer, x + size, y, x + size/2, y + size);
            break;
            
        case 'r':
        case 'R':
            drawThickVLine(x, y, y + size); // Gauche
            drawThickHLine(x, x + size, y); // Haut
            drawThickVLine(x + size, y, y + size/2); // Haut droite
            drawThickHLine(x, x + size, y + size/2); // Milieu
            SDL_RenderLine(renderer, x + size/2, y + size/2, x + size, y + size); // Diagonale
            break;
            
        case 'y':
        case 'Y':
            SDL_RenderLine(renderer, x, y, x + size/2, y + size/2);
            SDL_RenderLine(renderer, x + size, y, x + size/2, y + size/2);
            drawThickVLine(x + size/2, y + size/2, y + size);
            break;
            
        case 'd':
        case 'D':
            drawThickVLine(x, y, y + size); // Gauche
            drawThickHLine(x, x + size - size/4, y); // Haut
            drawThickVLine(x + size, y + size/4, y + size - size/4); // Droite arrondie
            drawThickHLine(x, x + size - size/4, y + size); // Bas
            break;
            
        case 'a':
            drawThickHLine(x, x + size, y + size/3); // Haut
            drawThickVLine(x, y + size/3, y + size); // Gauche
            drawThickVLine(x + size, y + size/3, y + size); // Droite
            drawThickHLine(x, x + size, y + size/2 + size/6); // Milieu
            drawThickHLine(x, x + size, y + size); // Bas
            break;
            
        case 'e':
            drawThickHLine(x, x + size, y + size/3); // Haut
            drawThickVLine(x, y + size/3, y + size); // Gauche
            drawThickHLine(x, x + size, y + size/2 + size/6); // Milieu
            drawThickHLine(x, x + size, y + size); // Bas
            break;
            
        case 'o':
            drawThickHLine(x, x + size, y + size/3); // Haut
            drawThickVLine(x, y + size/3, y + size); // Gauche
            drawThickVLine(x + size, y + size/3, y + size); // Droite
            drawThickHLine(x, x + size, y + size); // Bas
            break;
            
        case 'n':
            drawThickVLine(x, y + size/3, y + size); // Gauche
            drawThickVLine(x + size, y + size/3, y + size); // Droite
            drawThickHLine(x, x + size, y + size/2); // Milieu haut
            break;
    }
}

// ============================================================================
// Dessine du texte à l'écran avec des lettres stylisées
// ============================================================================
void SplashScreen::DrawText(const std::string& text, int y, int alpha, bool large)
{
    int letterSize = large ? 50 : 30;
    int letterSpacing = large ? 60 : 35;
    int thickness = large ? 5 : 3;
    
    int totalWidth = text.length() * letterSpacing;
    int startX = (WINDOW_WIDTH - totalWidth) / 2;
    
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, alpha);
    
    for (size_t i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ') continue;
        
        int x = startX + i * letterSpacing;
        DrawLetter(mRenderer, text[i], x, y, letterSize, thickness);
    }
}

// ============================================================================
// Dessine le logo complet "JUST MAX IT" + "Everyday"
// ============================================================================
void SplashScreen::DrawLogo(int alpha)
{
    // Fond noir
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
    
    unsigned long long currentTime = SDL_GetTicks();
    unsigned long long elapsed = currentTime - mStartTime;
    
    int alpha1 = alpha;
    int alpha2 = 0;
    
    if (elapsed > 1200)
    {
        unsigned long long alpha2Start = elapsed - 1200;
        if (alpha2Start < 800)
        {
            alpha2 = (int)((float)alpha2Start / 800.0f * alpha);
        }
        else
        {
            alpha2 = alpha;
        }
    }
    
    // Dessine "JUST MAX IT"
    DrawText("JUST MAX IT", WINDOW_HEIGHT / 2 - 60, alpha1, true);
    
    // Dessine "Everyday"
    if (alpha2 > 0)
    {
        DrawText("Everyday", WINDOW_HEIGHT / 2 + 40, alpha2, false);
    }
    
    // Effet de lueur
    if (alpha > 200)
    {
        SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 20);
        SDL_FRect glow = {
            80.0f,
            (float)(WINDOW_HEIGHT / 2 - 100),
            (float)(WINDOW_WIDTH - 160),
            220.0f
        };
        SDL_RenderRect(mRenderer, &glow);
    }
}

// ============================================================================
// Met à jour l'animation
// ============================================================================
void SplashScreen::Update()
{
    unsigned long long currentTime = SDL_GetTicks();
    unsigned long long elapsed = currentTime - mStartTime;
    
    if (elapsed >= TOTAL_DURATION)
    {
        mIsFinished = true;
    }
}

// ============================================================================
// Affiche l'animation
// ============================================================================
void SplashScreen::Render()
{
    unsigned long long currentTime = SDL_GetTicks();
    int alpha = CalculateAlpha(currentTime);
    DrawLogo(alpha);
}

// ============================================================================
// Vérifie si l'animation est terminée
// ============================================================================
bool SplashScreen::IsFinished() const
{
    return mIsFinished;
}