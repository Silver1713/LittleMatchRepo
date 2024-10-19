#ifndef BINDINGSYSTEM_HPP
#define BINDINGSYSTEM_HPP
#include <map>
#include <unordered_map>
#include <mono/metadata/object-forward.h>

#include "SageMonoManager.hpp"
#include "Components/Component.hpp"

class Transform;
class Behaviour;
class GameObject;

class BindingSystem
{

	static void Bind_Input_System();
	static void Bind_Rendering_System();
	

	
public:
	struct MonoRepresentation
	{
		GameObject* cpp_entity;
		MonoObject* cs_entity;
		std::map<ComponentType, MonoObject*> components;
		std::vector<MonoObject*> behaviours;

	};
	static std::vector<BindingSystem::MonoRepresentation> mono_entities;
	static std::unordered_map<MonoObject*, MonoRepresentation*> cs_to_cpp_mapping;
	static std::unordered_map<GameObject*, MonoRepresentation*> cpp_to_cs_mapping;
	
	static void Map_Script_Instance_GameObject(MonoObject* _instance, GameObject* _entity);


	template <typename T >
	static void Create_Component_Shadow(T* component);
	

	static GameObject* Get_GameObject_From_Instance(MonoObject* _instance);
	
	

	static void Init();

	static void Init_Batch(GameObject* _entity);

	static void Create_Game_Object_Shadow(GameObject* _entity);


	static void Exit();








};


template <typename T>
void BindingSystem::Create_Component_Shadow(T* component)
{
	GameObject* parent = component->Get_Parent();
	MonoRepresentation* representation = cpp_to_cs_mapping[parent];
	if (!representation)
	{
		return;
	}
	MonoObject* component_instance;
	switch (component->Get_Component_Type())
	{
	case ComponentType::TRANSFORM:
		// Create transform shadow
		component_instance = SageMonoManager::Create_Instance(SageMonoManager::Get_Klass_Info("Transform", "SageEngine")->klass);



		representation->components[ComponentType::TRANSFORM] = component_instance;
		break;
	default:
		// Invalid component
		component_instance = nullptr;
		break;
	}


}




#endif	// !BINDINGSYSTEM_HPP
