#ifndef SAGESHADERMANAGER_HPP
#define  SAGESHADERMANAGER_HPP
#include <string>
#include <map>
#include "SageShader.hpp"


struct SageShaderManager
{
	static std::string prev_found_shader_dir;
	static std::map<std::string, std::string> shader_buckets;

	static std::map<std::string, SageShader> shaders;
	static SageShader& CreateShaderProgram(std::string name, const char* vertex_shader_path, const char* fragment_shader_path);
	static SageShader& search_and_create_shader_program(const char * name, const char* vertex_shader_name, const char* fragment_shader_name);
	static std::string get_shader_file_path(std::string& name);
	static void add_shader_include(const char * name, const char * dir);
};

#endif // SAGESHADERMANAGER_HPP