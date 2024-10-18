#ifndef BEHAVIOUR_COMPONENT_HPP
#define BEHAVIOUR_COMPONENT_HPP
#include <unordered_map>
#include <mono/metadata/object-forward.h>

#include "Component.hpp"

class Behaviour : public Component
{
	std::vector<std::pair<std::string, MonoObject*>> mono_instances;
public:
	void Init(GameObject* _parent) override;
	void Update() override;
	void Draw() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;

	std::vector < std::pair<std::string, MonoObject*>>& Get_Mono_Instances();

	void Add_Instance(std::string _klass_name, std::string _namespace);
	void Remove_Instance(std::string _klass_name);


};
#endif // !BEHAVIOUR_COMPONENT_HPP