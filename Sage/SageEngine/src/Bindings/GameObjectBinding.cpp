//#include "Bindings/Bindings.hpp"
#include "Bindings/GameObjectBinding.hpp"

#include <iostream>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/object.h>
#include <mono/metadata/exception.h>
#include "BindingSystem.hpp"
#include "GameObjects.hpp"
#include "SageSystemManager.hpp"
#include "Systems/SageScripting.hpp"

void GameObjectBinding::Bind()
{
	mono_add_internal_call("SageEngine.Entity::getGameObject_Name", reinterpret_cast<void*>(GameObjectBinding::getName));
	mono_add_internal_call("SageEngine.Entity::getGameObject_Active", reinterpret_cast<void*>(GameObjectBinding::getActive));
	mono_add_internal_call("SageEngine.Entity::setGameObject_Active", reinterpret_cast<void*>(GameObjectBinding::setActive));
	mono_add_internal_call("SageEngine.GameObject::AddComponentInternal", reinterpret_cast<const void*>(Add_Component));
	mono_add_internal_call("SageEngine.GameObject::GetComponentInternal", reinterpret_cast<const void*>(Get_Component));
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







MonoObject* GameObjectBinding::Get_Component(MonoObject* obj, MonoReflectionType* component_name)
{
	SageScriptSystem* script_system = SageSystemManager::Get_System<SageScriptSystem>();
	MonoDomain* default_domain = SageMonoManager::Get_Default_Domain();
	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	MonoType* type = mono_reflection_type_get_type(component_name);
	MonoClass* component_klass = mono_class_from_mono_type(type);

	if (!component_klass)
	{
		script_system->Throw_Exception(mono_string_new(default_domain, "Component not found"));

		return nullptr;
	}
	// Get
	SageMonoManager::MonoKlassInfo* klass_info = SageMonoManager::Get_Klass_Info("Component", "SageEngine");
	// Check if the component is a subclass of Component
	if (!mono_class_is_subclass_of(component_klass, klass_info->klass, false))
	{
		MonoClass* exception = mono_get_exception_class();
		MonoObject* ex_instance = mono_object_new(SageMonoManager::Get_Default_Domain(), exception);
		void* args[1];
		args[0] = mono_string_new(SageMonoManager::Get_Default_Domain(), "Component not found");
		mono_runtime_invoke(mono_class_get_method_from_name(exception, ".ctor", 1), ex_instance, args, nullptr);

		mono_raise_exception(reinterpret_cast<MonoException*>(ex_instance));

		return nullptr;
	}
	BindingSystem::MonoRepresentation* representation = BindingSystem::Get_Mono_Represation_From_Entity(entity);

	std::string className = mono_class_get_name(component_klass);
	ComponentType component_type;
	if (className == "Transform")
	{
		component_type = ComponentType::TRANSFORM;
		if (representation->components.contains(component_type))
		{
			MonoObject* component = representation->components[component_type];
			return component;
		}
	}
	else if (className == "RigidBody")
	{
		component_type = ComponentType::RIGIDBODY;
		if (representation->components.contains(component_type))
		{
			MonoObject* component = representation->components[component_type];
			return component;
		}
	}
	else
	{
		if (!mono_class_is_subclass_of(component_klass, klass_info->klass, false))
		{
			script_system->Throw_Exception(mono_string_new(default_domain, "Component not found"));
			return nullptr;
		}

		// Get the instance of the component
		Behaviour* behaviourComponent = entity->Get_Component<Behaviour>();

		for (auto& [name, mono_object] : behaviourComponent->Get_Mono_Instances())
		{
			if (name == className)
			{
				return mono_object;
			}
		}
	}

	return nullptr;

}


MonoObject* GameObjectBinding::Add_Component(MonoObject* obj, MonoObject* component)
{
	MonoClass* component_klass = mono_object_get_class(component);
	SageMonoManager::MonoKlassInfo* component_info = SageMonoManager::Get_Klass_Info(component_klass);
	MonoDomain* default_domain = SageMonoManager::Get_Default_Domain();
	SageScriptSystem* script_system = SageSystemManager::Get_System<SageScriptSystem>();

	SageMonoManager::MonoKlassInfo* klass_info = SageMonoManager::Get_Klass_Info("Component", "SageEngine");
	bool is_component = mono_class_is_subclass_of(klass_info->klass, klass_info->klass, false);

	if (!is_component)
	{
		script_system->Throw_Exception(mono_string_new(default_domain, "Component not found"));
		return nullptr;
	}

	GameObject* entity = BindingSystem::Get_GameObject_From_Instance(obj);
	BindingSystem::MonoRepresentation* representation = BindingSystem::Get_Mono_Represation_From_Entity(entity);
	ComponentType  component_type = GameObjectBinding::Mono_Component_To_Primitive(component);
	bool has_component = representation->components.contains(component_type);

	if (has_component && component_type != BEHAVIOUR)
	{
		script_system->Throw_Exception(mono_string_new(default_domain, "Component already exists"));
		return nullptr;
	}

	if (component_type == BEHAVIOUR)
	{
		Behaviour* behaviourComponent = entity->Get_Component<Behaviour>();
		
		
		MonoObject* instance_comp = behaviourComponent->Add_Instance(component_info->Klass_Name, component_info->Klass_Namespace);
		return instance_comp;
	}
	else
	{
		MonoObject* component_instance = SageMonoManager::Create_Instance(component_info->klass);
		representation->components[component_type] = component_instance;

		BindingSystem::Map_Script_Instance_GameObject(component_instance, entity);

		return component_instance;
	}



	
	
}


ComponentType GameObjectBinding::Mono_Component_To_Primitive(MonoObject* component)
{
	MonoClass* component_klass = mono_object_get_class(component);
	SageMonoManager::MonoKlassInfo* component_info = SageMonoManager::Get_Klass_Info(component_klass);
	std::string className = component_info->Klass_Name;
	if (className == "Transform")
	{
		return ComponentType::TRANSFORM;
	}
	else if (className == "RigidBody")
	{
		return ComponentType::RIGIDBODY;
	}
	else if (className == "Renderer") {
		return ComponentType::RENDERER;
	}
	else if (className == "Sprite")
	{
		return ComponentType::SPRITE2D;
	}
	else if (className == "BoxCollider")
	{
		return ComponentType::BOXCOLLIDER2D;
	}

	else if (className == "Audio")
	{
		return ComponentType::AUDIO;
	}
	else
	{
		// Check if the component is a subclass of Behaviour
		MonoClass* behaviour_klass = SageMonoManager::Get_Klass_Info("Behaviour", "SageEngine")->klass;
		if (mono_class_is_subclass_of(component_klass, behaviour_klass, false))
		{
			return ComponentType::BEHAVIOUR;
		}
	}
	std::exit(1);
	
}

