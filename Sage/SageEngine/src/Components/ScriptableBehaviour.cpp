#include "Components/ScriptableBehaviour.hpp"


void ScriptableBehaviour::Init(GameObject* _parent)
{
	if (_parent)
	{
		parent = _parent;
	} else
	{
		// Get the parent from base class
		parent = Get_Parent();
	}
}



ComponentType ScriptableBehaviour::Get_Component_Type()
{
	return ComponentType::SCRIPTABLEBEHAVIOUR;
}

