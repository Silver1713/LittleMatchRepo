#ifndef GAMEOBJECTBINDING_HPP
#define GAMEOBJECTBINDING_HPP
#include "Binding.hpp"
#include "Components/Component.hpp"

class GameObjectBinding {
public:
	static void Bind() ;
	static void Bind(GameObject* object) ;
	static void Unbind() ;

	static MonoString* getName(MonoObject* obj);
	static void setName(MonoObject* obj, MonoString* name);
	static MonoBoolean getActive(MonoObject* obj);
	static void setActive(MonoObject* obj, MonoBoolean active);

	static MonoObject* Add_Component(MonoObject* obj, MonoObject* component);
	static MonoObject* Get_Component(MonoObject* obj, MonoReflectionType* component_name);

	static ComponentType Mono_Component_To_Primitive(MonoObject* component);
};


#endif