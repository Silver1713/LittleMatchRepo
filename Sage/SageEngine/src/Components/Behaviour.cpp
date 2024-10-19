#include "SageMonoManager.hpp"
#include "Components/Behaviour.hpp"



void Behaviour::Init(GameObject* _parent)
{
	Component::Init(_parent);
}

void Behaviour::Update()
{
	
}

void Behaviour::Draw()
{
	
}

void Behaviour::Exit()
{
	
}


ComponentType Behaviour::Get_Component_Type()
{
	return ComponentType::BEHAVIOUR;
}

std::vector<std::pair<std::string, MonoObject*>>& Behaviour::Get_Mono_Instances()
{
	return mono_instances;
}


void Behaviour::Add_Instance(std::string _klass_name, std::string _namespace)
{
	SageMonoManager::MonoKlassInfo* klass = SageMonoManager::Get_Klass_Info(_klass_name.c_str(), _namespace.empty() ? nullptr : _namespace.c_str());
	MonoObject* instance = SageMonoManager::Create_Instance(klass->klass);
	mono_instances.emplace_back(std::make_pair(_klass_name, instance));
}


void Behaviour::Remove_Instance(std::string _klass_name)
{
	return;
}


