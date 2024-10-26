#include "SageScriptLoader.hpp"

#include <iostream>
#include <sstream>
#include <thread>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/mono-gc.h>

std::string SageLoader::mono_assembly_dir{};
std::string SageLoader::mono_config_dir{};

MonoDomain* SageLoader::backend_domain{};
MonoDomain* SageLoader::runtime_domain{};

std::map<std::string, MonoAssembly*> SageLoader::assemblies{};



void SageLoader::Init(std::string const& mono_assembly_dir, std::string const& mono_config_dir)
{
	SageLoader::mono_assembly_dir = mono_assembly_dir;
	SageLoader::mono_config_dir = mono_config_dir;
	mono_set_dirs(mono_assembly_dir.c_str(), mono_config_dir.c_str());
	//Initialize runtime domain;
	runtime_domain = mono_jit_init("Runtime.exe");
	



}



MonoAssembly* SageLoader::Load_Assembly(const char * name, const char*  assembly_path)
{
	MonoAssembly* assembly = mono_domain_assembly_open(runtime_domain, assembly_path);
	if (!assembly) {
		std::cout << "Failed to open assembly\n";
		return nullptr;
	} else
	{
		return assembly;
	}

}


void SageLoader::Run_Main(MonoAssembly* assembly, const char* assembly_name)
{
	
	if (!assembly) {
		std::cout << "Failed to open assembly\n";
		return;
	}
	MonoImage* image = mono_assembly_get_image(assembly);
	MonoMethodDesc* desc = mono_method_desc_new("Program:Main(string[])", 0);
	MonoMethod* method = mono_method_desc_search_in_image(desc, image);

	if (!method) {
		std::cout << "Failed to find method\n";
		return;
	}

	MonoClass* string_class = mono_get_string_class();
	MonoArray* args_array = mono_array_new(runtime_domain, string_class, 0);

	mono_runtime_invoke(method, nullptr, reinterpret_cast<void**>(args_array), nullptr);

	mono_method_desc_free(desc);
	
}

MonoImage* SageLoader::Load_Image(MonoAssembly* assembly)
{
	if (!assembly) {
		std::cout << "Failed to open assembly\n";
		return nullptr;
	}
	MonoImage* image = mono_assembly_get_image(assembly);
	if (!image) {
		std::cout << "Failed to get image\n";
		return nullptr;
	}
	return image;

}


void SageLoader::Exit()
{
	

	mono_jit_cleanup(runtime_domain);

	
}


MonoDomain* SageLoader::Get_RT_Domain()
{
	return runtime_domain;
}

