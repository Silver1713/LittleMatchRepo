#include "SageTextureInternal.hpp"

#include <iostream>
#include <ostream>
#include <SOIL.h>
#include <GL/glew.h>





SageTextureInternal::SageTextureInternal() : texture_hdl(0), texture_unit(0)
{
	
}

SageTextureInternal::SageTextureInternal(const SageTextureInternal& other)
{
	if (this != &other)
	{
		texture_hdl = other.texture_hdl;
		texture_unit = other.texture_unit;
	}
}

SageTextureInternal::SageTextureInternal(std::string const& path, SageTextureInternal::TEXTURE_UNIT_TYPE type) : texture_path(path),  texture_hdl(), texture_unit()
{
	texture_hdl = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y);
	if (texture_hdl == 0)
	{
		std::cerr << "Error loading texture: " << path << '\n';
		std::cerr << SOIL_last_result() << '\n';
	}

	texture_unit = type;

	

	

}





