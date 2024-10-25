#include "SageHierarchy.hpp"

namespace SageHierarchy
{
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
}