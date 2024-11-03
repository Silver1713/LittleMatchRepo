#ifndef BEHAVIOUR_COMPONENT_HPP
#define BEHAVIOUR_COMPONENT_HPP
#include <unordered_map>
#include <mono/metadata/object-forward.h>

#include "Component.hpp"
#include "ScriptInstance.hpp"

class Behaviour : public Component
{
	std::vector<std::pair<std::string, MonoObject*>> mono_instances;
	std::vector<std::pair<std::string, ScriptInstance>> script_instances;

public:
	void Init(GameObject* _parent) override;
	void Update() override;
	void Draw() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;

	std::vector < std::pair<std::string, MonoObject*>>& Get_Mono_Instances();
	std::vector < std::pair<std::string, ScriptInstance>>& Get_Script_Instances();

	MonoObject* Add_Instance(std::string _klass_name, std::string _namespace);
	void Remove_Instance(std::string _klass_name);
	void Remove_All_Instance();

};
#endif // !BEHAVIOUR_COMPONENT_HPP