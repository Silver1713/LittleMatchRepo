

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
	/*!
	 * Enum class for texture unit type
	 */
	enum class TEXTURE_UNIT_TYPE
	{
		SAGE_COLOR_TEXTURE_UNIT = 0, //!< Color texture unit
		SAGE_NORMAL_TEXTURE_UNIT = 1, //!< Normal texture unit
		SAGE_SPECULAR_TEXTURE_UNIT = 2, //!< Specular texture unit
		SAGE_SHADOW_TEXTURE_UNIT = 3, //!< Shadow texture unit

	};
	/*!
	 * Enum class for texture errors
	 */
	enum class SAGE_TEXTURE_ERRORS
	{
		SAGE_TEXTURE_NO_ERROR = 0, //! < No error
		SAGE_TEXTURE_FILE_NOT_FOUND = 1, //!< File not found
		SAGE_TEXTURE_BIND_ERROR = 2, //!< Error binding texture
		SAGE_TEXTURE_UNLOAD_ERROR = 3 //! < Error unloading texture
	};

	/*!
	 * Default constructor for SageTexture
	 */
	SageTexture();
	/*!
	 * Constructor for SageTexture
	 * @param name  path to texture
	 * @param type Texture unit type
	 */
	SageTexture(const char* name, TEXTURE_UNIT_TYPE type);
	/*!
	 * Copy constructor for SageTexture
	 * @param other SageTexture to copy
	 */
	SageTexture(const SageTexture& other);
	/*!
	 * Assignment operator for SageTexture
	 * @param other SageTexture to copy
	 * @return SageTexture
	 */
	SageTexture& operator=(const SageTexture& other);
	/*!
	 *  Destructor for SageTexture
	 * @param other SageTexture to move
	 */
	~SageTexture();
	// Getters
	/*!
	 * Get the texture handle
	 * @return int texture handle
	 */
	int get_texture_handle() const;
	/*!
	 * Get the texture unit
	 * @return int texture unit
	 */
	int get_texture_unit() const;

	// Setters
	/*!
	 * Set the texture unit
	 * @param unit texture unit
	 */
	void setTextureRepeat();
	/*!
	 * Set the texture unit
	 * @param unit texture unit
	 */
	void setTextureClamp();
	/*!
	 * Set the texture unit
	 * @param unit texture unit
	 */
	void setTextureMirrorRepeat();
	/*!
	 * Set the texture unit
	 * @param unit texture unit
	 */
	void load_texture(const char* filepath, TEXTURE_UNIT_TYPE type);
	/*!
	 * Bind the texture
	 * @return true if successful
	 */
	bool bind_texture();
};


#endif // !SAGE_TEXTURE_HPP