#include "SageSystemManager.hpp"

#include "BindingSystem.hpp"
#include "Systems/SageScripting.hpp"

std::map<std::string, System*> SageSystemManager::systems{};
void SageSystemManager::Init()
{
	// Add Common Components
	Add_System(new SageScriptSystem());
	BindingSystem::Init();
}

void SageSystemManager::Exit()
{
	for (auto& system : systems)
	{
		delete system.second;
	}
	systems.clear();
}
