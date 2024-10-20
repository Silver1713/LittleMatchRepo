//#include "Bindings/Bindings.hpp"
#include "Bindings/GameObjectBinding.hpp"

#include <mono/metadata/appdomain.h>
#include <mono/metadata/object.h>
#include "BindingSystem.hpp"
#include "GameObjects.hpp"

void GameObjectBinding::Bind()
{

}


void GameObjectBinding::Bind(GameObject* object)
{

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












