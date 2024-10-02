/* Start Header ************************************************************************/
/*!
\file		SageCameraImpl.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The PIMPL implementation of the SageCamera class that is used to facilitate calls to the
			private interface that implements the camera.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

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
	static std::string get_shader_file_path(std::string const& name);
	static void add_shader_include(const char * name, const char * dir);
};

#endif // SAGESHADERMANAGER_HPP