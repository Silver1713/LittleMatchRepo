#include "SageEditor.hpp"
#include "../../SageEngine/include/Game.hpp"
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <string>

#include "imgui_internal.h"
#include "SageFrameBuffer.hpp"
#include "SageRenderer.hpp"

static bool show_hierarchy_window = true;
static bool show_console_window = true;
static bool show_inspector_window = true;
static bool show_project_window = true;
static bool show_scene_window = true;
static bool show_game_window = true;
static bool exit_requested = true;
static bool show_assets_window = false;

namespace SageEditor
{
    ImGuiTextFilter     Filter;
    TreeNode* selected_node = NULL;
    TreeNode* DemoTree = NULL;
    GameObject* selectedObject = nullptr;
    static GameObject* rootGameObject = nullptr;
    static const ComponentInfo component_infos[]
    {
        { "Position",       ImGuiDataType_S32,    2 },
        { "Rotation",       ImGuiDataType_S32,     2 },
        { "Scale",          ImGuiDataType_Float,   2 },
        { "Colour",         ImGuiDataType_Float,   4 },
        { "Velocity",       ImGuiDataType_S32,   2 },
    };

    // Bool flags for the toggling of windows
    void Show_Hierarchy_Window(TreeNode* root) {
        if (show_hierarchy_window) {
            ImGui::Begin("Hierarchy");
            Hierarchy();
            /*if (ImGui::TreeNode("Parent 1"))
            {
                ImGui::Text("Child 1");
                ImGui::Text("Child 2");
                ImGui::TreePop();
            }*/
            /*if (ImGui::InputTextWithHint("##search", "search", Filter.InputBuf, IM_ARRAYSIZE(Filter.InputBuf))) {
                Filter.Build();
            }*/
            //Hierarchy(CreateTreeNode());
            //ImGui::Text("This is the Hierarchy window.");
            ImGui::End();
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
            Inspector();
            ImGui::End();
        }
    }

    //void Show_Project_Window()
    //{
    //    if (show_project_window)
    //    {
    //        ImGui::Begin("Project");
    //        ImGui::Columns(2, "project_columns", true); // Create 2 columns that are resizeable
    //        ImGui::BeginChild("FolderHierarchy", ImVec2(0, 0), true);
    //        // HARDCODING TEST LAYOUT
    //        if (ImGui::TreeNode("Assets"))
    //        {
       //         if (ImGui::TreeNode("Scenes"))
    //            {
    //                ImGui::TreeNodeEx("Main Scene", ImGuiTreeNodeFlags_Leaf);
    //                ImGui::TreePop();
       //         }
    //            if (ImGui::TreeNode("Scripts"))
    //            {
    //                ImGui::TreeNodeEx("PlayerController.cs", ImGuiTreeNodeFlags_Leaf);
    //                ImGui::TreePop();
    //            }
    //            ImGui::TreePop();
    //        }
    //        ImGui::EndChild(); // End left panel
    //        ImGui::NextColumn(); // Right column (Assets)
    //        ImGui::BeginChild("AssetView", ImVec2(0, 0), true);
    //        ImGui::Text("Assets");
    //        ImGui::EndGroup();
    //        ImGui::EndChild();
    //        ImGui::Columns(1);
    //        ImGui::End();
    //        //ImGui::Separator();
    //        ////ImGui::MenuItem("Assets", nullptr, &show_assets_window);
    //        ImGui::Text("This is the Project window.");
    //        ImGui::End();
    //    }
    //}

