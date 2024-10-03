/* Start Header ************************************************************************/
/*!
\file		SageTextureInternalImpl.cpp
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contains the definition for the implementation class use by the PIMPL
			idiom.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "SageTextureInternalImpl.hpp"

#include <iostream>
#include <ostream>


/*!*****************************************************************************
	\brief
		A constructor for SageTextureInternalImpl
*******************************************************************************/
SageTexture::SageTextureInternalImpl::SageTextureInternalImpl()
{
	texture_handle = static_cast<unsigned int>(-1);
	texture_unit = -1;
	texture_type = -1;
}
/*!*****************************************************************************
\brief
	An overloaded constructor for SageTextureInternalImpl

\param _path
	The texture path

\param _type
	The texture type
*******************************************************************************/
SageTexture::SageTextureInternalImpl::SageTextureInternalImpl(std::string const& _path, int _type) : texture_path(_path), texture_handle(0), texture_unit(0), texture_type(_type), texture_internal(_path, _type)
{
	texture_internal = SageTextureInternal(texture_path, _type);
	texture_unit = texture_internal.get_texture_unit();
	texture_handle = texture_internal.get_texture_handle();
	is_loaded = true;

}

/*!*****************************************************************************
\brief
	A destructor for SageTextureInternalImpl to access the unload function
	of SageTextureInternal
*******************************************************************************/
SageTexture::SageTextureInternalImpl::~SageTextureInternalImpl()
{
	texture_internal.unload();

}


/*!*****************************************************************************
\brief
	Load function of SageTextureInternalImpl

\param src
	The source of texture

\param _type
	The texture unit

\return
	An int value
*******************************************************************************/
int SageTexture::SageTextureInternalImpl::load(const char* src, TEXTURE_UNIT_TYPE const& _type)
{
	texture_unit = texture_internal.load(src, static_cast<int>(_type));
	texture_path = src;

	texture_handle = texture_internal.get_texture_handle();
	texture_type = static_cast<int>(_type);

	if (texture_unit == -1)
	{
		std::cout << "Error loading texture" << std::endl;
		return -1;
	}
	is_loaded = true;
	return texture_unit;
}

/*!*****************************************************************************
\brief
	Function to bind the texture by accessing bind texture function of
	SageTextureInternalImpl which calls SageTextureInternal

\return
	Return a boolean value
*******************************************************************************/
bool SageTexture::SageTextureInternalImpl::bind_texture() const
{

	return texture_internal.bind_texture();
}
/*!*****************************************************************************
\brief
	Function of SageTextureInternalImpl to call SageTextureInternal unload function
*******************************************************************************/
void SageTexture::SageTextureInternalImpl::unload()
{
	texture_internal.unload();
	is_loaded = false;
}
/*!*****************************************************************************
\brief
	Function of SageTextureInternalImpl to get texture unit

\return
	An int value
*******************************************************************************/
int SageTexture::SageTextureInternalImpl::get_unit() const
{
	return texture_unit;
}
/*!*****************************************************************************
\brief
	Function of SageTextureInternalImpl to set texture to repeat by accessing
	SageTexture function
*******************************************************************************/
void SageTexture::SageTextureInternalImpl::set_texture_repeat() const
{
	texture_internal.set_texture_repeat();
}
/*!*****************************************************************************
\brief
	Function of SageTextureInternalImpl to set texture to clamp by accessing
	SageTexture function
*******************************************************************************/
void SageTexture::SageTextureInternalImpl::set_texture_clamp() const
{
	texture_internal.set_texture_clamp();
}
/*!*****************************************************************************
\brief
	Function of SageTextureInternalImpl to set texture to mirror repeat by
	accessing SageTexture function
*******************************************************************************/
void SageTexture::SageTextureInternalImpl::set_texture_mirror_repeat() const
{
	texture_internal.set_texture_mirror_repeat();
}
/*!*****************************************************************************
\brief
	Function of SageTextureInternalImpl to get the texture handle

\return
	Return an unsigned int value
*******************************************************************************/
unsigned int SageTexture::SageTextureInternalImpl::get_handle() const
{
	return texture_handle;
}
/*!*****************************************************************************
\brief
	Function of SageTextureInternalImpl to check if a texture is loaded or not

\return
	A boolean value
*******************************************************************************/
bool SageTexture::SageTextureInternalImpl::is_loaded_texture() const
{
	return is_loaded;
}