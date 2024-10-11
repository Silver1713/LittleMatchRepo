/* Start Header ************************************************************************/
/*!
\file		SageAssembler.cpp
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

#include "SageAssembler.hpp"

#include <fstream>
#include <iostream>

SageAssembler::SageAssembler(size_t _script_to_thread_ratio) : script_to_tread_ratio{ _script_to_thread_ratio }, thread_id{}, worker{},
                                                               path_to_compiler_dir{}, output_directory{}, scripts{}, command{}, flags{}, log{}, data{}
{
}


void SageAssembler::Init(char const* compiler_path, char const* ouput_dir)
{
	path_to_compiler_dir = compiler_path;
	output_directory = ouput_dir;
}

void SageAssembler::Set_Path_To_Compiler(std::string const& path)
{
	path_to_compiler_dir = path;
}

void SageAssembler::Set_Command(std::string const& command)
{
	this->command = command;
}

void SageAssembler::Set_Compile_Flags(std::string const& flags)
{
	this->flags = flags;
}

void SageAssembler::Set_Output_Directory(std::string const& path)
{
	output_directory = path;
}

std::string SageAssembler::Get_Command() const
{
	return command;
}

std::string SageAssembler::Get_Compile_Flags() const
{
	return flags;
}
std::string SageAssembler::Get_Log() const
{
	return log;
}

std::string SageAssembler::Get_Output_Directory() const
{
	return output_directory;
}
std::string SageAssembler::Get_Path_To_Compiler() const
{
	return path_to_compiler_dir;
}
std::thread::id SageAssembler::Get_Thread_ID() const
{
	return thread_id;
}

void SageAssembler::Compile(std::string const& name, std::string const& content)
{
	std::string compile_command = path_to_compiler_dir  + command;

	std::ifstream file{ compile_command };

	if (!file.is_open())
	{
		log = "Failed to open compiler";
		return;
	}

	file.close();

	std::string output_path = output_directory + "\\" + name + ".dll";

	// Make a temp cs file
	std::ofstream temp_file{ output_directory + "\\" + name + "T00.cs" };

	temp_file.write(content.c_str(), content.size());

	temp_file.close();


	std::cout << "File created in " << output_directory << std::endl;

	

	std::string temp_file_path = output_directory + "\\" + name + "T00.cs";

	// Call the compiler

	std::string actual_command = compile_command + " " + flags + " " + temp_file_path + " -out:" + output_path;

	int syscall_status = system(actual_command.c_str());
	system("echo %CD%");

	if (syscall_status)
	{
		log = "Failed to compile";
		std::cout << "Failed to compile" << std::endl;
		return;
	}
	else {
		log = "Compiled successfully";
	}
	// Delete the temp file
	int a  = remove(temp_file_path.c_str());
	if (!a)
	{
		std::cout << "File deleted successfully" << std::endl;
	}
	


	std::cout << "Compiled " << name << " into " << output_path << std::endl;

}






















