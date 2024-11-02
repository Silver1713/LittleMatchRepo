#ifndef SAGE_MONO_MANAGER_HPP
#define SAGE_MONO_MANAGER_HPP
// A manager class for the Mono runtime

#include <memory>
#include <unordered_map>
#include <mono/metadata/image.h>
#include <mono/utils/mono-forward.h>
#include <string>

#include "SageScriptLoader.hpp"
struct SageLoader;
class SageAssembler;
struct SageMonoManager
{
	struct MonoKlassInfo
	{
		// Internals
		MonoClass* klass;
		MonoImage* image;
		MonoAssembly* assembly;

		const char* Klass_Namespace{}; // Namespace
		const char* Klass_Name{}; // Class Name
		char * Klass_Full_Name{}; // Full Name
		const char* Klass_OfA_Name{}; // The Name of the Base Class, if any

		MonoKlassInfo();

		MonoKlassInfo(const MonoKlassInfo& other) = delete;
		MonoKlassInfo& operator=(const MonoKlassInfo& other) = delete;


		MonoKlassInfo(MonoKlassInfo&& other);
		MonoKlassInfo& operator=(MonoKlassInfo&& other);



		~MonoKlassInfo();
	};


	struct KlassInstance
	{
		MonoKlassInfo* Of_A; // The Class Information
		MonoObject* Instance; // The Instance

	};
	// Tools
	static std::unique_ptr< SageLoader> loader;
	static std::unique_ptr<SageAssembler> compiler;


	static MonoDomain* Default_Domain;
	static std::unordered_map<std::string, MonoDomain*> domains;
	static std::unordered_map<std::string, MonoAssembly*> assemblies;
	static std::unordered_map<std::string, MonoImage*> images;
	static std::unordered_map<std::string, MonoKlassInfo> klassList;

	// Streams

	struct STDOUTCS
	{
		size_t latest_index;
		std::string latest;
		std::vector<std::pair<std::string, size_t>> stdout_stream;


		void Add(const char* message);

		std::vector<std::pair<std::string, size_t>> Get();
		void Clear();

	};


	struct STDERRCS
	{
		std::string latest;
		std::map<std::string, size_t> stdout_stream;


		void Add(const char* message);
		void Clear();
		std::vector<std::pair<std::string, size_t>> Get();
	};


	static STDOUTCS output_stream;
	static STDERRCS error_stream;


	


	// Lifecycle
	static void Initialize();
	static void Shutdown();
	//Tools
	static SageAssembler* Get_Compiler();
	static SageLoader* Get_Loader();

	// Compilation
	static void Set_Compiler_Output(const char* _output_dir);
	static void Compiler_Add_File(const char* _file_path);
	static void Compiler_Add_Source(const char* name, const char* source);
	static void Compiler_CompileAsync(bool into_lib);
	// Loaders
	static void Load_Assembly(const char* _assembly_name);
	static void Load_Assembly(const char* _assembly_name, const char* _assembly_path);

	static void Load_Image(const char* _image_name, const char* _assembly_name);
	static void Load_Image(const char* _image_name, MonoAssembly* _assembly);

	// --- Reflection ---

	static MonoClass* Load_Klass_In_Image(MonoImage* Image, const char* _klass_name, const char* _klass_namespace=nullptr);
	static MonoObject* Create_Instance(MonoClass* _klass, bool do_not_instantiate=false);

	//------Retrieval-----

	static MonoKlassInfo* Get_Klass_Info(const char* _klass_name, const char* _namespace=nullptr);
	static MonoKlassInfo* Get_Klass_Info(MonoClass* klass);

	//---Compilation of Scripts
	static void Compile_Scripts(const char* script_dir, const char* output_assembly);


	//-----Get Domain-----
	static MonoDomain* Get_Default_Domain();


	//---Boxing and Unboxing---
	template <typename T >
	static MonoObject* Box_Value(MonoDomain* domain, MonoClass* klass, T* value);
	template <typename T>
	static T* Unbox_Value(MonoObject* obj);


	//Logging
	static void handle_print(const char* message, mono_bool is_stdout);
	static void handle_log(const char* log_domain, const char* log_level, const char* message, mono_bool fatal, void* user_data);


};

template <typename T>
MonoObject* SageMonoManager::Box_Value(MonoDomain* domain, MonoClass* klass, T* value)
{
	MonoObject* boxed = mono_value_box(domain, klass, value);
	return boxed;
}

template <typename T>
T* SageMonoManager::Unbox_Value(MonoObject* obj)
{
	T* value = reinterpret_cast<T*>(mono_object_unbox(obj));
	return value;
}



#endif // !SAGE_MONO_MANAGER_HPP