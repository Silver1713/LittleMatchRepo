/* Start Header ************************************************************************/
/*!
\file		SageShaderManager.cpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		A shader manager that allow multiple shader program to be compiled linked and
			managed.
*/
/* End Header **************************************************************************/
#include "SageHelper.hpp"
#include "SageShader.hpp"
#include "SageShaderManager.hpp"
#include <fstream>
#include <iostream>

std::map<std::string, SageShader> SageShaderManager::shaders;
std::string SageShaderManager::prev_found_shader_dir{};
std::map<std::string, std::string> SageShaderManager::shader_buckets;
SageShader& SageShaderManager::Create_Shader_Program(std::string name, const char* vertex_shader_path, const char* fragment_shader_path)
{
	SageShader shdr = SageHelper::Compile_Shaders_From_File(vertex_shader_path, fragment_shader_path);

	shaders[name] = std::move(shdr);

	return shaders[name];
}

SageShader& SageShaderManager::Search_And_Create_Shader_Program(const char* name, const char* vertex_shader_name, const char* fragment_shader_name)
{
	std::string vertex_shader_path = Get_Shader_File_Path(vertex_shader_name);
	std::string fragment_shader_path = Get_Shader_File_Path(fragment_shader_name);

	if (vertex_shader_path.empty() || fragment_shader_path.empty())
	{
		std::cerr << "Error: Shader file not found." << '\n';
		std::exit(EXIT_FAILURE);
	}

	return Create_Shader_Program(name, vertex_shader_path.c_str(), fragment_shader_path.c_str());

}


void SageShaderManager::Add_Shader_Include(const char* name, const char* dir)
{
	shader_buckets[name] = dir;
}

std::string SageShaderManager::Get_Shader_File_Path(std::string const& name) 
{
	if (shader_buckets.empty())
	{
		return {};
	}

	if (!(prev_found_shader_dir.empty()))
	{
		
		std::ifstream file{ prev_found_shader_dir + name + ".glsl" };
		if (file.is_open())
		{
			file.close();
			std::string	 path = prev_found_shader_dir + name + ".glsl";
			prev_found_shader_dir.clear();
			return path;
		}
		else
		{
			prev_found_shader_dir.clear();
		}

	}

	// loop through the directories and find the file that matches the name
	for (std::pair<const std::string, std::string>& val : shader_buckets)
	{
		std::string path = val.second + name + ".glsl";
		std::ifstream file{ path };

		if (file.is_open())
		{
			prev_found_shader_dir = val.second;
			file.close();
			return path;
		}
	}
	return {};
}


SageShader& SageShaderManager::Get_Shader_Program(std::string name)
{
	if (shaders.contains(name))
	{
		return shaders[name];
	}
	else
	{
		std::cerr << "Error: Shader not found." << '\n';
		throw "Error: Shader not found.";
	}
}






