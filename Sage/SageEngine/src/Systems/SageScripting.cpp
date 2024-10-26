#include "Systems/SageScripting.hpp"

#include <iostream>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/object.h>
#include "SageMonoManager.hpp"
#include "SageScriptLoader.hpp"
#include "GameObjects.hpp"
#include "Components/Behaviour.h"

System::SystemType SageScriptSystem::GetInstance()
{
	return System::SystemType::SCRIPTING;

}


void SageScriptSystem::Init()
{
	entities = &Game_Objects::Get_Game_Objects();

	for (auto& entity : *entities)
	{
		Behaviour* behaviour = entity.second->Get_Component<Behaviour>();

		if (!behaviour)
		{
			continue;
		}

		scriptable_entities[entity.first] = behaviour;
	}

	loader = SageMonoManager::Get_Loader();
	
}

void SageScriptSystem::Update()
{
	for (auto& entity : scriptable_entities)
	{
		Behaviour* scriptableComponent = entity.second;
		std::vector<std::pair<std::string, MonoObject*> >& instances = scriptableComponent->Get_Mono_Instances();

		for (auto& instance : instances)
		{
			Invoke_Method_In_Instance(instance.second, "Update()");
		}
	}
}


void SageScriptSystem::Update_Entity(GameObject* _entity)
{
	Behaviour* behaviour = _entity->Get_Component<Behaviour>();
	if (!behaviour)
	{
		return;
	}

	std::vector<std::pair<std::string, MonoObject*>>& instances = behaviour->Get_Mono_Instances();

	for (auto& instance : instances)
	{
		Invoke_Method_In_Instance(instance.second, "Update()");
	}
}

void SageScriptSystem::Exit()
{
	loader = nullptr;

}

SageScriptSystem::~SageScriptSystem()
{
	loader = nullptr;
}

void SageScriptSystem::Invoke_Method_In_Instance(MonoObject* mono_object, const char* _method_name, const char* _args)
{
	bool found = false;
	MonoClass* klass = mono_object_get_class(mono_object);
	MonoMethod* method = nullptr;
	if (methods.contains(klass))
	{
		auto& method_map = methods[klass];
		if (method_map.contains(_method_name))
		{
			method = method_map[_method_name];
			found = true;
		}
	}
	else
	{
		found = false;
	}


	if (!found)
	{
		const char* ns = mono_class_get_namespace(klass);

		const char* class_name = mono_class_get_name(klass);
		std::string quantified_method_name = std::string(ns) + "." + std::string(class_name) + ":" + _method_name;

		MonoImage* image = mono_class_get_image(klass);
		MonoMethodDesc* desc = mono_method_desc_new(quantified_method_name.c_str(), 1);
		method = mono_method_desc_search_in_image(desc, image);
		if (!method)
		{
			
			return;
		}
		methods[klass][_method_name] = method;
	}


	// Invoke
	if (_args)
	{
		MonoArray* args_array = mono_array_new(SageMonoManager::Default_Domain, mono_get_string_class(), 1);
		mono_array_set(args_array, MonoString*, 0, mono_string_new(SageMonoManager::Default_Domain, _args));
		mono_runtime_invoke(method, mono_object, reinterpret_cast<void**>(&args_array), nullptr);
	}
	else
	{
		mono_runtime_invoke(method, mono_object, nullptr, nullptr);
	}


}

void SageScriptSystem::Add_Script_Instance_Environment(const char* name, Behaviour* _behaviour)
{
	scriptable_entities[name] = _behaviour;
}


void SageScriptSystem::Map_Script_Instance_GameObject(MonoObject* _instance, GameObject* _entity)
{
	mapped_instances[_instance] = _entity;
}


void SageScriptSystem::Init_CSBehaviour_Instance(MonoObject* _instance)
{
	Invoke_Method_In_Instance(_instance, "Init()");

}


void SageScriptSystem::Throw_Exception(MonoString* message_instance)
{
	MonoClass* exception = mono_get_exception_class();
	MonoObject* ex_instance = mono_object_new(SageMonoManager::Default_Domain, exception);
	void* args[1];
	args[0] = message_instance;
	mono_runtime_invoke(mono_class_get_method_from_name(exception, ".ctor", 1), ex_instance, args, nullptr);

	mono_raise_exception(reinterpret_cast<MonoException*>(ex_instance));
}



