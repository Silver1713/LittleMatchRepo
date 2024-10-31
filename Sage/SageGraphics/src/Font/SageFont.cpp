
#include <iostream>
#include <ostream>
#include "SageModelManager.hpp"
#include "SageGlyph.hpp"

#include "SageFontManager.hpp"
#include "SageFont.hpp"

void SageFont::Load_Glyph_And_Create_Atlas()
{
	Set_Text_Size(128);

	CreateGLResource(128,10);

	glm::vec2 offset{};
	int rowHeight = 0;
	int padding = 10;


	for (int i =0; i < 128;i++)
	{
		char c = static_cast<char>(i);
		Add_Load_Glyph(c, offset, rowHeight, padding);
	}

	is_loaded = true;
	


}

void SageFont::Set_Text_Size(unsigned int size) //Set the font size in the atlas
{
	font_size = size;
	FT_Set_Pixel_Sizes(ft_face, 0, size);
}

void SageFont::CreateGLResource(int font_size, int padding)
{
	Calculate_Dimensions(font_size, padding, 128);

	//Create a texture atlas
	glCreateTextures(GL_TEXTURE_2D, 1, &font_texture_atlas_id);
	glTextureStorage2D(font_texture_atlas_id, 1, GL_R8, atlas_width, atlas_height);

	//Load a primitive model
	model = &SageModelManager::GetModel("PRIMITIVE_RECT");

	
}


void SageFont::Calculate_Dimensions(int font_size, int padding, int number_of_char)
{
	int numberGlyph = number_of_char;

	int totalEstimatedArea = (font_size + padding) * (font_size + padding) * numberGlyph;

	int atlas_dimension = static_cast<int>(std::ceil(sqrt(totalEstimatedArea)));

	//Find the nearest power of 2
	int power_of_2 = 1;
	while (power_of_2 < atlas_dimension)
	{
		power_of_2 *= 2;
	}

	atlas_width = power_of_2;
	atlas_height = power_of_2;
}


void SageFont::Add_Load_Glyph(char glyph_char, glm::vec2& offset, int& rowHeight, int padding)
{
	// Load the glyph
	FT_Error load_err = FT_Load_Char(ft_face, glyph_char, FT_LOAD_RENDER);
	if (load_err) return;

	// Get the glyph
	FT_GlyphSlot& ft_glyph = ft_face->glyph;

	// Convert the glyph to bitmap
	FT_Bitmap& bmp = ft_glyph->bitmap;
	std::cout << "Character: " << glyph_char << " ";
	std::cout << "Bitmap Width: " << bmp.width << ", Height: " << bmp.rows << std::endl;
	if (offset.x + bmp.width + padding > atlas_width)
	{
		offset.x = 0;
		offset.y += rowHeight + padding;
		rowHeight = 0;
	}

	glTextureSubImage2D(font_texture_atlas_id, 0, offset.x, offset.y, 
		bmp.width, bmp.rows, 
		GL_RED, GL_UNSIGNED_BYTE, bmp.buffer);


	SageGlyph glyph{};

	glyph.uv = { offset.x / atlas_width, offset.y / atlas_height,
	(offset.x + bmp.width) / atlas_width, (offset.y + bmp.rows) / atlas_height };
	glyph.character = glyph_char;
	glyph.ft_glyph = &ft_glyph;
	glyph.size = { bmp.width, bmp.rows };
	glyph.bearing = { ft_glyph->bitmap_left, ft_glyph->bitmap_top };
	glyph.advance = ft_glyph->advance.x >> 6;

	glyphs[glyph_char] = glyph;

	offset.x += bmp.width + padding;

	if (bmp.rows > rowHeight)
	{
		rowHeight = bmp.rows;
	}




}


void SageFont::Load_Font(const char* path)
{
	file_path = path;

	FT_Error err = FT_New_Face(*SageFontManager::get_library(), path, 0, &ft_face);
	if (err)
	{
		std::cout << "Error: Failed to load font: " << path << std::endl;
		return;
	}

	FT_Set_Pixel_Sizes(ft_face, 0, 128);

	Load_Glyph_And_Create_Atlas();
}

SageFont::SageFont()
{

}

SageFont::~SageFont()
{
	if (is_loaded)
	{
		glDeleteTextures(1, &font_texture_atlas_id);
	}
}


SageGlyph& SageFont::Get_Glyph(char c)
{
	return glyphs[c];
}
