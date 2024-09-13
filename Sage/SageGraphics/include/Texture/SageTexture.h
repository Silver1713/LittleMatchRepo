#pragma once
#include <string>
#include <vector>
#include <fstream>

// Create class for texture	

class SageTexture {

private:
	int texture_id;
	int texture_unit;
	std::string texture_path;
	std::vector<unsigned char> texture_data;
	static int  tex_count;
public:
	SageTexture() = delete;
	SageTexture(const char* name);
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