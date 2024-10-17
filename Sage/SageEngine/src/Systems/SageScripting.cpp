#include "Systems/SageScripting.hpp"

#include <iostream>
#include <mono/metadata/debug-helpers.h>

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
	if (methods.find(klass) != methods.end())
	{
		auto& method_map = methods[klass];
		if (method_map.find(_method_name) != method_map.end())
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
		MonoImage* image = mono_class_get_image(klass);
		MonoMethodDesc* desc = mono_method_desc_new(_method_name, 0);
		method = mono_method_desc_search_in_image(desc, image);
		if (!method)
		{
			std::cout << "Failed to find method\n";
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




