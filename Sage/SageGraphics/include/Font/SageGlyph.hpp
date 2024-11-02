#ifndef SAGE_GLYPH_HPP
#define SAGE_GLYPH_HPP
#include <glm/glm.hpp>
#include "freetype/ftglyph.h"

using GLuint = unsigned int;

struct SageGlyph
{

	char character; // Character represented by the glyph

	//FT_GlyphSlot* ft_glyph; // FreeType glyph

	glm::vec4 uv; // UV coordinates of the glyph
	glm::vec2 size; // Size of glyph
	glm::vec2 bearing; // Offset from baseline to left/top of glyph
	GLuint advance; // Offset to advance to next glyph

	SageGlyph();
	SageGlyph(FT_Face* face);
	SageGlyph(char character, FT_Face* font_face);


	void LoadGlyph(char character, FT_Face* font_face);



	void Clean();

};

// namespace TextRenderer
#endif // !SAGE_GLYPH_HPP