#include "SageTexture.h"

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <SOIL.h>


int SageTexture::tex_count{};
SageTexture::SageTexture(const char* source) : texture_path(source){
	
	texture_id = SOIL_load_OGL_texture(texture_path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT);
	std::cout << SOIL_last_result();
	texture_unit = ++tex_count;
	glBindTextureUnit(texture_unit, texture_id);
	setTextureRepeat();
}

SageTexture::SageTexture(const SageTexture& other) :  texture_path(other.texture_path) {
	if (this != &other)
	{
		texture_id = SOIL_load_OGL_texture(texture_path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT);
		texture_unit = tex_count++;
		glBindTextureUnit(texture_unit, texture_id);
		setTextureRepeat();
	}
}

SageTexture& SageTexture::operator=(const SageTexture& other) {
	if (this != &other) {
		texture_path = other.texture_path;
	}
	return *this;
}

// Getters
int SageTexture::getTextureID() const {
	return texture_id;
}

int SageTexture::getTextureUnit() const {
	return texture_unit;
}

// Setters
// Default state
void SageTexture::setTextureRepeat() {
	glTextureParameteri(texture_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(texture_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void SageTexture::setTextureClamp() {
	glTextureParameteri(texture_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texture_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void SageTexture::setTextureMirrorRepeat() {
	glTextureParameteri(texture_id, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTextureParameteri(texture_id, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
}

SageTexture::~SageTexture()
{
//	glDeleteTextures(1, reinterpret_cast<GLuint*>( & texture_id));
	tex_count--;
}


