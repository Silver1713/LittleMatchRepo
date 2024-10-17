#include "SageSystemManager.hpp"

#include "Systems/SageScripting.hpp"

std::map<std::string, System*> SageSystemManager::systems{};
void SageSystemManager::Init()
{
	// Add Common Components
	Add_System(new SageScriptSystem());
}

void SageSystemManager::Exit()
{
	for (auto& system : systems)
	{
		delete system.second;
	}
	systems.clear();
}
