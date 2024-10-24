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
	MonoAssembly* Load_Assembly(const char* name, const char* assembly_path);
	MonoImage* Load_Image(MonoAssembly* assembly);

	
	void Run_Main(MonoAssembly* assembly , const char* assembly_name);
	

	MonoDomain* Get_RT_Domain();



	void Exit();


};



#endif
