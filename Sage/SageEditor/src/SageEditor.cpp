#include "SageEditor.h"

#include "SageEngine.hpp"
#include "SageHierarchy.hpp"
#include "SageUIEditor.hpp"
#include "SceneManager.hpp"

void SageEditor::sage_editor_play()
{
	SageEngine::Input();
	SageEngine::Update();
	
	// selected obj to null
}

void SageEditor::sage_editor_stop()
{
	SageUIEditor::pause_select = false;

	SM::Set_Current_Level("level_1");
	SM::Go_To_Next_Scene();

	SageHierarchy::Update_Hierarchy();
}

