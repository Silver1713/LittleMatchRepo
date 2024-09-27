	// Internal class for SageTexture
#ifndef SAGE_TEXTURE_INTERNAL_HPP
#define SAGE_TEXTURE_INTERNAL_HPP
#define SOIL_ENABLE 1
#include <string>
#include <GL/glew.h>
#if SOIL_ENABLE == 1
#include <SOIL.h>
#else
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif


class SageTextureInternal
{
	enum class INTERNAL_TEXTURE_UNIT_TYPE
	{
		SAGE_COLOR_TEXTURE_UNIT = GL_TEXTURE0,
		SAGE_NORMAL_TEXTURE_UNIT = GL_TEXTURE1,
		SAGE_SPECULAR_TEXTURE_UNIT = GL_TEXTURE2,
		SAGE_SHADOW_TEXTURE_UNIT = GL_TEXTURE3

	};
	enum class INTERNAL_SAGE_TEXTURE_ERRORS
	{
		I_SAGE_TEXTURE_NO_ERROR = 0,
		I_SAGE_TEXTURE_FILE_NOT_FOUND = 1,
		I_SAGE_TEXTURE_BIND_ERROR = 2,
		I_SAGE_TEXTURE_UNLOAD_ERROR = 3
	};
private:
	std::string texture_path;
	GLuint texture_hdl;
	GLint texture_unit;

	int erro_no;
	std::string error_string;



	// Rule of 3
public:
	SageTextureInternal();
	SageTextureInternal(std::string const& path, int type=0);
	SageTextureInternal(const SageTextureInternal& other);
	SageTextureInternal& operator=(const SageTextureInternal& other);

	
	
	//Getter

	unsigned int get_texture_handle() const;
	 int get_texture_unit() const;


	void set_texture_repeat() const;
	void set_texture_clamp() const;
	void set_texture_mirror_repeat() const;


	// load, and bind texture
	int load(const char * name, int type=0);

	bool bind_texture() const;

	void unload();



};


#endif // !SAGE_TEXTURE_INTERNAL_HPP