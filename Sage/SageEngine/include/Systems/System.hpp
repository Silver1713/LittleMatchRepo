#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <memory>
#include <string>
#include <unordered_map>

class GameObject;

class System
{
protected:
	std::unordered_map<std::string, std::unique_ptr<GameObject>>* entities;
public:
	enum class SystemType
	{
		GRAPHICS,
		INPUT,
		SCRIPTING,
		NETWORK,
		RESOURCE,
		NUM_SYSTEMS
	};

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual  void Exit() = 0;
	virtual ~System() = default;
	virtual SystemType GetInstance() = 0;
};


#endif
