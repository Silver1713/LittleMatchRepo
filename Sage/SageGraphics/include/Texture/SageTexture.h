#pragma once
#include <string>
#include <vector>
#include <fstream>

// Create class for texture	

class SageTexture {

private:
	int texture_id;
	int texture_width;
	int texture_height;
	int bytes_per_texel;
	int texture_unit;
	std::string texture_path;
	std::vector<unsigned char> texture_data;
	int colour_channel;
	std::ifstream texture_file_stream;
	static int  tex_count;
public:
	SageTexture() = delete;
	SageTexture(const char* name);
	SageTexture(const SageTexture& other);
	SageTexture& operator=(const SageTexture& other);
	
	// Getters
	int getTextureID() const;
	int getTextureUnit() const;

	// Setters
	void setTextureRepeat();
	void setTextureClamp();	
	void setTextureMirrorRepeat();
};