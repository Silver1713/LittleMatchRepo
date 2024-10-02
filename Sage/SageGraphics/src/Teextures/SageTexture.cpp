#include "SageTextureInternal.hpp"
#include "SageTexture.h"
#include <iostream>

class SageTexture::SageTextureInternalImpl
{
	std::string texture_path{};
	unsigned int texture_handle;
	int texture_unit;
	int _type;

	bool is_loaded = false;
public:

	SageTextureInternal texture_internal;

	SageTextureInternalImpl()
	{
		texture_handle = static_cast<unsigned int>(-1);
		texture_unit = -1;
		_type = -1;

	}

	SageTextureInternalImpl(std::string const& path, int type) : texture_path(path), texture_handle(0), texture_unit(0), _type(type), texture_internal(path, type)
	{
		texture_internal = SageTextureInternal(texture_path, type);
		texture_unit = texture_internal.get_texture_unit();
		texture_handle = texture_internal.get_texture_handle();
		is_loaded = true;

	}

	~SageTextureInternalImpl()
	{
		texture_internal.unload();

	}

	int load(const char* src, TEXTURE_UNIT_TYPE const& type)
	{
		texture_unit = texture_internal.load(src, static_cast<int>(type));
		texture_path = src;

		texture_handle = texture_internal.get_texture_handle();
		_type = static_cast<int>(type);

		if (texture_unit == -1)
		{
			std::cout << "Error loading texture" << std::endl;
			return -1;
		}
		is_loaded = true;
		return texture_unit;
	}
	bool bind_texture() const
	{

		return texture_internal.bind_texture();
	}
	void unload()
	{
		texture_internal.unload();
		is_loaded = false;
	}

	int get_unit() const
	{
		return texture_unit;
	}

	void set_texture_repeat() const
	{
		texture_internal.set_texture_repeat();
	}
	void set_texture_clamp() const
	{
		texture_internal.set_texture_clamp();
	}
	void set_texture_mirror_repeat() const
	{
		texture_internal.set_texture_mirror_repeat();
	}
	unsigned int get_handle() const
	{
		return texture_handle;
	}

	bool is_loaded_texture() const
	{
		return is_loaded;
	}
};

SageTexture::SageTexture() : sage_internal_impl(std::make_unique<SageTextureInternalImpl>()),texture_unit(static_cast
	                             <unsigned int>(-1)),texture_id(static_cast
	                             <unsigned int>(-1)) {
	

}

SageTexture::SageTexture(const char* source, TEXTURE_UNIT_TYPE type) : texture_path(source), sage_internal_impl(std::make_unique<SageTextureInternalImpl>(source, static_cast
	<int>(type))) {
	texture_id = sage_internal_impl->get_handle();
	texture_unit = sage_internal_impl->get_unit();

}

SageTexture::SageTexture(const SageTexture& other) : texture_path(other.texture_path) {
	if (this != &other)
	{
		//To load or not to load
		texture_id = other.get_texture_handle();
		texture_unit = other.texture_unit;

	}
}

SageTexture& SageTexture::operator=(const SageTexture& other) {
	if (this != &other) {
		texture_path = other.texture_path;
	}
	return *this;
}

// Getters
int SageTexture::get_texture_handle() const {
	return texture_id;
}

int SageTexture::get_texture_unit() const {
	return texture_unit;
}

// Setters
// Default state
void SageTexture::setTextureRepeat() {
	sage_internal_impl->set_texture_repeat();
}

void SageTexture::setTextureClamp() {
	sage_internal_impl->set_texture_clamp();
}

void SageTexture::setTextureMirrorRepeat() {
	sage_internal_impl->set_texture_mirror_repeat();
}

SageTexture::~SageTexture()
{
	sage_internal_impl->unload();
}



void SageTexture::load_texture(const char* filepath, TEXTURE_UNIT_TYPE type)
{
	int status = sage_internal_impl->load(filepath, type);
	if (status == -1)
	{
		std::cout << "Error loading texture" << std::endl;
	}
	texture_path = filepath;
	texture_id = sage_internal_impl->get_handle();
	texture_unit = sage_internal_impl->get_unit();
}

bool SageTexture::bind_texture()
{
	return sage_internal_impl->bind_texture();
}



