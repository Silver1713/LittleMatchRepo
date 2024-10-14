#pragma once
#include "imgui.h"

namespace SageEditor
{
    //-----------------------------------------------------------------------------
// [SECTION] Helpers: ExampleTreeNode, ExampleMemberInfo (for use by Property Editor etc.)
//-----------------------------------------------------------------------------

// Simple representation for a tree
// (this is designed to be simple to understand for our demos, not to be fancy or efficient etc.)
    struct ExampleTreeNode
    {
        // Tree structure
        char                        Name[28] = "";
        int                         UID = 0;
        ExampleTreeNode* Parent = NULL;
        ImVector<ExampleTreeNode*>  Childs;
        unsigned short              IndexInParent = 0;  // Maintaining this allows us to implement linear traversal more easily

        // Leaf Data
        bool                        HasData = false;    // All leaves have data
        bool                        DataMyBool = true;
        int                         DataMyInt = 128;
        ImVec2                      DataMyVec2 = ImVec2(0.0f, 3.141592f);
    };

    // Simple representation of struct metadata/serialization data.
    // (this is a minimal version of what a typical advanced application may provide)
    struct ExampleMemberInfo
    {
        const char* Name;       // Member name
        ImGuiDataType   DataType;   // Member type
        int             DataCount;  // Member count (1 when scalar)
        int             Offset;     // Offset inside parent structure
    };

    //// Metadata description of ExampleTreeNode struct.
    //static const ExampleMemberInfo ExampleTreeNodeMemberInfos[]
    //{
    //    { "MyBool",     ImGuiDataType_Bool,    1, offsetof(ExampleTreeNode, DataMyBool) },
    //    { "MyInt",      ImGuiDataType_S32,     1, offsetof(ExampleTreeNode, DataMyInt) },
    //    { "MyVec2",     ImGuiDataType_Float,   2, offsetof(ExampleTreeNode, DataMyVec2) },
    //};

    //static ExampleTreeNode* ExampleTree_CreateNode(const char* name, int uid, ExampleTreeNode* parent)
    //{
    //    ExampleTreeNode* node = IM_NEW(ExampleTreeNode);
    //    snprintf(node->Name, IM_ARRAYSIZE(node->Name), "%s", name);
    //    node->UID = uid;
    //    node->Parent = parent;
    //    node->IndexInParent = parent ? (unsigned short)parent->Childs.Size : 0;
    //    if (parent)
    //        parent->Childs.push_back(node);
    //    return node;
    //}

    void Draw(ExampleTreeNode* root_node);
    void DrawTreeNode(ExampleTreeNode* node);
    void RenderGUI();
}