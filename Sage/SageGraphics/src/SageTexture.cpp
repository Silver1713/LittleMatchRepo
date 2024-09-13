#include "SageTexture.h"
#include "GLFW/glfw3.h"
#include "GL/glew.h"
#include <SOIL.h>

int SageTexture::tex_count{};
SageTexture::SageTexture(const char* source) : texture_height(0), texture_width(0), texture_path(source){
	texture_id = SOIL_load_OGL_texture(texture_path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT);
	texture_unit = tex_count++;
	glBindTextureUnit(texture_unit, texture_id);
	setTextureRepeat();
}

SageTexture::SageTexture(const SageTexture& other) : texture_height(other.texture_height), texture_width(other.texture_width), texture_path(other.texture_path) {

}

SageTexture& SageTexture::operator=(const SageTexture& other) {
	if (this->texture_width == other.texture_width && this->texture_height == other.texture_height && this->texture_path == other.texture_path) {
		return *this;
	}
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

