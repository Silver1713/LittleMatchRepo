
#include <iostream>
#include <ostream>
#include "SageModelManager.hpp"
#include "SageGlyph.hpp"

#include "SageFontManager.hpp"
#include "SageFont.hpp"

void SageFont::Load_Glyph_And_Create_Atlas()
{
	Set_Text_Size(128);

	CreateGLResource(128, 50);

	glm::vec2 offset{};
	int rowHeight = 0;
	int padding = 50;

	int baseline = 0;
	int boundsX = 0, boundsY = 0;
	Calculate_Bounds_Hack(boundsX, boundsY, baseline);




	for (int i = 0; i < 128; i++)
	{
		char c = static_cast<char>(i);
		Add_Load_Glyph(c, offset, rowHeight, padding, baseline);
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

	GLenum gerr = glGetError();
	glCreateTextures(GL_TEXTURE_2D, 1, &font_texture_atlas_id);
	glTextureStorage2D(font_texture_atlas_id, 1, GL_R8, atlas_width, atlas_height);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



	GLenum gerr1 = glGetError();

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

void SageFont::Calculate_Bounds_Hack(int& boundsX, int& boundsY, int& baseline)
{
	FT_Error err = FT_Load_Char(ft_face, 'H', FT_LOAD_RENDER);
	if (err)
	{
		std::cout << "Error: Failed to load glyph for baseline hack" << std::endl;
		return;
	}

	FT_GlyphSlot& ft_glyph = ft_face->glyph;

	baseline = ft_glyph->bitmap_top;
	

}


void SageFont::Add_Load_Glyph(char glyph_char, glm::vec2& offset, int& rowHeight, int padding, int baseline)
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

	int yOffset = 0;
	if (ft_glyph->bitmap_top < baseline) {
		yOffset = baseline - ft_glyph->bitmap_top;
	}
	if (offset.x + bmp.width + padding > atlas_width)
	{
		offset.x = 0;
		offset.y += rowHeight + padding;
		rowHeight = 0;
	}
	GLenum err = glGetError();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	unsigned char* data = (!bmp.buffer ? (new unsigned char[bmp.width * bmp.rows] {}) : bmp.buffer);

	if (bmp.buffer == nullptr)
	{
		std::fill_n(data, bmp.width * bmp.rows, 255);
	}
	glTextureSubImage2D(font_texture_atlas_id, 0, offset.x, offset.y + yOffset,
		bmp.width, bmp.rows, GL_RED, 
		GL_UNSIGNED_BYTE, data);

	if (!bmp.buffer)
	{
		delete[] data;
		data = nullptr;
	}

	err = glGetError();
	SageGlyph glyph{};

	glyph.uv = { offset.x / atlas_width, (offset.y + yOffset) / atlas_height,
	(offset.x + bmp.width) / atlas_width, (offset.y + yOffset + bmp.rows) / atlas_height };
	glyph.character = glyph_char;
	//glyph.ft_glyph = &ft_glyph;
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


SageModel* SageFont::Get_Mesh()
{
	return model;
}

unsigned int SageFont::Get_Texture_Atlas_ID()
{
	return font_texture_atlas_id;
}

glm::vec2 SageFont::getatlasSIze()
{
	return { atlas_width, atlas_height };
}

