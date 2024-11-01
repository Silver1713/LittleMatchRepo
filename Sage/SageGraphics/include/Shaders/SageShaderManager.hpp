/* Start Header ************************************************************************/
/*!
\file		SageShaderManager.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		A shader manager that allow multiple shader program to be compiled linked and
			managed.
*/
/* End Header **************************************************************************/

#ifndef SAGESHADERMANAGER_HPP
#define  SAGESHADERMANAGER_HPP
#include <string>
#include <map>
#include "SageShader.hpp"

/*!*****************************************************************************
	\brief
		Encapsulate a shader manager in the rendering engine.

		The shader manager manges the shade rprogram and allow the creation
		of the given shader program by searching for the vertex and fragment shader
		in the list of directory provided by the buckets.

*******************************************************************************/
struct SageShaderManager
{
	static std::string prev_found_shader_dir; //!< The previous directory used.
	static std::map<std::string, std::string> shader_buckets; //!< List of directories to find shaders file from.

	static std::map<std::string, SageShader> shaders; //!< The list of shader program.

	/*!*****************************************************************************
	\brief
		Create a shader program given the vertex and fragment shader relative
		path.

		This function will create a shader program and return a Shader object,
		given a vertex and fragment shader file path.
	\param vertex_shader_path
		Path to the vertex shader source
	\param fragment_shader_path
		Path to the fragment shader source.
	\return
		The created shader program.
	*******************************************************************************/
	static SageShader& Create_Shader_Program(std::string name, const char* vertex_shader_path, const char* fragment_shader_path);
	/*!*****************************************************************************
	\brief
		Create a shader program given the vertex and fragment shader file name.

		This function will perform a lookup on any cached directory in the data
		member. When the file is not found, it will then perform a lookup on the list
		of directories in the bucket. When the fragment and the vertex shader is found,
		it will compile the source and link it and create a shader program and
		returning it as output.
	\param vertex_shader_name
		File name of the vertex shader
	\param fragment_shader_path
		File name of the fragment shader
	\return
		The created shader program.
	*******************************************************************************/
	static SageShader& Search_And_Create_Shader_Program(const char * name, const char* vertex_shader_name, const char* fragment_shader_name);
	/*!*****************************************************************************
	\brief
		Helper function to perform a lookup on the file with the given directories
		list in the data member.
	\param name
		The name of the file.
	\return
		The path to the file.
	*******************************************************************************/
	static std::string Get_Shader_File_Path(std::string const& name);
	/*!*****************************************************************************
	\brief
		Add a idrectory to be included when looking up on a file.
	\param name
		The name of the directory
	\param dir
		The path to the directories
	*******************************************************************************/
	static void Add_Shader_Include(const char * name, const char * dir);

	static  SageShader& Get_Shader_Program(std::string name);
};

#endif // SAGESHADERMANAGER_HPP