#include "EditorStateManager.hpp"

std::vector<GameObject*> EditorStateManager::selected_objects{};
bool EditorStateManager::isPlaying = false;
bool EditorStateManager::isPaused = false;

std::vector<GameObject*>& EditorStateManager::Get_Selected_Objects()
{
	return selected_objects;
}


GameObject* EditorStateManager::Get_Selection()
{
	if (selected_objects.size() == 0)
	{
		return nullptr;
	}
	return selected_objects[0];
}


void EditorStateManager::Add_Selected_Object(GameObject* _object)
{
	selected_objects.push_back(_object);
}


void EditorStateManager::Clear_Selected_Objects()
{
	selected_objects.clear();
}



void EditorStateManager::Select_Object(GameObject* _object)
{
	Clear_Selected_Objects();
	Add_Selected_Object(_object);
}
