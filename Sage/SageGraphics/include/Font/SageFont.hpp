///* Start Header ************************************************************************/
///*!
//\file		SageFont.hpp
//\title		Memory's Flame
//\author		Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (100%)
//\par		halisilyasa.b@digipen.edu
//\date		08 September 2024
//\brief		Contains the functions for creating font.
//
//			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
//*/
///* End Header **************************************************************************/
//
#ifndef SAGEFONT_HPP
#define SAGEFONT_HPP
#include <map>
#include <string>
#include <freetype/freetype.h>
#include "SageGlyph.hpp"
#include "glm/vec2.hpp"
class SageModel;

class SageFont // Encapsulates a font face
{
	bool is_loaded = false;
	SageModel* model; // Contain the actual quad data
	FT_Face ft_face;


	unsigned int font_size;
	unsigned int font_texture_atlas_id;

	int atlas_width, atlas_height;



	std::map<char, SageGlyph> glyphs;

	std::string file_path; // Path to the font file (.ttf)


	void Calculate_Dimensions(int font_size, int padding=2, int numGlyph = 128);
	void CreateGLResource(int font_size, int padding=2);


public:
	SageFont();
	~SageFont();
	void Load_Font(const char* path);

	void Load_Glyph_And_Create_Atlas();

	SageGlyph& Get_Glyph(char c);
	void Load_Glyph_And_Create_Atlas(const char* path);

	void Set_Text_Size(unsigned int size);

	void Add_Load_Glyph(char glyph_char, glm::vec2& offset, int& rowHeight, int padding);

	SageModel* Get_Mesh();

	unsigned int Get_Texture_Atlas_ID();

	glm::vec2 getatlasSIze();

};
#endif //SAGEFONT_HPP