#include "SageUIEditor.hpp"
#include "../../SageEngine/include/Game.hpp"
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <string>

#include "SageEditor.hpp"
#include "imgui_internal.h"
#include "EditorStateManager.hpp"
#include "GameObjects.hpp"
#include "SageHierarchy.hpp"
#include "SageFrameBuffer.hpp"
#include "SageRenderer.hpp"
#include "SageInspector.hpp"
#include "SageProject.hpp"
#include "SceneManager.hpp"

static bool show_hierarchy_window = true;
static bool show_console_window = true;
static bool show_inspector_window = true;
static bool show_project_window = true;
static bool show_scene_window = true;
static bool show_game_window = true;
static bool exit_requested = true;
static bool show_assets_window = false;

namespace SageUIEditor
{
    ImGuiTextFilter     Filter;

    // Bool flags for the toggling of windows
    void Show_Hierarchy_Window() {
        if (show_hierarchy_window) {
            ImGui::Begin("Hierarchy");
            // Call your hierarchy drawing function
            SageHierarchy::Hierarchy(); // Render the actual hierarchy nodes
            ImGui::End(); // End the main window
        }
    }

    void Show_Console_Window()
    {
        if (show_console_window)
        {
            ImGui::Begin("Console");
            ImGui::Text("This is the Console window.");
            ImGui::End();
        }
    }

    void Show_Inspector_Window()
    {
        if (show_inspector_window)
        {
            ImGui::Begin("Inspector");
            if (SageHierarchy::selected_object != nullptr)
            {
                EditorStateManager::Select_Object(SageHierarchy::selected_object);
                Sage_Inspector::Show_Inspector(SageHierarchy::selected_object);
            }
            ImGui::Text("This is the Inspector window.");
            ImGui::End();
        }
    }

    void Show_Project_Window() {
        if (show_project_window) {
            Sage_Project::Initialize("../SageEditor/client");
            Sage_Project::Show();
        }
    }

    void Show_Scene_Window()
    {
        if (show_scene_window)
        {
            ImGui::Begin("Scene");
            ImGui::Image(SageRenderer::Get_FrameBuffer()->Get_Color_Buffer_Handle(), { 1920,1080 }, { 0,1 }, { 1,0 });
            
            ImGui::End();
        }
    }

    void Show_Game_Window()
    {
        if (show_game_window)
        {
            ImGui::Begin("Game");
            ImGui::Text("This is the Game window.");
            ImGui::End();
        }
    }

    void Show_Asset_Window()
    {
        if (show_assets_window)
        {
            ImGui::Begin("Assets:");
            ImGui::Text("This is the assets window.");
            ImGui::End();
        }
    }

    void RenderGUI()
    {
        //ImGui::NewFrame();
        // DOCKSPACE

        // READ THIS !!!
        // TL;DR; this demo is more complicated than what most users you would normally use.
        // If we remove all options we are showcasing, this demo would become:
        //     void ShowExampleAppDockSpace()
        //     {
        //         ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
        //     }
        // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
        // In this specific demo, we are not using DockSpaceOverViewport() because:
        // - (1) we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
        // - (2) we allow the host window to have padding (when opt_padding == true)
        // - (3) we expose many flags and need a way to have them visible.
        // - (4) we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport()
        //      in your code, but we don't here because we allow the window to be floating)

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        
        
        // Fullscreen window setup
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        // Begin the dockspace window
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);

        // Pop the style vars that were pushed for fullscreen mode
        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        if (!opt_padding)
            ImGui::PopStyleVar();

        // Submit the DockSpace
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        // MAIN MENU BAR
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New"))
                {
                    //std::string editor_startup_scene = "main_menu";
                    SM::Set_Current_Level("default");
                    SM::Go_To_Next_Scene();
                    SageHierarchy::Update_Hierarchy();
                }
                if (ImGui::MenuItem("Open", "Ctrl+O"))
                {
                    // To open scene
                }
                if (ImGui::MenuItem("Save", "Ctrl+S"))
                {
                    // To save scene
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit"))
                {
                    std::exit(0);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z"))
                {
                    // Undo Action
                }
                if (ImGui::MenuItem("Redo", "Ctrl+Y"))
                {
                    // Redo Action
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Settings"))
                {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Assets"))
            {
                if (ImGui::MenuItem("Create"))
                {
                    // Create new assets;
                }
                if (ImGui::MenuItem("Import New Asset"))
                {
                    // Import new assets
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("GameObject"))
            {
                if (ImGui::MenuItem("Create Empty"))
                {
                    // Create empty game object
                }
                if (ImGui::MenuItem("2D Object"))
                {
                    // Create 2D objects such as sprite UI elements etc
                }
                if (ImGui::MenuItem("Audio"))
                {
                    // Create audio sources
                }
                if (ImGui::MenuItem("Camera"))
                {
                    // Add camera to scene
                }
                if (ImGui::MenuItem("Effect"))
                {
                    // Add particle systems
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Component"))
            {
                if (ImGui::MenuItem("Physics 2D"))
                {
                    // rigidbodies 2d
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Audio"))
                {
                    // Add audio component to game object?
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Scripts"))
                {
                    // Attach scripts that contain custom functionality
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Window"))
            {
                ImGui::MenuItem("Scene", nullptr, &show_scene_window);
                ImGui::MenuItem("Hierarchy", nullptr, &show_hierarchy_window);
                ImGui::MenuItem("Inspector", nullptr, &show_inspector_window);
                ImGui::MenuItem("Game", nullptr, &show_game_window);
                ImGui::MenuItem("Console", nullptr, &show_console_window);
                ImGui::MenuItem("Project", nullptr, &show_project_window);

                ImGui::EndMenu();
            }
            // ADD MORE FOR MAIN MENU
            ImGui::EndMainMenuBar();
        }

        Show_Scene_Window();
        Show_Game_Window();
        Show_Inspector_Window();
        Show_Hierarchy_Window();
        Show_Console_Window();
        Show_Project_Window();
        Show_Asset_Window();

        if (exit_requested)
        {
            // Call separate exit (in engine)
        }

        //ImGui End for Begin(DockSpace Demo), DON'T DELETE
        ImGui::End();

        ImGui::ShowDemoWindow();
    }


    namespace IMGUI_Elements
    {
		IMGUI_Vector2::IMGUI_Vector2(float* _value) : active(false), hovered(false), onChanged(false), onClick(false)
	   {
           
           onChanged = ImGui::InputFloat2("##Vector2", _value);
           active = ImGui::IsItemActive();
           hovered = ImGui::IsItemHovered();
           onClick = ImGui::IsItemClicked();
          
	   }


    }


}
