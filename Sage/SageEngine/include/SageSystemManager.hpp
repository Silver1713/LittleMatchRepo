#ifndef SAGE_SYSTEM_MANAGER_HPP
#define SAGE_SYSTEM_MANAGER_HPP
#include <map>
#include <string>

#include "Systems/System.hpp"

struct SageSystemManager
{
	static std::map<std::string, System*> systems;
	static void Init();
	static void Exit();

	template <typename T>
	static T* Get_System();
	template <typename T >
	static void Add_System(T* _system);

};

template<typename T>
T* SageSystemManager::Get_System()
{
	auto it = systems.find(typeid(T).name());
	if (it != systems.end())
	{
		return dynamic_cast<T*>(it->second);
	}
	return nullptr;
}

template <typename T >
void SageSystemManager::Add_System(T* _system)
{
	if (dynamic_cast<System*>(_system))
	{
		systems[typeid(T).name()] = _system;
		_system->Init();
	}
	else
	{
		delete _system;
	}
}


#endif