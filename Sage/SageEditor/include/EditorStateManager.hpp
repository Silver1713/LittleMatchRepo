#ifndef EDITOR_STATE_MANAGER_HPP
#define EDITOR_STATE_MANAGER_HPP
#include <vector>

class GameObject;

struct EditorStateManager
{
	static std::vector<GameObject*> selected_objects;
	static bool isPlaying;
	static bool isPaused;
		
	static GameObject* Get_Selection();

	static std::vector<GameObject*>& Get_Selected_Objects();

	static void Add_Selected_Object(GameObject* _object);

	static void Clear_Selected_Objects();

};


#endif // !EDITOR_STATE_MANAGER_HPP