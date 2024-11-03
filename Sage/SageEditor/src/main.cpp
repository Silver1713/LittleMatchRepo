// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include <backward.hpp>
#include "SageUIEditor.hpp"
#include "SageHierarchy.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include "EditorStateManager.hpp"
#include "GameObjects.hpp"

#include "KeyInputs.h"
#include "SageEditor.h"
#include "SageTimer.hpp"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#define ENABLE_NVIDIA_OPTIMUS 1

#if ENABLE_NVIDIA_OPTIMUS == 1
extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif


#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// TESTING PURPOSES
#include "SageEngine.hpp"
#include "SageHelper.hpp"
#include "SageWindow.hpp"
#include "SceneManager.hpp"
constexpr double physics_update_target = 0.02;

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif
const std::string editor_window_config_path = "../SageEditor/data/configuration/project_config.json";



namespace
{
    static double accumulator = 0;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Forward declaration
int init();
void update();
void draw();
void exit();

// Create window with graphics context
GLFWwindow* window;
SageWindow* window_self;
ImVec4 clear_color;


// Main code
namespace Sage_Editor_Main
{
	
}
int main(int, char**)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	SageEngine::Init(editor_window_config_path.c_str());
	init();
    
    // Main loop

    while (!glfwWindowShouldClose(window))
    {
        /// KEEP LOOPING
        update();
        
		
        draw();
        if (SageUIEditor::is_playing && SageUIEditor::play_select)
        {
            SageEditor::sage_editor_play();
        }
        if (SageUIEditor::pause_select)
        {
            SageEditor::sage_editor_stop();
        }

		SageEngine::Draw(true);

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }
    exit();


    // Cleanup
    ImGui::EndFrame();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

int init()
{
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 450";

    // Create window with graphics context
	
    window = glfwGetCurrentContext();
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    
    ImGuiIO& io = ImGui::GetIO();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Enable docking (this should be done once, in initialization, not per frame)
    
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable docking globally
    io.IniFilename = "../SageEditor/config/custom_layout.ini";  // Use custom ini file for storing layout
    io.LogFilename = "../SageEditor/config/custom_layout_log.txt";
    ImGui::LoadIniSettingsFromDisk(io.IniFilename);

    SageHierarchy::Update_Hierarchy();
    return 0;
}

void update()
{
    if (SageHierarchy::scene_change)
    {
	    if (!SM::Get_Is_Restarting())
	    {
            SageHierarchy::selected_object = nullptr;
	    }
    }
    SageHierarchy::Update_Hierarchy();
    
    // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.

    //ImGuiIO& io = ImGui::GetIO();

	SAGEInputHandler::update();

    if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
    {
        ImGui_ImplGlfw_Sleep(10);
        return;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    //ImGui::NewFrame();
}

void draw()
{
    //[HALIS] [HUI ZONG]
    SageUIEditor::RenderGUI();

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void exit()
{
    //SageEditor::CleanUpScene();
}
