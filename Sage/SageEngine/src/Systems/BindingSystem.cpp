#include "BindingSystem.hpp"

#include <iostream>
#include <ostream>

#include "SageBindings.hpp"
#include "GameObjects.hpp"
#include "SageRenderer.hpp"
#include "Components/Behaviour.h"
#include "internal/GLFWHandler.h"
#include "Bindings/Bindings.hpp"

std::vector<BindingSystem::MonoRepresentation> BindingSystem::mono_entities{};
 std::unordered_map<MonoObject*, unsigned> BindingSystem::cs_to_cpp_mapping{};
 std::unordered_map<GameObject*, unsigned> BindingSystem::cpp_to_cs_mapping{};

void BindingSystem::Map_Script_Instance_GameObject(MonoObject* _instance, GameObject* _entity)
{
	std::cout << "MAPPING GAME OBJECTS" << std::endl;
	std::vector<MonoRepresentation>::iterator const& it = std::find_if(mono_entities.begin(), mono_entities.end(), [&_entity](MonoRepresentation& obj)
	{
		return _entity == obj.cpp_entity;
	});

	if (it == mono_entities.end())
	{
		std::string obj_class_name = mono_class_get_name(mono_object_get_class(_instance));
		if (obj_class_name == "GameObject")
		{
			Create_Game_Object_Shadow(_entity);
			Transform* transform = _entity->Get_Component<Transform>();
			if (transform)
			{
				Create_Component_Shadow(transform);

			}

			RigidBody* rigid_body = _entity->Get_Component<RigidBody>();
			if (rigid_body)
			{
				Create_Component_Shadow(rigid_body);
			}



		}
	}

	int index = std::distance(mono_entities.begin(), it);

	cs_to_cpp_mapping[_instance] = index;
	cpp_to_cs_mapping[_entity] = index;
}

GameObject* BindingSystem::Get_GameObject_From_Instance(MonoObject* _instance)
{
	bool result = cs_to_cpp_mapping.contains(_instance);
	unsigned representation = result? cs_to_cpp_mapping[_instance] : -1;
	
	if (!result)
	{
		mono_object_get_class(_instance);
		char const* a = mono_class_get_name(mono_object_get_class(_instance));
		return nullptr;
	}

	return mono_entities[representation].cpp_entity;
}

MonoObject* BindingSystem::Get_MonoGameObject_From_Entity(GameObject* _entity)
{
	bool result = cpp_to_cs_mapping.contains(_entity);
	unsigned representation = result ? cpp_to_cs_mapping[_entity] : -1;
	if (!representation)
	{
		return nullptr;
	}

	return mono_entities[representation].cs_entity;
}


BindingSystem::MonoRepresentation* BindingSystem::Get_Mono_Represation_From_Entity(GameObject* _entity)
{
	bool result = cpp_to_cs_mapping.contains(_entity);
	unsigned representation = result ? cpp_to_cs_mapping[_entity] : -1;
	if (!representation)
	{
		return {};
	}

	return &mono_entities[representation];
}

void BindingSystem::Init()
{
	//Bind all Static Methods
	Bind_Input_System();
	Bind_Rendering_System();

	GameObjectBinding::Bind();
	TransformBinding::Bind();
	RigidBodyBinding::Bind();
	std::cout << "Init success" << std::endl;

	

}

void BindingSystem::Exit()
{
	cs_to_cpp_mapping.clear();
	cpp_to_cs_mapping.clear();


}



void BindingSystem::Bind_Input_System()
{
	SageBindings::Add_Internal_Call("SageEngine.Input::GetKeyInternal", GLFWInputHandler::Get_Key);
	SageBindings::Add_Internal_Call("SageEngine.Input::GetKeyOnce", GLFWInputHandler::Get_Key_Pressed);
	SageBindings::Add_Internal_Call("SageEngine.Input::Get_Mouse_Pos", GLFWInputHandler::Get_Mouse_Pos);
}

void BindingSystem::Bind_Rendering_System()
{
	SageBindings::Add_Internal_Call("SageEngine.Renderer::Draw_Rect", SageRenderer::Draw_Rect);
	SageBindings::Add_Internal_Call("SageEngine.Renderer::Draw_Line", static_cast<void(*)(ToastBox::Vec2, ToastBox::Vec2, ToastBox::Vec4, float)>(SageRenderer::Draw_Line));
	SageBindings::Add_Internal_Call("SageEngine.Renderer::Draw_Point", static_cast<void(*)(ToastBox::Vec2, ToastBox::Vec4, float)>(
		                                SageRenderer::Draw_Point));
}


void BindingSystem::Init_Batch(GameObject* _entity)
{
	Create_Game_Object_Shadow(_entity);

	for (auto& component : _entity->Get_Components())
	{
		ComponentType type = component->Get_Component_Type();
		switch (type)
		{
		case ComponentType::TRANSFORM:
			Create_Component_Shadow(dynamic_cast<Transform*>(component.get()));
			break;
		case ComponentType::RIGIDBODY:
			Create_Component_Shadow(dynamic_cast<RigidBody*>(component.get()));
			break;
		}
	}
	
}



void BindingSystem::Create_Game_Object_Shadow(GameObject* _entity)
{
	MonoRepresentation representation{};
	representation.cpp_entity = _entity;
	SageMonoManager::MonoKlassInfo* klass = SageMonoManager::Get_Klass_Info("GameObject", "SageEngine");
	representation.cs_entity = SageMonoManager::Create_Instance(klass->klass);
	
	

	mono_entities.emplace_back(representation);
	unsigned current_pos = static_cast<unsigned>(mono_entities.size() - 1);
	cpp_to_cs_mapping[_entity] = current_pos;
	cs_to_cpp_mapping[representation.cs_entity] = current_pos;

}


