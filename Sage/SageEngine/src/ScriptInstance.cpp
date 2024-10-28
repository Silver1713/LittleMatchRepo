#include "ScriptInstance.hpp"

#include <mono/metadata/object.h>


void ScriptInstance::Init()
{
	
}


ScriptInstance::ScriptInstance() : instance(nullptr), init_method(nullptr), update_method(nullptr), draw_method(nullptr),
exit_method(nullptr), on_collision_enter_method(nullptr), on_collision_exit_method(nullptr),
on_collision_stay_method(nullptr)
{

}


ScriptInstance::ScriptInstance(MonoObject* _instance) : instance(_instance), init_method(nullptr), update_method(nullptr), draw_method(nullptr),
exit_method(nullptr), on_collision_enter_method(nullptr), on_collision_exit_method(nullptr),
on_collision_stay_method(nullptr)
{
	if (!instance) return;

	MonoClass* klass_instance = mono_object_get_class(instance);

	init_method = mono_class_get_method_from_name(klass_instance, "Init", 0);
	update_method = mono_class_get_method_from_name(klass_instance, "Update", 0);
	draw_method = mono_class_get_method_from_name(klass_instance, "Draw", 0);
	exit_method = mono_class_get_method_from_name(klass_instance, "Exit", 0);

	on_collision_enter_method = mono_class_get_method_from_name(klass_instance, "OnCollisionEnter", 1);
	on_collision_exit_method = mono_class_get_method_from_name(klass_instance, "OnCollisionExit", 1);
	on_collision_stay_method = mono_class_get_method_from_name(klass_instance, "OnCollisionStay", 1);


}




