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
	static std::unordered_map<MonoObject*, unsigned> cs_to_cpp_mapping;
	static std::unordered_map<GameObject*, unsigned> cpp_to_cs_mapping;
	
	static void Map_Script_Instance_GameObject(MonoObject* _instance, GameObject* _entity);


	template <typename T >
	static void Create_Component_Shadow(T* component);
	

	static GameObject* Get_GameObject_From_Instance(MonoObject* _instance);
	
	static MonoObject* Get_MonoGameObject_From_Entity(GameObject* _entity);


	static MonoRepresentation* Get_Mono_Represation_From_Entity(GameObject* _entity);

	static void Init();

	static void Init_Batch(GameObject* _entity);

	static void Create_Game_Object_Shadow(GameObject* _entity);


	static void Exit();








};


template <typename T>
void BindingSystem::Create_Component_Shadow(T* component)
{
	if (!component) return;
	GameObject* parent = component->Get_Parent();
	bool found = cpp_to_cs_mapping.contains(parent);
	if (!found)
	{
		return;
	}
	MonoObject* component_instance;
	unsigned index = cpp_to_cs_mapping[parent];
	switch (component->Get_Component_Type())
	{
	case ComponentType::TRANSFORM:
		// Create transform shadow
		component_instance = SageMonoManager::Create_Instance(SageMonoManager::Get_Klass_Info("Transform", "SageEngine")->klass);
		mono_entities[index].components[ComponentType::TRANSFORM] = component_instance;
		cs_to_cpp_mapping[component_instance] = index;
		//mono_runtime_object_init(component_instance);
		break;
	default:
		// Invalid component
		component_instance = nullptr;
		break;
	}


}




#endif	// !BINDINGSYSTEM_HPP