    void Show_Project_Window() {
        if (show_project_window) {
            ImGui::Begin("Project");

            // Split the window into two sections: folder structure (left) and asset view (right)
            ImGui::Columns(2, "project_columns", true);  // Create two columns, resizable

            // Left column: Folder hierarchy
            ImGui::BeginChild("FolderHierarchy", ImVec2(0, 0), true);

            // HARDCODING TESTING LAYOUT
            if (ImGui::TreeNode("Assets")) {
                if (ImGui::TreeNode("Scenes")) {
                    ImGui::Text("Main Scene");
                    ImGui::TreePop();  // Pop the "Scenes" node
                }

                if (ImGui::TreeNode("Scripts")) {
                    ImGui::Text("PlayerController.cs");
                    ImGui::TreePop();  // Pop the "Scripts" node
                }

                ImGui::TreePop();  // Pop the "Assets" node
            }

            ImGui::EndChild();  // End left panel (Folder Hierarchy)

            ImGui::NextColumn();  // Move to the next column

            // Right column: Asset view
            ImGui::BeginChild("AssetView", ImVec2(0, 0), true);

            ImGui::Text("Assets");  // Title
            ImGui::Separator();

            // Simulating asset grid or list (as icons)
            ImGui::BeginGroup();


            ImGui::EndGroup();

            ImGui::EndChild();  // End right panel (Asset View)

            ImGui::Columns(1);  // Reset columns

            ImGui::End();
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

    void CleanUpScene() {
        delete rootGameObject;
        rootGameObject = nullptr;
    }

    //Creates a node to a new GameObject in Hierarchy
    static TreeNode* CreateNode(const char* name, int uid, TreeNode* parent)
    {
        TreeNode* node = IM_NEW(TreeNode);
        snprintf(node->Name, IM_ARRAYSIZE(node->Name), "%s", name);
        node->UID = uid;
        node->Parent = parent;
        node->IndexInParent = parent ? (unsigned short)parent->Childs.Size : 0;
        if (parent)
            parent->Childs.push_back(node);
        return node;
    }

    //Creates the tree nodes containing GameObjects
    static TreeNode* CreateTreeNode()
    {
        //Hardcoded GameObject from example
        static const char* root_names[] = { "Empty GameObject" };
        const size_t NAME_MAX_LEN = sizeof(TreeNode::Name);
        char name_buf[NAME_MAX_LEN];
        int uid = 0;
        //ROOT of the tree
        TreeNode* node_L0 = CreateNode("<ROOT>", ++uid, NULL);
        snprintf(name_buf, IM_ARRAYSIZE(name_buf), "%s", root_names[0]);
        //Indepedent GameObject
        TreeNode* node_L1 = CreateNode(name_buf, ++uid, node_L0);
        //Tells it that it has data to be changed in Inspector
        node_L1->HasData = true;
        return node_L0;
    }

    //Draws the TreeNode within ImGui dockspace
    void DrawTreeNode(TreeNode* _node)
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::PushID(_node->UID);
        ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_None;
        tree_flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;    // Standard opening mode as we are likely to want to add selection afterwards
        tree_flags |= ImGuiTreeNodeFlags_NavLeftJumpsBackHere;                                  // Left arrow support
        if (_node == selected_node)
            tree_flags |= ImGuiTreeNodeFlags_Selected;
        if (_node->Childs.Size == 0)
            tree_flags |= ImGuiTreeNodeFlags_Leaf;
        if (_node->DataMyBool == false)
            ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
        bool node_open = ImGui::TreeNodeEx("", tree_flags, "%s", _node->Name);
        if (_node->DataMyBool == false)
            ImGui::PopStyleColor();
        if (ImGui::IsItemFocused())
            selected_node = _node;
        if (node_open)
        {
            for (TreeNode* child : _node->Childs)
                DrawTreeNode(child);
            ImGui::TreePop();
        }
        ImGui::PopID();
    }

    void CreateNewGameObject() {
        auto* newObject = new GameObject("New GameObject");
        rootGameObject->children.push_back(newObject); // Add to the root or the currently selected object if desired.
    }

    void DrawHierarchy(GameObject* object)
    {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        if (object->children.empty()) {
            flags |= ImGuiTreeNodeFlags_Leaf;
        }

        // Make the object selectable and update the selectedObject pointer when clicked
        bool nodeOpen = ImGui::TreeNodeEx(object->name.c_str(), flags, "%s", object->name.c_str());
        if (ImGui::IsItemClicked()) {
            selectedObject = object;
        }

        if (nodeOpen) {
            for (auto* child : object->children) {
                DrawHierarchy(child);
            }
            ImGui::TreePop();
        }
    }

    void Hierarchy()
    {
        if (ImGui::Button("Add GameObject")) {
            CreateNewGameObject();
        }

        DrawHierarchy(rootGameObject);
    }

//    //Drawing Hierarchy dockspace with parameter of the TreeNode
//    //Here you can see 3 examples of what is to be expected from manipulation of Hierarchy dockspace
//    void Hierarchy(TreeNode* _root_node)
//    {
//        static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
//
//        // - Currently using a table to benefit from RowBg feature
//        //Ctrl+F allows user to search GameObject
//        ImGui::SetNextItemWidth(-FLT_MIN);
//        ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F, ImGuiInputFlags_Tooltip);
//        ImGui::PushItemFlag(ImGuiItemFlags_NoNavDefaultFocus, true);
//        if (ImGui::Button("Add GameObject")) {
//            CreateNewGameObject();
//        }
//        if (ImGui::InputTextWithHint("##search", "search", Filter.InputBuf, IM_ARRAYSIZE(Filter.InputBuf), ImGuiInputTextFlags_EscapeClearsAll))
//            Filter.Build();
//        ImGui::PopItemFlag();
////#pragma region Visible Selection
////        // 'selection_mask' is dumb representation of what may be user-side selection state.
////        //  You may retain selection state inside or outside your objects in whatever format you see fit.
////        // 'node_clicked' is temporary storage of what node we have clicked to process selection at the end
////        /// of the loop. May be a pointer to your own node type, etc.
////
////        //This example shows the selectable nodes of GameObject but is not reflected onto the Inspector
////        static int selection_mask = (1 << 2);
////        int node_clicked = -1;
////        for (int i = 0; i < 6; i++)
////        {
////            // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
////            // To alter selection we use IsItemClicked() && !IsItemToggledOpen(), so clicking on an arrow doesn't alter selection.
////            ImGuiTreeNodeFlags node_flags = base_flags;
////            const bool is_selected = (selection_mask & (1 << i)) != 0;
////            if (is_selected)
////                node_flags |= ImGuiTreeNodeFlags_Selected;
////
////            // Items 3..5 are Tree Leaves
////            // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
////            // use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
////            node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
////            ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
////            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
////                node_clicked = i;
////            if (ImGui::BeginDragDropSource())
////            {
////                ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
////                ImGui::Text("This is a drag and drop source");
////                ImGui::EndDragDropSource();
////            }
////        }
////        if (node_clicked != -1)
////        {
////            // Update selection state
////            // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
////            if (ImGui::GetIO().KeyCtrl)
////                selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
////            else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
////                selection_mask = (1 << node_clicked);           // Click to single-select
////        }
////#pragma endregion
////
////#pragma region Inspector Properties
////        //This is the main example for changing of properties in Inspector when selecting a GameObject in Hierarchy
////        //Currently, it doesn't save the properties as there's no File I/O or Parser for data.
////        //Renaming in Inspector is not properly added as it doesn't update onto the Hierarchy
////        if (ImGui::BeginTable("##bg", 1, ImGuiTableFlags_RowBg))
////        {
////            for (TreeNode* node : _root_node->Childs)
////                if (Filter.PassFilter(node->Name)) // Filter root node
////                    DrawTreeNode(node);
////
////            // FIXME: there is temporary (usually single-frame) ID Conflict during reordering as a same item may be submitting twice.
////            // This code was always slightly faulty but in a way which was not easily noticeable.
////            // Until we fix this, enable ImGuiItemFlags_AllowDuplicateId to disable detecting the issue.
////            ImGui::PushItemFlag(ImGuiItemFlags_AllowDuplicateId, true);
////        }
////#pragma endregion
////
////#pragma region GameObject Reordering
////            //This example shows the reordering of GameObjects on the Hierarchy. Simple drag and drop.
////            //Hardcoded array of GameObjects
////            static const char* item_names[] = { "Empty GameObject 1", "Empty GameObject 2", "Empty GameObject 3" };
////            for (int n = 0; n < IM_ARRAYSIZE(item_names); n++)
////            {
////                const char* item = item_names[n];
////                ImGui::Selectable(item);
////
////                if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
////                {
////                    int n_next = n + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
////                    if (n_next >= 0 && n_next < IM_ARRAYSIZE(item_names))
////                    {
////                        item_names[n] = item_names[n_next];
////                        item_names[n_next] = item;
////                        ImGui::ResetMouseDragDelta();
////                    }
////                }
////            }
////            ImGui::PopItemFlag();
////            ImGui::EndTable();
////#pragma endregion
//    }

    ////Draws Inspector dockspace
    //void Inspector()
    //{
    //    // Right side: draw properties
    //    ImGui::BeginGroup();
    //    if (TreeNode* node = selected_node)
    //    {
    //        //This is how renaming works on the Inspector that is supposed to change in the Hierarchy.
    //        if (ImGui::InputText("###name", node->Name, IM_ARRAYSIZE(node->Name), ImGuiInputTextFlags_EnterReturnsTrue))
    //        {
    //            /*RenamingDoc = doc;
    //            RenamingStarted = true;*/
    //        }
    //        ImGui::Separator();
    //        if (ImGui::BeginTable("##properties", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
    //        {
    //            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
    //            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 2.0f); // Default twice larger
    //            if (node->HasData)
    //            {
    //                // In a typical application, the structure description would be derived from a data-driven system.
    //                // - We try to mimic this with our ExampleMemberInfo structure and the ExampleTreeNodeMemberInfos[] array.
    //                // - Limits and some details are hard-coded to simplify the demo.
    //                for (const ComponentInfo& field_desc : component_infos)
    //                {
    //                    ImGui::TableNextRow();
    //                    ImGui::PushID(field_desc.Name);
    //                    ImGui::TableNextColumn();
    //                    ImGui::AlignTextToFramePadding();
    //                    ImGui::TextUnformatted(field_desc.Name);
    //                    ImGui::TableNextColumn();
    //                    void* field_ptr = (void*)(((unsigned char*)node) + field_desc.Offset);
    //                    switch (field_desc.DataType)
    //                    {
    //                    case ImGuiDataType_Bool:
    //                    {
    //                        IM_ASSERT(field_desc.DataCount == 1);
    //                        ImGui::Checkbox("##Editor", (bool*)field_ptr);
    //                        break;
    //                    }
    //                    case ImGuiDataType_S32:
    //                    {
    //                        int v_min = INT_MIN, v_max = INT_MAX;
    //                        ImGui::SetNextItemWidth(-FLT_MIN);
    //                        ImGui::DragScalarN("##Editor", field_desc.DataType, field_ptr, field_desc.DataCount, 1.0f, &v_min, &v_max);
    //                        break;
    //                    }
    //                    case ImGuiDataType_Float:
    //                    {
    //                        float v_min = 0.0f, v_max = 1.0f;
    //                        ImGui::SetNextItemWidth(-FLT_MIN);
    //                        ImGui::SliderScalarN("##Editor", field_desc.DataType, field_ptr, field_desc.DataCount, &v_min, &v_max);
    //                        break;
    //                    }
    //                    }
    //                    ImGui::PopID();
    //                }
    //            }
    //            ImGui::EndTable();
    //        }
    //    }
    //    ImGui::EndGroup();
    //}

    void RenderInspectorWindow() {
        if (selectedObject) {
            // Display properties like name
            char nameBuffer[128];
            strcpy(nameBuffer, selectedObject->name.c_str());
            if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
                selectedObject->name = nameBuffer;
            }

            // Display components and allow adding new ones
            ImGui::Text("Components:");
            for (auto* component : selectedObject->components) {
                ImGui::Text("Component");
            }

            if (ImGui::Button("Add Component")) {
                ImGui::OpenPopup("AddComponentPopup");
            }

            if (ImGui::BeginPopup("AddComponentPopup")) {
                // Example: list of component types to add
                if (ImGui::MenuItem("Transform")) {
                    
                }
                if (ImGui::MenuItem("Mesh Renderer")) {
                    
                }
                ImGui::EndPopup();
            }
        }
        else {
            ImGui::Text("Select a GameObject to edit its properties");
        }
    }



