#ifndef SCRIPT_INSTANCE_HPP
#define SCRIPT_INSTANCE_HPP
#include <mono/metadata/object-forward.h>

class ScriptInstance
{
public:
	MonoObject* instance;


	//Behaviour life cycle
	MonoMethod* init_method;
	MonoMethod* update_method;
	MonoMethod* draw_method;
	MonoMethod* exit_method;


	//Collision life cycle
	MonoMethod* on_collision_enter_method;
	MonoMethod* on_collision_exit_method;
	MonoMethod* on_collision_stay_method;


	ScriptInstance();
	ScriptInstance(MonoObject* _instance);

	void Init();



};

#endif // !SCRIPT_INSTANCE_HPP