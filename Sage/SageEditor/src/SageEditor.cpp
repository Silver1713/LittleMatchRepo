#include "SageEditor.hpp"
#include "../../SageEngine/include/Game.hpp"
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <string>

namespace SageEditor
{
    ImGuiTextFilter     Filter;
    TreeNode*           selected_node = NULL;
    TreeNode*           DemoTree = NULL;
    static const ComponentInfo component_infos[]
    {
        { "MyBool",     ImGuiDataType_Bool,    1, offsetof(TreeNode, DataMyBool) },
        { "MyInt",      ImGuiDataType_S32,     1, offsetof(TreeNode, DataMyInt) },
        { "MyVec2",     ImGuiDataType_Float,   2, offsetof(TreeNode, DataMyVec2) },
    };


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
            tree_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet;
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

    //Drawing Hierarchy dockspace with parameter of the TreeNode
    //Here you can see 3 examples of what is to be expected from manipulation of Hierarchy dockspace
    void Hierarchy(TreeNode* _root_node)
    {
        static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

        // - Currently using a table to benefit from RowBg feature
        //Ctrl+F allows user to search GameObject
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F, ImGuiInputFlags_Tooltip);
        ImGui::PushItemFlag(ImGuiItemFlags_NoNavDefaultFocus, true);
        if (ImGui::InputTextWithHint("##search", "search", Filter.InputBuf, IM_ARRAYSIZE(Filter.InputBuf), ImGuiInputTextFlags_EscapeClearsAll))
            Filter.Build();
        ImGui::PopItemFlag();

#pragma region Visible Selection
        // 'selection_mask' is dumb representation of what may be user-side selection state.
        //  You may retain selection state inside or outside your objects in whatever format you see fit.
        // 'node_clicked' is temporary storage of what node we have clicked to process selection at the end
        /// of the loop. May be a pointer to your own node type, etc.

