#ifndef Sage_Script_Loader_HPP
#define Sage_Script_Loader_HPP
#include <string>
#include <mono/jit/jit.h>
#include <map>


struct SageLoader
{
	static std::string mono_assembly_dir;
	static std::string mono_config_dir;

	static MonoDomain* backend_domain;
	static MonoDomain* runtime_domain; //!< Main runtime environment for game engine scripts.

	static std::map<std::string, MonoAssembly*> assemblies;

	void Init(std::string const& mono_assembly_dir, std::string const& mono_config_dir);
	void Load_Assembly(const char* name, const char* assembly_path);
	void Run_Main(const char* assembly_name);

	void Run_Method(const char* assembly_name, const char* method_name, const char* args);

	void Run_Method(MonoMethod* method, MonoObject* obj, void** args);

	void Exit();

};



#endif
