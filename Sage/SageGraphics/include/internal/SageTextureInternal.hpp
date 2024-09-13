// Internal class for SageTexture
#ifndef SAGE_TEXTURE_INTERNAL_HPP
#define SAGE_TEXTURE_INTERNAL_HPP
#define SOIL_ENABLE 1
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#if SOIL_ENABLE == 1
#else

#endif


class SageTextureInternal
{
	enum TEXTURE_UNIT_TYPE
	{
		SAGE_COLOR_TEXTURE_UNIT = GL_TEXTURE0,
		SAGE_NORMAL_TEXTURE_UNIT = GL_TEXTURE1,
		SAGE_SPECULAR_TEXTURE_UNIT = GL_TEXTURE2,
		SAGE_SHADOW_TEXTURE_UNIT = GL_TEXTURE3

	};
private:
	std::string texture_path;
	GLuint texture_hdl;
	GLuint texture_unit;



	// Rule of 3
public:
	SageTextureInternal();
	SageTextureInternal(std::string const& path, TEXTURE_UNIT_TYPE type);
	SageTextureInternal(const SageTextureInternal& other);
	SageTextureInternal& operator=(const SageTextureInternal& other);

	SageTextureInternal(std::string const& path);
	
	//Getter

	int get_texture_handle() const;
	int get_texture_unit() const;


	void set_texture_repeat();
	void set_texture_clamp();
	void set_texture_mirror_repeat();


	// load, and bind texture
	void load(const char * name);

	void bind_texture();



};


#endif // !SAGE_TEXTURE_INTERNAL_HPP