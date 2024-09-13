#include "SageHelper.hpp"
#include "SageShader.hpp"
#include "SageShaderManager.hpp"

std::map<std::string, SageShader> SageShaderManager::shaders;

SageShader& SageShaderManager::CreateShaderProgram(std::string name, const char* vertex_shader_path, const char* fragment_shader_path)
{
	SageShader shdr = SageHelper::CompileShadersFromFile(vertex_shader_path, fragment_shader_path);

	shaders[name] = std::move(shdr);

	return shaders[name];
}
