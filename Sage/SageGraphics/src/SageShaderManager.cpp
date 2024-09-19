#include "SageHelper.hpp"
#include "SageShader.hpp"
#include "SageShaderManager.hpp"
#include <fstream>
#include <iostream>

std::map<std::string, SageShader> SageShaderManager::shaders;
std::string SageShaderManager::prev_found_shader_dir{};
std::map<std::string, std::string> SageShaderManager::shader_buckets;
SageShader& SageShaderManager::CreateShaderProgram(std::string name, const char* vertex_shader_path, const char* fragment_shader_path)
{
	SageShader shdr = SageHelper::CompileShadersFromFile(vertex_shader_path, fragment_shader_path);

	shaders[name] = std::move(shdr);

	return shaders[name];
}

SageShader& SageShaderManager::search_and_create_shader_program(const char* name, const char* vertex_shader_name, const char* fragment_shader_name)
{
	std::string vertex_shader_path = get_shader_file_path(vertex_shader_name);
	std::string fragment_shader_path = get_shader_file_path(fragment_shader_name);

	if (vertex_shader_path.empty() || fragment_shader_path.empty())
	{
		std::cerr << "Error: Shader file not found." << '\n';
		std::exit(EXIT_FAILURE);
	}

	return CreateShaderProgram(name, vertex_shader_path.c_str(), fragment_shader_path.c_str());

}


void SageShaderManager::add_shader_include(const char* name, const char* dir)
{
	shader_buckets[name] = dir;
}

std::string SageShaderManager::get_shader_file_path(std::string const& name) 
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






