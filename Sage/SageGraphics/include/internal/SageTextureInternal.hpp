/* Start Header ************************************************************************/
/*!
\file		SageTextureInternal.hpp
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contains the SageTextureInternal class and declaration of functions that will
			interact with SOIL and create an openGL texture object.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#ifndef SAGE_TEXTURE_INTERNAL_HPP
#define SAGE_TEXTURE_INTERNAL_HPP
#define SOIL_ENABLE 1
#include <string>
#include <GL/glew.h>

// For stb implementation (not implemented)
#if SOIL_ENABLE == 1
#include <SOIL.h>
#else
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

class SageTextureInternal
{
	/*!*****************************************************************************
	\brief
		An enum class that specify the texture unit type
	*******************************************************************************/
	enum class INTERNAL_TEXTURE_UNIT_TYPE
	{
		SAGE_COLOR_TEXTURE_UNIT = GL_TEXTURE0, // Diffuse
		SAGE_NORMAL_TEXTURE_UNIT = GL_TEXTURE1, // Normal
		SAGE_SPECULAR_TEXTURE_UNIT = GL_TEXTURE2, // Specular
		SAGE_SHADOW_TEXTURE_UNIT = GL_TEXTURE3 // Shadow

	};

	/*!*****************************************************************************
	\brief
		An enum class that specify the texture errors
	*******************************************************************************/
	enum class INTERNAL_SAGE_TEXTURE_ERRORS
	{
		I_SAGE_TEXTURE_NO_ERROR = 0, // Okay
		I_SAGE_TEXTURE_FILE_NOT_FOUND = 1, // Not found
		I_SAGE_TEXTURE_BIND_ERROR = 2, // Cannot bind
		I_SAGE_TEXTURE_UNLOAD_ERROR = 3 // Cannot unload
	};

private:
	std::string texture_path;
	GLuint texture_hdl;
	GLint texture_unit;

	int erro_no;
	std::string error_string;

public:
	/*!*****************************************************************************
	\brief
		A constructor for SageTextureInternal class
	*******************************************************************************/
	SageTextureInternal();

	/*!*****************************************************************************
	\brief
		An overloaded constructor for SageTextureInternal class

	\param _path
		A path for the texture

	\param _type
		A texture tpye
	*******************************************************************************/
	SageTextureInternal(std::string const& _path, int _type=0);

	/*!*****************************************************************************
	\brief
		An overloaded constructor for SageTextureInternal class

	\param _other
		Another texture object
	*******************************************************************************/
	SageTextureInternal(const SageTextureInternal& _other);

	/*!*****************************************************************************
	\brief
		A copy assignment operator of SageTextureInternal class

	\param _other
		Another texture object
	*******************************************************************************/
	SageTextureInternal& operator=(const SageTextureInternal& _other);
	
	//Getters
	/*!*****************************************************************************
	\brief
		Function to get the texture handle

	\return
		Return an unsigned int value
	*******************************************************************************/
	unsigned int get_texture_handle() const;

	/*!*****************************************************************************
	\brief
		Function to get the texture unit

	\return
		Return an int value
	*******************************************************************************/
	int get_texture_unit() const;

	/*!*****************************************************************************
	\brief
		Function to set the texture mode to repeat
	*******************************************************************************/
	void set_texture_repeat() const;

	/*!*****************************************************************************
	\brief
		Function to set the texture mode to clamp
	*******************************************************************************/
	void set_texture_clamp() const;

	/*!*****************************************************************************
	\brief
		Function to set the texture mode to mirror repeat
	*******************************************************************************/
	void set_texture_mirror_repeat() const;

	/*!*****************************************************************************
	\brief
		Function to load the texture

	\param _name
		Name of texture

	\param _type
		Type of texture

	\return
		An int value
	*******************************************************************************/
	int load(const char * _name, int _type=0);

	/*!*****************************************************************************
	\brief
		Function to bind the texture

	\return
		A bool value
	*******************************************************************************/
	bool bind_texture() const;

	/*!*****************************************************************************
	\brief
		Function to unload the texture
	*******************************************************************************/
	void unload();

};

#endif // !SAGE_TEXTURE_INTERNAL_HPP