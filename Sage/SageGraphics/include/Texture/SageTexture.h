/* Start Header ************************************************************************/
/*!
\file		SageTexture.h
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		Contains the declaration for the public interface that will access
			SageTextureInternal functions which will interact with SOIL and openGL

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#ifndef SAGE_TEXTURE_HPP
#define SAGE_TEXTURE_HPP
#include <string>
#include <memory>

/*!
 * Class for texture
 */
class SageTexture {

	

private:
	class SageTextureInternalImpl;
	std::unique_ptr<SageTextureInternalImpl> sage_internal_impl;
	unsigned int texture_id{};
	unsigned int texture_unit{};
	std::string texture_path;
public:
	/*!*****************************************************************************
	\brief
		An enum class that specify the texture unit type
	*******************************************************************************/
	enum class TEXTURE_UNIT_TYPE
	{
		SAGE_COLOR_TEXTURE_UNIT = 0, //!< Color texture unit
		SAGE_NORMAL_TEXTURE_UNIT = 1, //!< Normal texture unit
		SAGE_SPECULAR_TEXTURE_UNIT = 2, //!< Specular texture unit
		SAGE_SHADOW_TEXTURE_UNIT = 3, //!< Shadow texture unit

	};
	/*!*****************************************************************************
	\brief
		An enum class that specify the texture errors
	*******************************************************************************/
	enum class SAGE_TEXTURE_ERRORS
	{
		SAGE_TEXTURE_NO_ERROR = 0, //! < No error
		SAGE_TEXTURE_FILE_NOT_FOUND = 1, //!< File not found
		SAGE_TEXTURE_BIND_ERROR = 2, //!< Error binding texture
		SAGE_TEXTURE_UNLOAD_ERROR = 3 //! < Error unloading texture
	};

	/*!*****************************************************************************
	\brief
		A constructor for SageTexture class
	*******************************************************************************/
	SageTexture();

	/*!*****************************************************************************
	\brief
		An overloaded constructor for SageTexture class
	*******************************************************************************/
	SageTexture(const char* name, TEXTURE_UNIT_TYPE type);

	/*!*****************************************************************************
	\brief
		A copy constructor of SageTexture class
	*******************************************************************************/
	SageTexture(const SageTexture& other);

	/*!*****************************************************************************
	\brief
		A copy assignment operator of SageTexture class
	*******************************************************************************/
	SageTexture& operator=(const SageTexture& other);

	/*!*****************************************************************************
	\brief
		A destructor to destroy the sage texture object
	*******************************************************************************/
	~SageTexture();

	// Getters
	/*!*****************************************************************************
	\brief
		Function to get the texture handle
	*******************************************************************************/
	int get_texture_handle() const;

	/*!*****************************************************************************
	\brief
		Function to get the texture unit
	*******************************************************************************/
	int get_texture_unit() const;

	// Setters

	/*!*****************************************************************************
	\brief
		Function to set the texture mode to repeat
	*******************************************************************************/
	void setTextureRepeat();

	/*!*****************************************************************************
	\brief
		Function to set the texture mode to clamp
	*******************************************************************************/
	void setTextureClamp();

	/*!*****************************************************************************
	\brief
		Function to set the texture mode to mirror repeat
	*******************************************************************************/
	void setTextureMirrorRepeat();

	/*!*****************************************************************************
	\brief
		Function to load the texture
	*******************************************************************************/
	void load_texture(const char* filepath, TEXTURE_UNIT_TYPE type);

	/*!*****************************************************************************
	\brief
		Function to bind the texture
	*******************************************************************************/
	bool bind_texture();
};


#endif // !SAGE_TEXTURE_HPP