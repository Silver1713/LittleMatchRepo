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

/*!*****************************************************************************
	\brief
		A class the encapsulates the Mono runtime and provides a set of
		tools to interact with it
*******************************************************************************/
struct SageMonoManager
{
	/*!*****************************************************************************
	\brief
		Encapsulate a Mono Class information
	*******************************************************************************/
	struct MonoKlassInfo
	{
		// Internals
		MonoClass* klass; //!< The Mono Class
		MonoImage* image; //!< The Image
		MonoAssembly* assembly; //!< The Assembly

		const char* Klass_Namespace{}; //!< Namespace
		const char* Klass_Name{}; //!< Class Name
		char* Klass_Full_Name{}; //!< Full Name
		const char* Klass_OfA_Name{}; //!< The Name of the Base Class, if any

		/*!*****************************************************************************
		\brief
			Default Constructor for the MonoKlassInfo
		*******************************************************************************/
		MonoKlassInfo();
		/*!*****************************************************************************
		\brief
			Deleted Copy Constructor. This is to prevent copying of the MonoKlassInfo
		\param other
			The other MonoKlassInfo to copy from
		*******************************************************************************/
		MonoKlassInfo(const MonoKlassInfo& other) = delete;
		/*!*****************************************************************************
		\brief
			Deleted Copy Assignment Operator. This is to prevent copying of the
			MonoKlassInfo
		\param other
			The other MonoKlassInfo to copy from
		\return
			The MonoKlassInfo
		*******************************************************************************/
		MonoKlassInfo& operator=(const MonoKlassInfo& other) = delete;

		/*!*****************************************************************************
		\brief
			Move Constructor for the MonoKlassInfo

			This will transfer the ownership of the MonoKlassInfo from the other
			MonoKlassInfo to this MonoKlassInfo. Transfering the pointers and
			other resources.
		\param other
			The other MonoKlassInfo to move from
		*******************************************************************************/
		MonoKlassInfo(MonoKlassInfo&& other) noexcept;
		/*!*****************************************************************************
		\brief
			Move Assignment Operator for the MonoKlassInfo

			This will transfer the ownership of the MonoKlassInfo from the other
			MonoKlassInfo to this MonoKlassInfo. Transfering the pointers and
			other resources.
		\param other
			The other MonoKlassInfo to move from
		\return
			The MonoKlassInfo
		*******************************************************************************/
		MonoKlassInfo& operator=(MonoKlassInfo&& other) noexcept;


		/*!*****************************************************************************
		\brief
			Destructor for the MonoKlassInfo

			This will release the resources held by the MonoKlassInfo releasing any
			allocated memory back to the free store.
		
		*******************************************************************************/
		~MonoKlassInfo();
	};

	/*!*****************************************************************************
	\brief
		Encapsulate a Mono Instance
	*******************************************************************************/
	struct KlassInstance
	{
		MonoKlassInfo* Of_A; //!< The Base Class
		MonoObject* Instance; //!< The Instance

	};
	// Tools
	static std::unique_ptr< SageLoader> loader; //!< The Loader
	static std::unique_ptr<SageAssembler> compiler; //!< The Compiler

	
	static MonoDomain* Default_Domain; //!< The Default Domain
	static std::unordered_map<std::string, MonoDomain*> domains; //!< The Domains
	static std::unordered_map<std::string, MonoAssembly*> assemblies; //!< The Assemblies
	static std::unordered_map<std::string, MonoImage*> images; //!< The Images
	static std::unordered_map<std::string, MonoKlassInfo> klassList; //!< The Klass List

	
	/*!*****************************************************************************
		\brief
			A structure to encapsulate the logic system's output stream

			This structure serves as the middleman between the logic system and the
			Mono runtime. It is used to capture the output of the logic system's scripts
			and provide it to the logic system. This structure will only capture the
			output through the use of internal functions. This allow logging to be
			perform in C++ side.

	*******************************************************************************/
	struct STDOUTCS
	{
		size_t latest_index; //!< The Latest Index
		std::string latest; //!< The Latest Message
		std::vector<std::pair<std::string, size_t>> stdout_stream; //!< The Stream

		/*!*****************************************************************************
		\brief
			Add a message to the output stream.

			This function will add a message to the output stream. if the message is
			the same as the last message, it will increment the count of the last message
			instead of adding a new message which increase efficiency.

		\param message
			The message to add to the output stream
		*******************************************************************************/
		void Add(const char* message); 

		/*!*****************************************************************************
		\brief
			Get the output stream

			This function will return the output stream. This will return a vector of
			pairs of strings and size_t. The string is the message and the size_t is the
			count of the message.
		\return
			Vector of pairs of strings and size_t
		*******************************************************************************/
		std::vector<std::pair<std::string, size_t>> Get();
		/*!*****************************************************************************
		\brief
			Clear the output stream

			This function will clear messages logged from the C# output stream, clearing
			the messages from the output stream from the C# side.
		*******************************************************************************/
		void Clear();
	};
	/*!*****************************************************************************
		\brief
			A structure to encapsulate the logic system's error stream

			This structure serves as the middleman between the logic system and the
			Mono runtime. It is used to capture the error output of the logic system's
			scripts and provide it to the logic system. This structure will only capture
			the output through the use of internal functions. This allow logging to be
			perform in C++ side.
	/********************************************************************************/
	struct STDERRCS
	{
		std::string latest; //!< The Latest Message
		std::map<std::string, size_t> stdout_stream; //!< The Stream

		/*!*****************************************************************************
		\brief
			Add a message to the error stream.

			This function will add a message to the error stream. if the message is
			the same as the last message, it will increment the count of the last message
			instead of adding a new message which increase efficiency.

		\param message
			The message to add to the error stream
		*******************************************************************************/
		void Add(const char* message);
		/*!*****************************************************************************
		\brief
			Clear the error stream

			This function will clear messages logged from the C# error stream, clearing
			the messages from the error stream from the C# side.
		*******************************************************************************/
		void Clear();
		/*!*****************************************************************************
		\brief
			Get the error stream

			This function will return the error stream. This will return a vector of
			pairs of strings and size_t. The string is the message and the size_t is the
			count of the message.
		\return
			Vector of pairs of strings and size_t
		*******************************************************************************/
		std::vector<std::pair<std::string, size_t>> Get();
	};


	static STDOUTCS output_stream; //!< The Output Stream
	static STDERRCS error_stream; //!< The Error Stream





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

	static MonoClass* Load_Klass_In_Image(MonoImage* Image, const char* _klass_name, const char* _klass_namespace = nullptr);
	static MonoObject* Create_Instance(MonoClass* _klass, bool do_not_instantiate = false);

	//------Retrieval-----

	static MonoKlassInfo* Get_Klass_Info(const char* _klass_name, const char* _namespace = nullptr);
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