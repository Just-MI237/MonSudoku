#!/usr/bin/env python3
# ============================================================================
# build.py
# Script de compilation automatique pour le projet Sudoku
# Auteur: [Vivien Yann Nka]
# Date: Janvier 2026
# ============================================================================

import os
import subprocess
import sys

def CollectSources():
    """Collecte tous les fichiers source .cpp du projet"""
    sources = []
    
    # Collecte les fichiers dans src/
    if os.path.exists("src"):
        for root, dirs, files in os.walk("src"):
            for file in files:
                if file.endswith(".cpp"):
                    sources.append(os.path.join(root, file))
    
    # Collecte les fichiers ImGui
    imgui_path = "thirdparty/imgui"
    if os.path.exists(imgui_path):
        # Fichiers principaux d'ImGui
        for f in ["imgui.cpp", "imgui_draw.cpp", "imgui_tables.cpp", 
                  "imgui_widgets.cpp", "imgui_demo.cpp"]:
            sources.append(os.path.join(imgui_path, f))
        
        # Backends SDL3 pour ImGui
        for f in ["imgui_impl_sdl3.cpp", "imgui_impl_sdlrenderer3.cpp"]:
            sources.append(os.path.join(imgui_path, "backends", f))
    
    return sources

def Build():
    """Compile le projet"""
    print("=" * 50)
    print("COMPILATION SUDOKU - Just Max It, Everyday")
    print("=" * 50)
    
    # Collecte les fichiers source
    sources = CollectSources()
    if not sources:
        print("ERREUR: Aucun fichier source trouve")
        return False
    
    print(f"\nFichiers a compiler: {len(sources)}")
    
    # Récupère les flags de compilation SDL3
    try:
        sdl_cflags = subprocess.check_output(
            ["pkg-config", "sdl3", "--cflags"],
            text=True
        ).strip().split()
        
        sdl_libs = subprocess.check_output(
            ["pkg-config", "sdl3", "--libs"],
            text=True
        ).strip().split()
    except subprocess.CalledProcessError:
        print("ERREUR: SDL3 non trouve via pkg-config")
        return False
    except FileNotFoundError:
        print("ERREUR: pkg-config non trouve")
        return False
    
    # Construit la commande de compilation
    cmd = [
        "clang++",                          # Compilateur
        "-std=c++17",                       # Standard C++17
        "-Wall",                            # Tous les warnings
        "-Wextra",                          # Warnings supplémentaires
        "-Wno-unused-parameter",            # Ignore les paramètres non utilisés
        "-g",                               # Symboles de débogage
        "-Iinclude",                        # Dossier des headers du projet
        "-Ithirdparty/imgui",               # Dossier ImGui
        "-Ithirdparty/imgui/backends"       # Dossier backends ImGui
    ]
    
    # Ajoute les flags SDL3
    cmd.extend(sdl_cflags)
    
    # Ajoute tous les fichiers source
    cmd.extend(sources)
    
    # Ajoute les bibliothèques SDL3
    cmd.extend(sdl_libs)
    
    # Nom de l'exécutable final
    cmd.extend(["-o", "sudoku"])
    
    # Affiche la commande (pour débogage)
    print("\nCommande de compilation:")
    print(" ".join(cmd))
    print()
    
    # Lance la compilation
    result = subprocess.run(cmd)
    
    if result.returncode == 0:
        print("\n" + "=" * 50)
        print("COMPILATION REUSSIE !")
        print("=" * 50)
        print("\nPour lancer le jeu, tape:")
        print("  ./sudoku")
        return True
    else:
        print("\n" + "=" * 50)
        print("ERREUR DE COMPILATION")
        print("=" * 50)
        return False

if __name__ == "__main__":
    # Lance la compilation et retourne le code d'erreur approprié
    sys.exit(0 if Build() else 1)