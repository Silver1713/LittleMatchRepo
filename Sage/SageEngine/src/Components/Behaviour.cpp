#include "SageMonoManager.hpp"
#include "Components/Behaviour.hpp"

#include <iostream>

#include "BindingSystem.hpp"
#include "SageSystemManager.hpp"
#include "Systems/SageScripting.hpp"


void Behaviour::Init(GameObject* _parent)
{
	Component::Init(_parent);

}

void Behaviour::Update()
{
	if (!is_enabled) { return; }
}

void Behaviour::Draw()
{
	
}

void Behaviour::Exit()
{
	
}


ComponentType Behaviour::Get_Component_Type()
{
	return ComponentType::BEHAVIOUR;
}

std::vector<std::pair<std::string, MonoObject*>>& Behaviour::Get_Mono_Instances()
{
	return mono_instances;
}


void Behaviour::Add_Instance(std::string _klass_name, std::string _namespace)
{
	SageMonoManager::MonoKlassInfo* klass = SageMonoManager::Get_Klass_Info(_klass_name.c_str(), _namespace.empty() ? nullptr : _namespace.c_str());
	if (!klass)
	{
		return;
	}

	if (std::strcmp(klass->Klass_OfA_Name, "SageBehaviour") != 0)
	{
		std::cout << "Warning:	Class is not of a Behaviour Type, You can only add class that is of SageBehaviour type.\n";
		return;
	}
	MonoObject* instance = SageMonoManager::Create_Instance(klass->klass);
	SageSystemManager::Get_System<SageScriptSystem>()->Map_Script_Instance_GameObject(instance, parent);
	BindingSystem::Map_Script_Instance_GameObject(instance, parent);

	SageMonoManager::MonoKlassInfo* BaseClass = SageMonoManager::Get_Klass_Info("Component", "SageEngine");
	// Get field gameObject
	MonoClassField* field = mono_class_get_field_from_name(BaseClass->klass, "gameObject");
	MonoObject* gameObject = BindingSystem::Get_MonoGameObject_From_Entity(parent);
	mono_field_set_value(instance, field, gameObject);

	// Get Field transform
	BaseClass = SageMonoManager::Get_Klass_Info("Transform", "SageEngine");
	field = mono_class_get_field_from_name(BaseClass->klass, "transform");
	BindingSystem::MonoRepresentation* representation = BindingSystem::Get_Mono_Represation_From_Entity(parent);
	MonoObject* transform = representation->components[ComponentType::TRANSFORM];

	mono_field_set_value(instance, field, transform);

	


	mono_instances.emplace_back(std::make_pair(_klass_name, instance));

	SageSystemManager::Get_System<SageScriptSystem>()->Init_CSBehaviour_Instance(instance);

	
}


void Behaviour::Remove_Instance(std::string _klass_name)
{
		
	return;
}


