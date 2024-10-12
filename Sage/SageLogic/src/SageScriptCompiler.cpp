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

#include "SageScriptCompiler.hpp"
#include <mono/jit/jit.h>
#include <fstream>
#include <iostream>




std::string const SageAssembler::FILE_MODE = "__FILE_PATH__";
std::mutex SageAssembler::mutex;
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

SageAssembly SageAssembler::Compile(std::string const& name, std::string const& content)
{
	std::string compile_command = path_to_compiler_dir  + command;

	std::ifstream file{ compile_command };

	if (!file.is_open())
	{
		log = "Failed to open compiler";
		return{};
	}

	file.close();

	std::string output_path = output_directory + "\\" + name + ".dll";

	// Make a temp cs file
	std::ofstream temp_file{ output_directory + "\\" + name + "T00.cs" };

	temp_file.write(content.c_str(), content.size());

	temp_file.close();


	std::cout << "File created in " << output_directory << '\n';

	

	std::string temp_file_path = output_directory + "\\" + name + "T00.cs";

	// Call the compiler

	std::string actual_command = compile_command + " " + flags + " " + temp_file_path + " -out:" + output_path;

	int syscall_status = std::system(actual_command.c_str());
	
	

	if (syscall_status)
	{
		log = "Failed to compile";
		std::cout << "Failed to compile" << '\n';
		return {};
	}
	else {
		log = "Compiled successfully";
	}
	// Delete the temp file
	int a  = remove(temp_file_path.c_str());
	if (!a)
	{
		std::cout << "File deleted successfully" << '\n';
	}
	


	std::cout << "Compiled " << name << " into " << output_path << '\n';

	return { name, output_path };

}


SageAssembly SageAssembler::CompileFile(std::string const& path)
{
	std::ifstream file{ path };

	if (!file.is_open())
	{
		log = "Failed to open file";
		return {};
	}
	file.close();

	std::string name = path.substr(path.find_last_of("/") + 1, path.find_last_of("s") - 3 - path.find_last_of("/"));


	std::string compile_command = path_to_compiler_dir + command;

	std::ifstream cmd{ compile_command };

	if (!cmd.is_open())
	{
		log = "Failed to open compiler";
		return{};
	}

	cmd.close();

	std::string output_path = output_directory + "\\" + name + ".dll";

	std::string actual_command = compile_command + " " + flags + " " + path + " -out:" + output_path;

	int syscall_status = std::system(actual_command.c_str());



	if (syscall_status)
	{
		log = "Failed to compile";
		std::cout << "Failed to compile" << '\n';
		return {};
	}
	else {
		log = "Compiled successfully";
	}
	std::cout << "Compiled " << name << " into " << output_path << '\n';

	
	return { name, output_path };

	



}


void SageAssembler::CompileFileAsync(std::string const& path)
{
	std::ifstream file{ path };

	if (!file.is_open())
	{
		log = "Failed to open file";
		return;
	}
	file.close();

	std::string name = path.substr(path.find_last_of("/") + 1, path.find_last_of("s") - 3 - path.find_last_of("/"));


	std::string compile_command = path_to_compiler_dir + command;

	std::ifstream cmd{ compile_command };

	if (!cmd.is_open())
	{
		log = "Failed to open compiler";
		return;
	}

	cmd.close();

	std::string output_path = output_directory + "\\" + name + ".dll";

	std::string actual_command = compile_command + " " + flags + " " + path + " -out:" + output_path;
	
	int syscall_status = std::system(actual_command.c_str());



	if (syscall_status)
	{
		log = "Failed to compile";
		std::cout << "Failed to compile" << '\n';
		return;
	}
	else {
		log = "Compiled successfully";
	}
	std::cout << "Compiled " << name << " into " << output_path << '\n';


	SageAssembly assembly = { name, output_directory + "\\" + name + ".dll" };

	std::lock_guard<std::mutex> lock{ mutex };
	assemblies[name] = assembly;
}


void SageAssembler::CompileGroupAsync()
{

	std::vector<std::thread> threads;

	for (auto& script : scripts)
	{
		if (script.first == "__FILE_PATH__")
		{
			threads.push_back(std::thread{ &SageAssembler::CompileFileAsync, this, script.second });
		}
		else
		{
			threads.push_back(std::thread{ (&SageAssembler::CompileScriptAsync), this, script.first, script.second });
		}
	}


	for (auto& thread : threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
	
}




void SageAssembler::CompileScriptAsync(std::string const& name, std::string const& content)
{
	std::string compile_command = path_to_compiler_dir + command;

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


	std::cout << "File created in " << output_directory << '\n';



	std::string temp_file_path = output_directory + "\\" + name + "T00.cs";

	// Call the compiler

	std::string actual_command = compile_command + " " + flags + " " + temp_file_path + " -out:" + output_path;

	int syscall_status = std::system(actual_command.c_str());



	if (syscall_status)
	{
		log = "Failed to compile";
		std::cout << "Failed to compile" << '\n';
		return;
	}
	else {
		log = "Compiled successfully";
	}
	// Delete the temp file
	int a = remove(temp_file_path.c_str());
	if (!a)
	{
		std::cout << "File deleted successfully" << '\n';
	}



	std::cout << "Compiled " << name << " into " << output_path << '\n';


	std::lock_guard<std::mutex> lock{ mutex };	
	assemblies[name] = { name, output_path };
}


void SageAssembler::StartCompilation()
{
	worker = std::thread{ &SageAssembler::CompileGroupAsync, this };
	thread_id = worker.get_id();

}

void SageAssembler::Wait_For_Compile()
{
	if (worker.joinable())
	{
		worker.join();
	}
	std::cout.flush();
}


SageAssembly SageAssembler::Get_Assembly(std::string const& name)
{
	return assemblies[name];
}


void SageAssembler::Add_Script(std::string const& name, std::string const& content)
{
	scripts.push_back({ name, content });
}






















