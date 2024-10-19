#include "BindingSystem.hpp"

#include "SageBindings.hpp"
#include "GameObjects.hpp"
#include "SageRenderer.hpp"
#include "Components/Behaviour.h"
#include "internal/GLFWHandler.h"


std::vector<BindingSystem::MonoRepresentation> BindingSystem::mono_entities{};
 std::unordered_map<MonoObject*, BindingSystem::MonoRepresentation*> BindingSystem::cs_to_cpp_mapping{};
 std::unordered_map<GameObject*, BindingSystem::MonoRepresentation*> BindingSystem::cpp_to_cs_mapping{};

void BindingSystem::Map_Script_Instance_GameObject(MonoObject* _instance, GameObject* _entity)
{
	MonoRepresentation representation;
	representation.cpp_entity = _entity;
	representation.cs_entity = _instance;

	mono_entities.emplace_back(representation);
	MonoRepresentation* current = &mono_entities.front();

	cs_to_cpp_mapping[_instance] = current;
	cpp_to_cs_mapping[_entity] = current;



}

GameObject* BindingSystem::Get_GameObject_From_Instance(MonoObject* _instance)
{
	MonoRepresentation* representation = cs_to_cpp_mapping[_instance];
	if (!representation)
	{
		return nullptr;
	}

	return representation->cpp_entity;
}




void BindingSystem::Init()
{
	//Bind all Static Methods
	Bind_Input_System();
	Bind_Rendering_System();

}

void BindingSystem::Exit()
{
	cs_to_cpp_mapping.clear();
	cpp_to_cs_mapping.clear();
}



void BindingSystem::Bind_Input_System()
{
	SageBindings::Add_Internal_Call("SageEngine.Input::Get_Key", GLFWInputHandler::Get_Key);
	SageBindings::Add_Internal_Call("SageEngine.Input::Get_Key_Pressed", GLFWInputHandler::Get_Key_Pressed);
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
	Create_Component_Shadow(_entity->Get_Component<Transform>());
	
}



void BindingSystem::Create_Game_Object_Shadow(GameObject* _entity)
{
	MonoRepresentation representation;
	representation.cpp_entity = _entity;
	SageMonoManager::MonoKlassInfo* klass = SageMonoManager::Get_Klass_Info("GameObject", "SageEngine");
	representation.cs_entity = SageMonoManager::Create_Instance(klass->klass);
	mono_entities.emplace_back(representation);
	MonoRepresentation* current = &mono_entities.front();
	cpp_to_cs_mapping[_entity] = current;
	cs_to_cpp_mapping[representation.cs_entity] = current;

}


