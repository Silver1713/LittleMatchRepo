//#include "Bindings/Bindings.hpp"
#include "Bindings/GameObjectBinding.hpp"

#include <iostream>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/object.h>
#include "BindingSystem.hpp"
#include "GameObjects.hpp"

void GameObjectBinding::Bind()
{
	mono_add_internal_call("SageEngine.Entity::getGameObject_Name", reinterpret_cast<void*>(GameObjectBinding::getName));
	mono_add_internal_call("SageEngine.Entity::getGameObject_Active", reinterpret_cast<void*>(GameObjectBinding::getActive));
	mono_add_internal_call("SageEngine.Entity::setGameObject_Active", reinterpret_cast<void*>(GameObjectBinding::setActive));
	
}


void GameObjectBinding::Unbind()
{

}

MonoString* GameObjectBinding::getName(MonoObject* obj)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	MonoString* name = mono_string_new(mono_domain_get(), entity->Get_ID().c_str());

	return name;
}

MonoBoolean GameObjectBinding::getActive(MonoObject* obj)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	MonoBoolean active = entity->Is_Enabled();
	return active;
}

void GameObjectBinding::setActive(MonoObject* obj, MonoBoolean active)
{
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);

	if (active)
	{
		entity->Enable();
	}
	else
	{
		entity->Disable();
	}



}

void GameObjectBinding::setName(MonoObject* obj, MonoString* name)
{
}














