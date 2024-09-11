#ifndef SAGESHADERMANAGER_HPP
#define  SAGESHADERMANAGER_HPP
#include <string>
#include <map>
#include "SageShader.hpp"


struct SageShaderManager
{
	static std::map<std::string, SageShader> shaders;
	static SageShader& CreateShaderProgram(std::string name, const char* vertex_shader_path, const char* fragment_shader_path);

};

#endif // SAGESHADERMANAGER_HPP