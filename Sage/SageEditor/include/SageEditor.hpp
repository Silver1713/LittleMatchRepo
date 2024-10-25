#pragma once
#include "imgui.h"
#include <limits.h>
#include <cstdio>
#include "imgui_impl_opengl3.h"
#include "GameObjects.hpp"
#include "AssetLoader.hpp"
namespace SageEditor
{
//-----------------------------------------------------------------------------
// [SECTION] Helpers: ExampleTreeNode, ExampleMemberInfo (for use by Property Editor etc.)
//-----------------------------------------------------------------------------

// Simple representation for a tree
// (this is designed to be simple to understand for our demos, not to be fancy or efficient etc.)
    struct TreeNode
    {
        // Tree structure
        char                        Name[64] = "";
        int                         UID = 0;
        TreeNode*                   Parent = NULL;
        ImVector<TreeNode*>         Childs;
        unsigned short              IndexInParent = 0;  // Maintaining this allows us to implement linear traversal more easily

        // Leaf Data
        bool                        HasData = false;    // All leaves have data
        bool                        DataMyBool = true;
        int                         DataMyInt = 128;
        ImVec2                      DataMyVec2 = ImVec2(0.0f, 3.141592f);
    };

    // Simple representation of struct metadata/serialization data.
    // (this is a minimal version of what a typical advanced application may provide)
    struct ComponentInfo
    {
        const char*     Name;       // Member name
        ImGuiDataType   DataType;   // Member type
        int             DataCount;  // Member count (1 when scalar)
        int             Offset;     // Offset inside parent structure
    };

    class GameObject
    {
    public:
        std::string name;
        std::vector<GameObject*> children;
        std::vector<Component*> components;

        GameObject(const std::string& name) : name(name) {}

        void AddComponent(Component* component)
        {
            components.push_back(component);
        }

        ~GameObject()
        {
            // Clean up dynamically allocated children and components
            for (auto* child : children) {
                delete child;
            }
            for (auto* component : components) {
                delete component;
            }
        }
    };

    GameObject* GetRootGameObject();
    void CleanUpScene();
    static TreeNode* CreateNode(const char* name, int uid, TreeNode* parent);
    static TreeNode* CreateTreeNode();
    void DrawTreeNode(TreeNode* node);
    void Hierarchy();
    //void Hierarchy(TreeNode* root_node);
    void Inspector();
    void RenderGUI();
}