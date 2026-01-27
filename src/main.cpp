// ============================================================================
// main.cpp
// Point d'entrée du programme
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#include "../include/Game.h"
#include <iostream>

int main(int argc, char* argv[])
{
    // Évite les warnings sur les paramètres inutilisés
    (void)argc;
    (void)argv;
    
    // Création de l'instance du jeu
    Game game;
    
    // Initialisation du jeu
    if (!game.Initialize())
    {
        std::cerr << "Echec initialisation du jeu" << std::endl;
        return 1;
    }
    
    // Lancement de la boucle de jeu
    game.Run();
    
    // Fermeture propre
    game.Shutdown();
    
    std::cout << "Merci d'avoir joue !" << std::endl;
    
    return 0;
}