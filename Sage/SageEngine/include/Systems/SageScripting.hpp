#ifndef SAGE_SCRIPTING_SYSTEM
#define SAGE_SCRIPTING_SYSTEM
#include <memory>
#include <mono/metadata/object-forward.h>

#include "System.hpp"
class Behaviour;
class SageAssembler;
struct SageLoader;
class SageScriptSystem : public System
{
	SageLoader* loader;
	std::unordered_map<std::string, Behaviour*> scriptable_entities;
	std::unordered_map<MonoClass*, std::unordered_map<std::string, MonoMethod*>> methods{};



public:

	// Invokation - Method default to Main(Strg[] args) if not specified
	void Invoke_Method_In_Instance(MonoObject* mono_instance, const char* _method_name="Main(String[] args)", const char* _args = nullptr);

	void Init() override;
	void Update() override;
	void Update_Entity(GameObject* _entity) override;
	
	void Exit() override;
	SystemType GetInstance() override;

	~SageScriptSystem() override;


	void Add_Script_Instance_Environment(const char* name ,Behaviour* _behaviour);


	
};

#endif