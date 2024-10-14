#ifndef SAGE_SCRIPTING_SYSTEM
#define SAGE_SCRIPTING_SYSTEM
#include <memory>

struct SageLoader;
struct SageScriptSystem
{
	static std::unique_ptr<SageLoader> loader;
		static void Init(const char* _mono_lib_path, const char* _mono_etc_path);
	static void Update();
	static void Exit();
};

#endif