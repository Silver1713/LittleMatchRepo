/* Start Header ************************************************************************/
/*!
\file		SageTexture.cpp
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contains the definition for the public interface that will access
			SageTextureInternal functions which will interact with SOIL and openGL

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "SageTextureInternal.hpp"
#include "SageTextureInternalImpl.hpp"
#include "SageTexture.h"
#include <iostream>

/*!*****************************************************************************
\brief
	A constructor for SageTexture
*******************************************************************************/
SageTexture::SageTexture() : sage_internal_impl(std::make_unique<SageTextureInternalImpl>()),texture_unit(static_cast<unsigned int>(-1)), texture_id(static_cast<unsigned int>(-1)) {

}

/*!*****************************************************************************
\brief
	An overloaded constructor for SageTexture class

\param _source
	The sage texture source

\param _type
	Sage texture unit type
*******************************************************************************/
SageTexture::SageTexture(const char* _source, TEXTURE_UNIT_TYPE _type) : texture_path(_source), sage_internal_impl(std::make_unique<SageTextureInternalImpl>(_source, static_cast
	<int>(_type))) {
	texture_id = sage_internal_impl->get_handle();
	texture_unit = sage_internal_impl->get_unit();

}

/*!*****************************************************************************
\brief
	A copy constructor of SageTexture class

\param _other
	Another sage texture object
*******************************************************************************/
SageTexture::SageTexture(const SageTexture& _other) : texture_path(_other.texture_path) {
	if (this != &_other)
	{
		//To load or not to load
		texture_id = _other.Get_Texture_Handle();
		texture_unit = _other.texture_unit;

	}
}

/*!*****************************************************************************
\brief
	A copy assignment operator of SageTexture class

\param _other
	Another sage texture object
*******************************************************************************/
SageTexture& SageTexture::operator=(const SageTexture& _other) {
	if (this != &_other) {
		texture_path = _other.texture_path;
	}
	return *this;
}

// Getters
/*!*****************************************************************************
\brief
	Function of SageTexture to get the texture handle

\return
	An int object
*******************************************************************************/
int SageTexture::Get_Texture_Handle() const {
	return texture_id;
}

/*!*****************************************************************************
\brief
	Function of SageTexture to get the texture unit

\return
	Return an int value object
*******************************************************************************/
int SageTexture::Get_Texture_Unit() const {
	return texture_unit;
}

// Setters
/*!*****************************************************************************
\brief
	Function of SageTexture to set the texture mode to repeat (default mode)
*******************************************************************************/
void SageTexture::Set_Texture_Repeat() {
	sage_internal_impl->set_texture_repeat();
}

/*!*****************************************************************************
\brief
	Function of SageTexture to set the texture mode to clamp
*******************************************************************************/
void SageTexture::Set_Texture_Clamp() {
	sage_internal_impl->set_texture_clamp();
}

/*!*****************************************************************************
\brief
	Function of SageTexture to set the texture mode to mirror repeat
*******************************************************************************/
void SageTexture::Set_Texture_Mirror_Repeat() {
	sage_internal_impl->set_texture_mirror_repeat();
}

/*!*****************************************************************************
\brief
	A destructor to destroy the sage texture object
*******************************************************************************/
SageTexture::~SageTexture()
{
	sage_internal_impl->unload();
}

/*!*****************************************************************************
\brief
	Function of SageTexture to load the texture

\param _filepath
	The file path of loading the texture

\param _type
	The type of the texture unit
*******************************************************************************/
void SageTexture::Load_Texture(const char* _filepath, TEXTURE_UNIT_TYPE _type)
{
	int status = sage_internal_impl->load(_filepath, _type);
	if (status == -1)
	{
		std::cout << "Error loading texture" << std::endl;
	}
	texture_path = _filepath;
	texture_id = sage_internal_impl->get_handle();
	texture_unit = sage_internal_impl->get_unit();
}

/*!*****************************************************************************
\brief
	Function of SageTexture to bind the texture

\return
	Return a boolean object
*******************************************************************************/
bool SageTexture::Bind_Texture()
{
	return sage_internal_impl->bind_texture();
}



