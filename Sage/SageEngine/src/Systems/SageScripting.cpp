#include "Systems/SageScripting.hpp"
#include "SageScriptLoader.hpp"

std::unique_ptr<SageLoader> SageScriptSystem::loader{};
void SageScriptSystem::Init(const char* _mono_lib_path, const char* _mono_etc_path)
{
	loader = std::make_unique<SageLoader>();
	loader->Init(_mono_lib_path, _mono_etc_path);
}


void SageScriptSystem::Update()
{
	
}


void SageScriptSystem::Exit()
{
	loader->Exit();
}


