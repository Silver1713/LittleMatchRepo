#ifndef RIDIGBODYBINDING_HPP
#define RIDIGBODYBINDING_HPP


#include <mono/metadata/object-forward.h>
#include <mono/metadata/object.h>


#include "BindingStruct.hpp"

#include "Components/Component.hpp"

class GameObject;

class RigidBodyBinding
{
	static void Set_Velocity(MonoObject* obj, BindingStruct::CSVector2D* velocity);
	static void Set_Gravity(MonoObject* obj, BindingStruct::CSVector2D* gravity);
	static void Set_Mass(MonoObject* obj, float mass);

	static void Get_Velocity(MonoObject* obj, BindingStruct::CSVector2D* out_obj = nullptr);
	static void Get_Gravity(MonoObject* obj, BindingStruct::CSVector2D* out_obj = nullptr);
	static float Get_Mass(MonoObject* obj);


	static void Add_Force(MonoObject* obj, BindingStruct::CSVector2D* force, MonoObject* force_mode_types);


	static void Set_Gravity_On(MonoObject* obj, MonoBoolean gravity_on);

public:
	static void Bind();
	static void Bind(GameObject* object);
	static void Unbind();
};
#endif // !RIDIGBODYBINDING_HPP