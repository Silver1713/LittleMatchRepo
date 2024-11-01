//#ifndef SAGE_GLYPH_HPP
//#define SAGE_GLYPH_HPP
//#include "glm/vec2.hpp"
//
//namespace TextRenderer
//{
//	struct SageGlyph
//	{
//		
//
//		unsigned texture_handle;
//
//		glm::ivec2 size;
//		glm::ivec2 bearing;
//
//		size_t advance;
//
//		SageGlyph();
//		SageGlyph(unsigned tex, glm::ivec2 size, glm::ivec2 bearing, size_t advance);
//		SageGlyph(unsigned id, int width, int height, int bearingX, int bearingY, size_t advance);
//
//		~SageGlyph();
//
//		void init(unsigned tex, glm::ivec2 size, glm::ivec2 bearing, size_t advance);
//		void init(unsigned id, int width, int height, int bearingX, int bearingY, size_t advance);
//
//		void SetSize(int width, int height);
//		void SetBearing(int bearingX, int bearingY);
//		void SetAdvance(size_t advance);
//	};
//
//}// namespace TextRenderer
//#endif // !SAGE_GLYPH_HPP