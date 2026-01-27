// ============================================================================
// UI.cpp
// Implémentation de l'interface utilisateur avec ImGui
// Auteur: [Vivien Yann Nka]
// Date: Janvier 2026
// ============================================================================

#include "../include/UI.h"
#include "../include/SudokuGrid.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

// ============================================================================
// Constructeur
// ============================================================================
UI::UI() : mShowWinMessage(false), mStatusMessage(""), mMessageTime(0)
{
}

// ============================================================================
// Destructeur
// ============================================================================
UI::~UI()
{
}

// ============================================================================
// Initialise ImGui
// ============================================================================
void UI::Initialize(SDL_Window* window, SDL_Renderer* renderer)
{
    // Initialisation ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Navigation au clavier
    
    // Style sombre par défaut
    ImGui::StyleColorsDark();
    
    // Personnalisation du style
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.0f;
    style.FrameRounding = 3.0f;
    
    // Palette de couleurs personnalisée
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.12f, 0.95f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.30f, 0.50f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.30f, 0.40f, 0.60f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.40f, 0.70f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.50f, 0.80f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.35f, 0.65f, 1.00f);
    
    // Initialise ImGui pour SDL3
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

// ============================================================================
// Ferme ImGui
// ============================================================================
void UI::Shutdown()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

// ============================================================================
// Démarre une nouvelle frame ImGui
// ============================================================================
void UI::NewFrame()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

// ============================================================================
// Affiche le rendu ImGui
// ============================================================================
void UI::Render()
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), nullptr);
}

// ============================================================================
// Dessine le menu principal
// ============================================================================
void UI::DrawMainMenu(SudokuGrid* grid)
{
    // Position et taille de la fenêtre
    ImGui::SetNextWindowPos(ImVec2(550.0f, 80.0f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(230.0f, 420.0f), ImGuiCond_FirstUseEver);
    
    ImGui::Begin("Menu Principal", nullptr, ImGuiWindowFlags_NoCollapse);
    
    // Titre
    ImGui::TextColored(ImVec4(0.4f, 0.7f, 1.0f, 1.0f), "SUDOKU");
    ImGui::Text("Just Max It");
    ImGui::Separator();
    ImGui::Spacing();
    
    // Section Contrôles
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.6f, 1.0f), "Controles");
    ImGui::Spacing();
    
    // Bouton Nouvelle Grille
    if (ImGui::Button("Nouvelle Grille", ImVec2(-1.0f, 40.0f)))
    {
        grid->Initialize();
        mShowWinMessage = false;
        ShowMessage("Nouvelle grille !");
    }
    
    ImGui::Spacing();
    
    // Bouton Réinitialiser
    if (ImGui::Button("Reinitialiser", ImVec2(-1.0f, 40.0f)))
    {
        grid->Clear();
        grid->Initialize();
        mShowWinMessage = false;
        ShowMessage("Reinitialise !");
    }
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    // Section Comment jouer
    ImGui::TextColored(ImVec4(0.6f, 1.0f, 0.6f, 1.0f), "Comment jouer");
    ImGui::Spacing();
    
    ImGui::BulletText("Clic sur case vide");
    ImGui::BulletText("Tape 1-9");
    ImGui::BulletText("Retour = effacer");
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    // Section Règles
    ImGui::TextColored(ImVec4(1.0f, 0.6f, 0.6f, 1.0f), "Regles");
    ImGui::Spacing();
    
    ImGui::TextWrapped("Chaque ligne, colonne et carre 3x3 : chiffres 1-9 une fois.");
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    // Légende des couleurs
    ImGui::BulletText("Noir = Cases fixes");
    ImGui::BulletText("Bleu = Tes chiffres");
    
    ImGui::End();
}

// ============================================================================
// Dessine la barre de statut
// ============================================================================
void UI::DrawStatusBar(SudokuGrid* grid)
{
    // Position et taille fixes
    ImGui::SetNextWindowPos(ImVec2(100.0f, 550.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(450.0f, 80.0f), ImGuiCond_Always);
    
    ImGui::Begin("##StatusBar", nullptr, 
                 ImGuiWindowFlags_NoTitleBar | 
                 ImGuiWindowFlags_NoResize | 
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar);
    
    ImGui::Spacing();
    
    const unsigned long long MESSAGE_DURATION = 3000; // 3 secondes
    bool hasTemporaryMessage = false;
    
    // Affiche le message temporaire s'il existe
    if (!mStatusMessage.empty())
    {
        unsigned long long currentTime = SDL_GetTicks();
        if (currentTime - mMessageTime < MESSAGE_DURATION)
        {
            hasTemporaryMessage = true;
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.2f, 1.0f));
            ImGui::TextWrapped("%s", mStatusMessage.c_str());
            ImGui::PopStyleColor();
        }
        else
        {
            mStatusMessage.clear();
        }
    }
    
    // Affiche le message par défaut si pas de message temporaire
    if (!hasTemporaryMessage)
    {
        // Vérifie si le joueur a gagné
        if (grid->CheckWin())
        {
            if (!mShowWinMessage)
            {
                mShowWinMessage = true;
            }
            
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.2f, 1.0f, 0.2f, 1.0f));
            ImGui::TextWrapped("FELICITATIONS ! Grille complete !");
            ImGui::PopStyleColor();
            ImGui::Spacing();
            ImGui::Text("Nouvelle Grille pour rejouer");
        }
        else
        {
            // Instructions par défaut
            ImGui::Text("Clic case, tape 1-9");
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), 
                              "Retour=effacer | N=nouvelle");
        }
    }
    
    ImGui::End();
}

// ============================================================================
// Affiche un message temporaire
// ============================================================================
void UI::ShowMessage(const std::string& message)
{
    mStatusMessage = message;
    mMessageTime = SDL_GetTicks();
}

// ============================================================================
// Vérifie si ImGui capture la souris
// ============================================================================
bool UI::WantsMouseCapture() const
{
    return ImGui::GetIO().WantCaptureMouse;
}

// ============================================================================
// Vérifie si ImGui capture le clavier
// ============================================================================
bool UI::WantsKeyboardCapture() const
{
    return ImGui::GetIO().WantCaptureKeyboard;
}