    void RenderGUI()
    {
        ImGui::NewFrame();
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

        


        //if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        //{
        //    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        //    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        //    ImVec2 dockspace_size = ImGui::GetContentRegionAvail();
        //    //ImGui::DockSpaceOverViewport(dockspace_id, ImGui::GetMainViewport(), dockspace_flags);
        //    dockspace_size.y = 1440;
        //    std::cout << dockspace_size.x << " * " << dockspace_size.y << std::endl;
        //    //static bool first_time = true;
        //    //if (first_time)
        //    //{
        //    //    first_time = false;

        //    //    

        //    //    // Clear any previous layout
        //    //    ImGui::DockBuilderRemoveNode(dockspace_id); // Clear the node
        //    //    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace); // Re-add the dockspace node



        //    //    // Step 1: Split the dockspace into left (30%) and right (70%)
        //    //    ImGuiID dock_left_id{}, dock_middle_id{}, dock_right_id{};
        //    //    ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.5f, &dock_left_id, &dock_right_id);  // Left 30%, Right 70%
        //    //    
        //    //    //// Step 2: Split the right (70%) into middle (70%) and right (30%)
        //    //    //ImGui::DockBuilderSplitNode(dock_right_id, ImGuiDir_Right, 0.0f, &dock_right_id, &dock_middle_id);  // Right 30%, Middle 70%
        //    //    //
        //    //    //// Step 3: Split the left section into top (Hierarchy) and bottom (Project)
        //    //    //ImGuiID dock_left_top_id{}, dock_left_bottom_id{};
        //    //    //ImGui::DockBuilderSplitNode(dock_left_id, ImGuiDir_Down, 0.3f, &dock_left_bottom_id, &dock_left_top_id);  // Top 70%, Bottom 30%

        //    //    // Dock windows into their respective sections
        //    //    //ImGui::DockBuilderDockWindow("Hierarchy", dock_left_top_id);     // Top-left (Hierarchy)
        //    //    //ImGui::DockBuilderDockWindow("Project", dock_left_bottom_id);    // Bottom-left (Project)
        //    //    ImGui::DockBuilderDockWindow("Scene", dock_left_id);           // Middle (Scene)
        //    //    ImGui::DockBuilderDockWindow("Inspector", dock_right_id);        // Right (Inspector)

        //    //    // Finalize the layout
        //    //    ImGui::DockBuilderFinish(dockspace_id);

        //    //}
        //}

        // MAIN MENU BAR
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New"))
                {
                    // New scene
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
                    exit_requested = true;
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
                ImGui::MenuItem("Inspector", nullptr, &show_inspector_window);
                ImGui::MenuItem("Hierarchy", nullptr, &show_hierarchy_window);
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
        Show_Hierarchy_Window(CreateTreeNode());
        Show_Console_Window();
        Show_Project_Window();
        Show_Asset_Window();

        if (exit_requested)
        {
            // Call separate exit (in engine)
        }


        //#pragma region Settings
        //        ImGui::Begin("Settings");
        //        ImGui::Button("Hello");
        //        static float value = 0.0f;
        //        ImGui::DragFloat("Value", &value);
        //        ImGui::End();
        //#pragma endregion

        //#pragma region Hierarchy
        //        ImGui::Begin("Hierarchy");
        //        Hierarchy(CreateTreeNode());
        //        ImGui::End();
        //#pragma endregion

        //#pragma region Inspector
        //        ImGui::Begin("Inspector");
        //        //Inspector();
        //        ImGui::Text("Select an object to inspect.");
        //        ImGui::End();
        //#pragma endregion

        //#pragma region Scene
        //        ImGui::Begin("Scene");
        //        ImGui::End();
        //#pragma endregion

        //#pragma region Game
        //        ImGui::Begin("Game");
        //        ImGui::End();
        //#pragma endregion

        //#pragma region Project
        //        ImGui::Begin("Project");
        //        ImGui::End();
        //#pragma endregion

        //#pragma region Console
        //        ImGui::Begin("Console");
        //        ImGui::End();
        //#pragma endregion

                //ImGui End for Begin(DockSpace Demo), DON'T DELETE
        ImGui::End();

        ImGui::ShowDemoWindow();
    }


}
