/* Start Header ************************************************************************/
/*!
\file		SageAssembler.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		This file contains the declaration for the SageAssembler class.

			SageAssembler is a middle man class that will calls the external CS assembler
			to compile the c sharp scripts into a dll/exe file. It contain declaration of
			functions that takes in a C# script in both string and file format and compile
			it into a C# assembly file. The assembly file will be loaded into the mono
			runtime and executed.

			All content  2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#ifndef SAGE_ASSEMBLER_HPP
#define SAGE_ASSEMBLER_HPP

#include <thread>
#include <vector>
#include <string>
class SageAssembler
{
	size_t script_to_tread_ratio; //!< How many scripts that the assembler can accept to compile per thread
	std::thread::id thread_id; //!< The thread id of the current thread that is compiling the scripts.
	std::string log; //!< The log of the current thread that is compiling the scripts. (For debugging purposes)
	std::string data; //!< The data of the current thread that is compiling the scripts. (For debugging purposes)

	std::string path_to_compiler_dir{}; //!< The path to the C# compiler
	std::string output_directory; //!< The output directory of the compiled C# scripts
	std::vector<std::pair<std::string, std::string>> scripts; //!< The scripts that are to be compiled (name,content)


	std::string command; //!< The command that will be executed to compile the scripts
	std::string flags; //!< The flags that will be passed to the compiler


	std::thread worker; //!< The thread that will compile the scripts


	struct SageAssembly {
		std::string name;
		std::string path_to_assembly;
	};

	

public:
	SageAssembler(size_t script_to_tread_ratio = 1); //!< Constructor
	SageAssembler(std::string& name, std::string& content); //!< Constructor
	
	SageAssembler(std::vector<std::pair<std::string, std::string>> scripts); //!< Constructor
	SageAssembler(std::initializer_list<std::pair<std::string, std::string>> scripts); //!< Constructor


	SageAssembler(SageAssembler&& other) noexcept = delete; //!< Move constructor
	SageAssembler(SageAssembler const& other) = delete; //!< Copy constructor
	//~SageAssembler(); //!< Destructor


	void Init(char const* compiler_path, char const* ouput_dir); //!< Initialize the assembler

	void Set_Path_To_Compiler(std::string const& path); //!< Set the path to the C# compiler
	void Set_Output_Directory(std::string const& path); //!< Set the output directory of the compiled C# scripts
	void Set_Command(std::string const& command); //!< Set the command that will be executed to compile the scripts
	void Set_Compile_Flags(std::string const& flags); //!< Set the flags that will be passed to the compiler
	

	std::string Get_Log() const; //!< Get the log of the current thread that is compiling the scripts. (For debugging purposes)
	std::string Get_Path_To_Compiler() const; //!< Get the path to the C# compiler
	std::string Get_Output_Directory() const; //!< Get the output directory of the compiled C# scripts
	std::string Get_Command() const; //!< Get the command that will be executed to compile the scripts
	std::string Get_Compile_Flags() const; //!< Get the flags that will be passed to the compiler


	// Threading functions
	std::thread::id Get_Thread_ID() const; //!< Get the thread id of the current thread that is compiling the scripts.
	bool Check_Running() const; //!< Check if the current thread that is compiling the scripts is running.
	void Join(); //!< Join the current thread that is compiling the scripts.
	void Detach(); //!< Detach the current thread that is compiling the scripts.

	// Script functions
	void Add_Script(std::string const& name, std::string const& content); //!< Add a script to the list of scripts that are to be compiled
	void Add_Script(std::pair<std::string, std::string> const& script); //!< Add a script to the list of scripts that are to be compiled
	void Add_Scripts(std::vector<std::pair<std::string, std::string>> const& scripts); //!< Add a list of scripts to the list of scripts that are to be compiled
	void Add_Scripts(std::initializer_list<std::pair<std::string, std::string>> const& scripts); //!< Add a list of scripts to the list of scripts that are to be compiled
	
	void Clear_Scripts(); //!< Clear the list of scripts that are to be compiled


	void CompileGroup(); //!< Compile the scripts that are in the list of scripts that are to be compiled
	void Compile(std::string const& name, std::string const& content); //!< Compile a script
	void Compile(std::pair<std::string, std::string> const& script); //!< Compile a script
	




};
#endif // SAGE_ASSEMBLER_HPP