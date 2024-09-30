/* Start Header ************************************************************************/
/*!
\file		SageTextureInternal.cpp
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contains the SageTextureInternal class and definition of the functions that will
			interact with SOIL and openGL and create an openGL texture object.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "SageTextureInternal.hpp"

#include <GL/glew.h>
#include <cassert>
#include <iostream>
#include <ostream>
#include <SOIL.h>

/*!*****************************************************************************
\brief
	A constructor for SageTextureInternal class
*******************************************************************************/
SageTextureInternal::SageTextureInternal() : texture_hdl(0), texture_unit(0), erro_no(0)
{
}

/*!*****************************************************************************
\brief
	An overloaded constructor for SageTextureInternal class
*******************************************************************************/
SageTextureInternal::SageTextureInternal(const SageTextureInternal& other) : texture_hdl(other.texture_hdl),
texture_unit(other.texture_unit), erro_no()
{

}

/*!*****************************************************************************
\brief
	A copy assignment operator of SageTextureInternal class
*******************************************************************************/
SageTextureInternal& SageTextureInternal::operator=(const SageTextureInternal& other)
{
	if (this != &other)
	{
		texture_hdl = other.texture_hdl;
		texture_unit = other.texture_unit;
	}
	return *this;

}

/*!*****************************************************************************
\brief
	A copy constructor of SageTextureInternal class
*******************************************************************************/
SageTextureInternal::SageTextureInternal(std::string const& path, int internal_type) : texture_path(path), texture_hdl(), texture_unit()
{
	switch (internal_type % 4)
	{
	case 0:
		texture_unit = static_cast<GLint>(INTERNAL_TEXTURE_UNIT_TYPE::SAGE_COLOR_TEXTURE_UNIT);
		break;
	case 1:
		texture_unit = static_cast<GLint>(INTERNAL_TEXTURE_UNIT_TYPE::SAGE_NORMAL_TEXTURE_UNIT);
		break;
	case 2:
		texture_unit = static_cast<GLint>(INTERNAL_TEXTURE_UNIT_TYPE::SAGE_SPECULAR_TEXTURE_UNIT);
		break;
	case 3:
		texture_unit = static_cast<GLint>(INTERNAL_TEXTURE_UNIT_TYPE::SAGE_SHADOW_TEXTURE_UNIT);
		break;
	default:
		break;
	}
#if _DEBUG
	GLint max_texture_unit;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &max_texture_unit);

	if (texture_unit - GL_TEXTURE0 > max_texture_unit)
	{
		assert(texture_unit >= 0 && texture_unit < max_texture_unit && "Texture unit out of range");
	}
	
#endif

	texture_unit += (internal_type / 4) * 4;

	texture_hdl = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT);
	if (texture_hdl == 0)
	{
		erro_no = static_cast<int>(INTERNAL_SAGE_TEXTURE_ERRORS::I_SAGE_TEXTURE_FILE_NOT_FOUND);
		std::cerr << "Error loading texture: " << path << std::endl;
		std::cerr << "Error: " << SOIL_last_result() << std::endl;
	}
	set_texture_repeat();
}

/*!*****************************************************************************
\brief
	Function to set the texture mode to repeat
*******************************************************************************/
void SageTextureInternal::set_texture_repeat() const
{
	glTextureParameteri(texture_hdl, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(texture_hdl, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

/*!*****************************************************************************
\brief
	Function to set the texture mode to clamp
*******************************************************************************/
void SageTextureInternal::set_texture_clamp() const
{
	glTextureParameteri(texture_hdl, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texture_hdl, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

/*!*****************************************************************************
\brief
	Function to set the texture mode to mirror repeat
*******************************************************************************/
void SageTextureInternal::set_texture_mirror_repeat() const
{
	glTextureParameteri(texture_hdl, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTextureParameteri(texture_hdl, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
}

/*!*****************************************************************************
\brief
	Function to bind the texture
*******************************************************************************/
bool SageTextureInternal::bind_texture() const
{
	glBindTextureUnit(texture_unit - GL_TEXTURE0, texture_hdl);
	return (glGetError() == GL_NO_ERROR);
}

/*!*****************************************************************************
\brief
	Function to load the texture
*******************************************************************************/
int SageTextureInternal::load(const char* name ,int type)
{
	if (texture_hdl != 0)
	{
		unload();
	}
	texture_hdl = SOIL_load_OGL_texture(name, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y);
	if (texture_hdl == 0)
	{
		std::cerr << "Error loading texture: " << name << std::endl;
		std::cerr << "Error: " << SOIL_last_result() << std::endl;
		// std::exit(1);
	}

	switch (type % 4)
	{
	case 0:
		texture_unit = static_cast<GLint>(INTERNAL_TEXTURE_UNIT_TYPE::SAGE_COLOR_TEXTURE_UNIT);
		break;
	case 1:
		texture_unit = static_cast<GLint>(INTERNAL_TEXTURE_UNIT_TYPE::SAGE_NORMAL_TEXTURE_UNIT);
		break;
	case 2:
		texture_unit = static_cast<GLint>(INTERNAL_TEXTURE_UNIT_TYPE::SAGE_SPECULAR_TEXTURE_UNIT);
		break;
	case 3:
		texture_unit = static_cast<GLint>(INTERNAL_TEXTURE_UNIT_TYPE::SAGE_SHADOW_TEXTURE_UNIT);
		break;
	default:
		break;
	}
#if _DEBUG
	GLint max_texture_unit;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &max_texture_unit);

	if (texture_unit - GL_TEXTURE0 > max_texture_unit)
	{
		assert(texture_unit >= 0 && texture_unit < max_texture_unit && "Texture unit out of range");
	}

#endif

	texture_unit += (type / 4) * 4;

	return texture_unit;
}

/*!*****************************************************************************
\brief
	Function to get the texture handle
*******************************************************************************/
unsigned int SageTextureInternal::get_texture_handle() const
{
	return texture_hdl;
}

/*!*****************************************************************************
\brief
	Function to get the texture unit
*******************************************************************************/
int SageTextureInternal::get_texture_unit() const
{
	return texture_unit;
}

/*!*****************************************************************************
\brief
	Function to unload the texture
*******************************************************************************/
void SageTextureInternal::unload()
{
	glDeleteTextures(1, &texture_hdl);
	texture_hdl = 0;
	texture_unit = -1;
}












