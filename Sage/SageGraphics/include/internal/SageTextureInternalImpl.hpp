/* Start Header ************************************************************************/
/*!
\file		SageTextureInternalImpl.hpp
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contains the declaration for the implementation class use by the PIMPL
			idiom.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#ifndef SAGE_TEXTURE_INTERNAL_IMPL_HPP
#define SAGE_TEXTURE_INTERNAL_IMPL_HPP
#include "SageTexture.h"
#include "SageTextureInternal.hpp"

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
	SageTextureInternalImpl();

	/*!*****************************************************************************
	\brief
		An overloaded constructor for SageTextureInternalImpl

	\param _path
		The texture path

	\param _type
		The texture type
	*******************************************************************************/
	SageTextureInternalImpl(std::string const& _path, int _type);

	/*!*****************************************************************************
	\brief
		A destructor for SageTextureInternalImpl to access the unload function
		of SageTextureInternal
	*******************************************************************************/
	~SageTextureInternalImpl();

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
	int load(const char* src, TEXTURE_UNIT_TYPE const& _type);

	/*!*****************************************************************************
	\brief
		Function to bind the texture by accessing bind texture function of
		SageTextureInternalImpl which calls SageTextureInternal

	\return
		Return a boolean value
	*******************************************************************************/
	bool bind_texture() const;

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to call SageTextureInternal unload function
	*******************************************************************************/
	void unload();

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to get texture unit

	\return
		An int value
	*******************************************************************************/
	int get_unit() const;

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to set texture to repeat by accessing
		SageTexture function
	*******************************************************************************/
	void set_texture_repeat() const;
	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to set texture to clamp by accessing
		SageTexture function
	*******************************************************************************/
	void set_texture_clamp() const;

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to set texture to mirror repeat by
		accessing SageTexture function
	*******************************************************************************/
	void set_texture_mirror_repeat() const;

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to get the texture handle

	\return
		Return an unsigned int value
	*******************************************************************************/
	unsigned int get_handle() const;

	/*!*****************************************************************************
	\brief
		Function of SageTextureInternalImpl to check if a texture is loaded or not

	\return
		A boolean value
	*******************************************************************************/
	bool is_loaded_texture() const;
};

#endif