#include "SageMonoManager.hpp"

#include <iostream>
#include <filesystem>
#include <mono/metadata/debug-helpers.h>

#include "SageScriptLoader.hpp"
#include "SageScriptCompiler.hpp"


std::unique_ptr<SageLoader> SageMonoManager::loader{};
std::unique_ptr<SageAssembler> SageMonoManager::compiler{};
MonoDomain* SageMonoManager::Default_Domain{};

std::unordered_map<std::string, MonoDomain*> SageMonoManager::domains{};
std::unordered_map<std::string, MonoAssembly*> SageMonoManager::assemblies{};
std::unordered_map<std::string, MonoImage*> SageMonoManager::images{};
std::unordered_map<std::string, SageMonoManager::MonoKlassInfo> SageMonoManager::klassList{};

void SageMonoManager::Initialize()
{
	compiler = std::make_unique<SageAssembler>();
	loader = std::make_unique<SageLoader>();

	// Initialize Mono Environment
	loader->Init("../MONO/lib", "../MONO/etc");
	compiler->Init("..\\MONO\\bin\\", "..\\BehaviourScripts\\programs");
	compiler->Set_Command("csc"); // use roslyn compiler.
	compiler->Set_Compile_Flags("/target:library -langversion:8.0");

	// Compile ALL C# Scripts
	Compile_Scripts("../BehaviourScripts/scripts", "../BehaviourScripts/programs/");

	//MonoAssembly* assembly = loader->Load_Assembly("SageLibrary", "../BehaviourScripts/programs/SageLibrary.dll");
	Load_Assembly("SageLibrary", "../BehaviourScripts/programs/SageLibrary.dll");
	Load_Image("SageLibraryImage", "SageLibrary");
	Default_Domain = loader->Get_RT_Domain();
}

void SageMonoManager::Shutdown()
{
	delete compiler.release();
	delete loader.release();

	compiler = nullptr;
	loader = nullptr;
}

// Compilation
SageAssembler* SageMonoManager::Get_Compiler()
{
	return compiler.get();
}

SageLoader* SageMonoManager::Get_Loader()
{
	return loader.get();
}



void SageMonoManager::Set_Compiler_Output(const char* _output_dir)
{
	compiler->Set_Output_Directory(_output_dir);
}


void SageMonoManager::Compiler_Add_File(const char* _file_path)
{
	compiler->Add_Script(SageAssembler::FILE_MODE, _file_path);
}

void SageMonoManager::Compiler_Add_Source(const char* name, const char* source)
{
	compiler->Add_Script(name, source);
}

void SageMonoManager::Compiler_CompileAsync(bool into_lib)
{
	compiler->StartCompilation(into_lib);
	compiler->GetLog();
	compiler->Wait_For_Compile();
}

// Loaders
void SageMonoManager::Load_Assembly(const char* _assembly_name)
{
	if (assemblies.find(_assembly_name) != assemblies.end()) {
		std::cout << "Assembly already loaded\n";
		return;
	}

	MonoAssembly* assembly = loader->Load_Assembly(_assembly_name, "../BehaviourScripts/programs/SageLibrary.dll");
	if (assembly)
		assemblies[_assembly_name] = assembly;


}
void SageMonoManager::Load_Assembly(const char* _assembly_name, const char* _assembly_path)
{
	if (assemblies.find(_assembly_name) != assemblies.end()) {
		std::cout << "Assembly already loaded\n";
		return;
	}
	MonoAssembly* assembly = loader->Load_Assembly(_assembly_name, _assembly_path);
	if (assembly)
		assemblies[_assembly_name] = assembly;
}

void SageMonoManager::Load_Image(const char* _image_name, MonoAssembly* _assembly)
{
	if (images.find(_image_name) != images.end()) {
		std::cout << "Image already loaded\n";
		return;
	}
	MonoImage* image = loader->Load_Image(_assembly);
	if (image)
		images[_image_name] = image;
}

void SageMonoManager::Load_Image(const char* _image_name, const char* _assembly_name)
{
	if (images.find(_image_name) != images.end()) {
		std::cout << "Image already loaded\n";
		return;
	}
	MonoImage* image = loader->Load_Image(assemblies[_assembly_name]);
	if (image)
		images[_image_name] = image;
}


MonoClass* SageMonoManager::Load_Klass_In_Image(MonoImage* Image, const char* _klass_name, const char* _klass_namespace)
{
	MonoKlassInfo KlassInfo{};
	const char* ns;
	if (!_klass_namespace) {
		ns = "";
	}
	else ns = _klass_namespace;


	MonoClass* klass = mono_class_from_name(Image, ns, _klass_name);
	if (!klass) {
		std::cout << "Failed to load class\n";
		return nullptr;
	}

	KlassInfo.klass = klass;
	KlassInfo.image = Image;
	KlassInfo.Klass_Name = _klass_name;

	// Reflection

	// Klass Namespace
	KlassInfo.Klass_Namespace = mono_class_get_namespace(klass);
	// Klass Full Name

	std::string Klass_FName{};

	if (!_klass_namespace)
	{
		// No Namespace
		Klass_FName = _klass_name;
	} else
	{
		Klass_FName = std::string(ns) + "." + std::string(_klass_name);
	}

	KlassInfo.Klass_Full_Name = Klass_FName.c_str();

	KlassInfo.Klass_OfA_Name = mono_class_get_name(mono_class_get_parent(klass));

	klassList[Klass_FName.c_str()] = KlassInfo;
	return klass;
}



MonoObject* SageMonoManager::Create_Instance(MonoClass* _klass, bool do_not_instantiate)
{
	
	MonoObject* instance = mono_object_new(Default_Domain, _klass);
	if (!do_not_instantiate)
		mono_runtime_object_init(instance);
	return instance;
}


SageMonoManager::MonoKlassInfo* SageMonoManager::Get_Klass_Info(const char* _klass_name, const char* _namespace)
{
	std::string Klass_FName{};
	if (!_namespace)
	{
		// No Namespace
		Klass_FName = _klass_name;
	}
	else
	{
		Klass_FName = std::string(_namespace) + "." + std::string(_klass_name);
	}

	auto it = klassList.find(Klass_FName.c_str());

	if (it != klassList.end())
	{
		return &it->second;
	}
	else
	{
		MonoImage* image = images["SageLibraryImage"];
		MonoClass* klass = Load_Klass_In_Image(image, _klass_name, _namespace);
		if (!klass)
		{
			std::cout << "Failed to load class\n";
			return nullptr;
		}

		return &klassList[Klass_FName];
	}
}

void SageMonoManager::Compile_Scripts(const char* script_dir, const char* output_assembly)
{
	std::filesystem::path path(script_dir);
	if (!std::filesystem::exists(path))
	{
		std::cout << "Directory does not exist\n";
		return;
	}

	std::vector<std::string> files;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		files.push_back(entry.path().string());
	}

	for (const auto& file : files)
	{
		compiler->Add_Script(SageAssembler::FILE_MODE, file.c_str());
	}

	compiler->Set_Output_Directory(output_assembly);
	compiler->StartCompilation(true);
	compiler->Wait_For_Compile();
	std::cout << compiler->GetLog();
}


MonoDomain* SageMonoManager::Get_Default_Domain()
{
	return Default_Domain;
}
