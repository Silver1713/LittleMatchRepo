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
#include "SageTexture.h"
#include <iostream>

class SageTexture::SageTextureInternalImpl
{
	std::string texture_path{};
	unsigned int texture_handle;
	int texture_unit;
	int texture_type;

	bool is_loaded = false;

public:

	SageTextureInternal texture_internal;
	
	/*!*****************************************************************************
	\brief
		A constructor for SageTextureInternalImpl
	*******************************************************************************/
	SageTextureInternalImpl()
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
	SageTextureInternalImpl(std::string const& _path, int _type) : texture_path(_path), texture_handle(0), texture_unit(0), texture_type(_type), texture_internal(_path, _type)
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
	~SageTextureInternalImpl()
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
	int load(const char* src, TEXTURE_UNIT_TYPE const& _type)
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
	bool bind_texture() const
	{

		return texture_internal.bind_texture();
	}

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to call SageTextureInternal unload function
	*******************************************************************************/
	void unload()
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
	int get_unit() const
	{
		return texture_unit;
	}

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to set texture to repeat by accessing
		SageTexture function
	*******************************************************************************/
	void set_texture_repeat() const
	{
		texture_internal.set_texture_repeat();
	}

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to set texture to clamp by accessing
		SageTexture function
	*******************************************************************************/
	void set_texture_clamp() const
	{
		texture_internal.set_texture_clamp();
	}

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to set texture to mirror repeat by
		accessing SageTexture function
	*******************************************************************************/
	void set_texture_mirror_repeat() const
	{
		texture_internal.set_texture_mirror_repeat();
	}

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to get the texture handle

	\return
		Return an unsigned int value
	*******************************************************************************/
	unsigned int get_handle() const
	{
		return texture_handle;
	}

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to check if a texture is loaded or not

	\return
		A boolean value
	*******************************************************************************/
	bool is_loaded_texture() const
	{
		return is_loaded;
	}
};

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
		texture_id = _other.get_texture_handle();
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
int SageTexture::get_texture_handle() const {
	return texture_id;
}

/*!*****************************************************************************
\brief
	Function of SageTexture to get the texture unit

\return
	Return an int value object
*******************************************************************************/
int SageTexture::get_texture_unit() const {
	return texture_unit;
}

// Setters
/*!*****************************************************************************
\brief
	Function of SageTexture to set the texture mode to repeat (default mode)
*******************************************************************************/
void SageTexture::setTextureRepeat() {
	sage_internal_impl->set_texture_repeat();
}

/*!*****************************************************************************
\brief
	Function of SageTexture to set the texture mode to clamp
*******************************************************************************/
void SageTexture::setTextureClamp() {
	sage_internal_impl->set_texture_clamp();
}

/*!*****************************************************************************
\brief
	Function of SageTexture to set the texture mode to mirror repeat
*******************************************************************************/
void SageTexture::setTextureMirrorRepeat() {
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
void SageTexture::load_texture(const char* _filepath, TEXTURE_UNIT_TYPE _type)
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
bool SageTexture::bind_texture()
{
	return sage_internal_impl->bind_texture();
}