        //This example shows the selectable nodes of GameObject but is not reflected onto the Inspector
        static int selection_mask = (1 << 2);
        int node_clicked = -1;
        for (int i = 0; i < 6; i++)
        {
            // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
            // To alter selection we use IsItemClicked() && !IsItemToggledOpen(), so clicking on an arrow doesn't alter selection.
            ImGuiTreeNodeFlags node_flags = base_flags;
            const bool is_selected = (selection_mask & (1 << i)) != 0;
            if (is_selected)
                node_flags |= ImGuiTreeNodeFlags_Selected;

            // Items 3..5 are Tree Leaves
            // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
            // use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
            node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
            ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                node_clicked = i;
            if (ImGui::BeginDragDropSource())
            {
                ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                ImGui::Text("This is a drag and drop source");
                ImGui::EndDragDropSource();
            }
        }
        if (node_clicked != -1)
        {
            // Update selection state
            // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
            if (ImGui::GetIO().KeyCtrl)
                selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
            else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
                selection_mask = (1 << node_clicked);           // Click to single-select
        }
#pragma endregion

#pragma region Inspector Properties
        //This is the main example for changing of properties in Inspector when selecting a GameObject in Hierarchy
        //Currently, it doesn't save the properties as there's no File I/O or Parser for data.
        //Renaming in Inspector is not properly added as it doesn't update onto the Hierarchy
        if (ImGui::BeginTable("##bg", 1, ImGuiTableFlags_RowBg))
        {
            for (TreeNode* node : _root_node->Childs)
                if (Filter.PassFilter(node->Name)) // Filter root node
                    DrawTreeNode(node);

            // FIXME: there is temporary (usually single-frame) ID Conflict during reordering as a same item may be submitting twice.
            // This code was always slightly faulty but in a way which was not easily noticeable.
            // Until we fix this, enable ImGuiItemFlags_AllowDuplicateId to disable detecting the issue.
            ImGui::PushItemFlag(ImGuiItemFlags_AllowDuplicateId, true);
#pragma endregion

#pragma region GameObject Reordering
            //This example shows the reordering of GameObjects on the Hierarchy. Simple drag and drop.
            //Hardcoded array of GameObjects
            static const char* item_names[] = { "Empty GameObject 1", "Empty GameObject 2", "Empty GameObject 3" };
            for (int n = 0; n < IM_ARRAYSIZE(item_names); n++)
            {
                const char* item = item_names[n];
                ImGui::Selectable(item);

                if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
                {
                    int n_next = n + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
                    if (n_next >= 0 && n_next < IM_ARRAYSIZE(item_names))
                    {
                        item_names[n] = item_names[n_next];
                        item_names[n_next] = item;
                        ImGui::ResetMouseDragDelta();
                    }
                }
            }
            ImGui::PopItemFlag();
            ImGui::EndTable();
#pragma endregion
        }
    }

    //Draws Inspector dockspace
    void Inspector()
    {
        // Right side: draw properties
        ImGui::BeginGroup();
        if (TreeNode* node = selected_node)
        {
            //This is how renaming works on the Inspector that is supposed to change in the Hierarchy.
            if (ImGui::InputText("###name", node->Name, IM_ARRAYSIZE(node->Name), ImGuiInputTextFlags_EnterReturnsTrue))
            {
                /*RenamingDoc = doc;
                RenamingStarted = true;*/
            }

            ImGui::Separator();
            if (ImGui::BeginTable("##properties", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
            {
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 2.0f); // Default twice larger
                if (node->HasData)
                {
                    // In a typical application, the structure description would be derived from a data-driven system.
                    // - We try to mimic this with our ExampleMemberInfo structure and the ExampleTreeNodeMemberInfos[] array.
                    // - Limits and some details are hard-coded to simplify the demo.
                    for (const ComponentInfo& field_desc : component_infos)
                    {
                        ImGui::TableNextRow();
                        ImGui::PushID(field_desc.Name);
                        ImGui::TableNextColumn();
                        ImGui::AlignTextToFramePadding();
                        ImGui::TextUnformatted(field_desc.Name);
                        ImGui::TableNextColumn();
                        void* field_ptr = (void*)(((unsigned char*)node) + field_desc.Offset);
                        switch (field_desc.DataType)
                        {
                        case ImGuiDataType_Bool:
                        {
                            IM_ASSERT(field_desc.DataCount == 1);
                            ImGui::Checkbox("##Editor", (bool*)field_ptr);
                            break;
                        }
                        case ImGuiDataType_S32:
                        {
                            int v_min = INT_MIN, v_max = INT_MAX;
                            ImGui::SetNextItemWidth(-FLT_MIN);
                            ImGui::DragScalarN("##Editor", field_desc.DataType, field_ptr, field_desc.DataCount, 1.0f, &v_min, &v_max);
                            break;
                        }
                        case ImGuiDataType_Float:
                        {
                            float v_min = 0.0f, v_max = 1.0f;
                            ImGui::SetNextItemWidth(-FLT_MIN);
                            ImGui::SliderScalarN("##Editor", field_desc.DataType, field_ptr, field_desc.DataCount, &v_min, &v_max);
                            break;
                        }
                        }
                        ImGui::PopID();
                    }
                }
                ImGui::EndTable();
            }
        }
        ImGui::EndGroup();
    }

	void RenderGUI()
    {
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

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
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
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        ImGui::PopStyleVar(2);
        if (!opt_padding)
            ImGui::PopStyleVar();

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }



#pragma region Hierarchy
        ImGui::Begin("Hierarchy");
        Hierarchy(CreateTreeNode());
        ImGui::End();
#pragma endregion

#pragma region Inspector
        ImGui::Begin("Inspector");
        Inspector();
        ImGui::End();
#pragma endregion

#pragma region Scene
        ImGui::Begin("Scene");
        ImGui::End();
#pragma endregion

#pragma region Game
        ImGui::Begin("Game");
        ImGui::End();
#pragma endregion

#pragma region Project
        ImGui::Begin("Project");
        ImGui::End();
#pragma endregion

#pragma region Console
        ImGui::Begin("Console");
        ImGui::End();
#pragma endregion

        //ImGui End for Begin(DockSpace Demo), DON'T DELETE
        ImGui::End();

        ImGui::ShowDemoWindow();
    }
}
