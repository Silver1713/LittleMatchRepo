#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <fstream>

// Create class for texture	

class SageTexture {

	enum TEXTURE_UNIT_TYPE
	{
		SAGE_COLOR_TEXTURE_UNIT = GL_TEXTURE0,
		SAGE_NORMAL_TEXTURE_UNIT = GL_TEXTURE1,
		SAGE_SPECULAR_TEXTURE_UNIT = GL_TEXTURE2,
		SAGE_SHADOW_TEXTURE_UNIT = GL_TEXTURE3

	};

private:
	unsigned int texture_id;
	unsigned int texture_unit;
	std::string texture_path;
	std::vector<unsigned char> texture_data;
	static int  tex_count;
public:
	SageTexture() = delete;
	SageTexture(const char* name, TEXTURE_UNIT_TYPE type = SAGE_NORMAL_TEXTURE_UNIT);
	SageTexture(const SageTexture& other);
	SageTexture& operator=(const SageTexture& other);
	~SageTexture();
	// Getters
	int getTextureID() const;
	int getTextureUnit() const;

	// Setters
	void setTextureRepeat();
	void setTextureClamp();	
	void setTextureMirrorRepeat();
};