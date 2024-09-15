#ifndef SAGE_TEXTURE_HPP
#define SAGE_TEXTURE_HPP
#include <string>
#include <memory>
// Create class for texture	

class SageTexture {

	

private:
	class SageTextureInternalImpl;
	std::unique_ptr<SageTextureInternalImpl> sage_internal_impl;
	unsigned int texture_id{};
	unsigned int texture_unit{};
	std::string texture_path;
public:
	enum class TEXTURE_UNIT_TYPE
	{
		SAGE_COLOR_TEXTURE_UNIT = 0,
		SAGE_NORMAL_TEXTURE_UNIT = 1,
		SAGE_SPECULAR_TEXTURE_UNIT = 2,
		SAGE_SHADOW_TEXTURE_UNIT = 3

	};

	enum class SAGE_TEXTURE_ERRORS
	{
		SAGE_TEXTURE_NO_ERROR = 0,
		SAGE_TEXTURE_FILE_NOT_FOUND = 1,
		SAGE_TEXTURE_BIND_ERROR = 2,
		SAGE_TEXTURE_UNLOAD_ERROR = 3
	};

	SageTexture();
	SageTexture(const char* name, TEXTURE_UNIT_TYPE type);
	SageTexture(const SageTexture& other);
	SageTexture& operator=(const SageTexture& other);
	~SageTexture();
	// Getters
	int get_texture_handle() const;
	int get_texture_unit() const;

	// Setters
	void setTextureRepeat();
	void setTextureClamp();	
	void setTextureMirrorRepeat();

	void load_texture(const char* filepath, TEXTURE_UNIT_TYPE type);

	bool bind_texture();
};


#endif // !SAGE_TEXTURE_HPP