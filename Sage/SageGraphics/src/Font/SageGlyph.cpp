//#include "SageGlyph.hpp"
//
//namespace TextRenderer
//{
//	SageGlyph::SageGlyph() : texture_handle{}, size{}, bearing{}, advance{} {}
//	SageGlyph::SageGlyph(unsigned tex, glm::ivec2 size, glm::ivec2 bearing, size_t advance)
//		: texture_handle{ tex }, size{ size }, bearing{ bearing }, advance{ advance } {}
//	SageGlyph::SageGlyph(unsigned id, int width, int height, int bearingX, int bearingY, size_t advance)
//		: texture_handle{ id }, size{ width, height }, bearing{ bearingX, bearingY }, advance{ advance } {}
//	SageGlyph::~SageGlyph() {}
//
//	void SageGlyph::init(unsigned tex, glm::ivec2 sz, glm::ivec2 bearin, size_t adv)
//	{
//		texture_handle = tex;
//		this->size = sz;
//		this->bearing = bearin;
//		this->advance = adv;
//	}
//
//	void SageGlyph::init(unsigned id, int width, int height, int bearingX, int bearingY, size_t adv)
//	{
//		texture_handle = id;
//		size = glm::ivec2(width, height);
//		bearing = glm::ivec2(bearingX, bearingY);
//		this->advance = adv;
//	}
//
//	void SageGlyph::SetSize(int width, int height)
//	{
//		size = glm::ivec2(width, height);
//	}
//
//	void SageGlyph::SetAdvance(size_t adv)
//	{
//		advance = adv;
//	}
//
//	void SageGlyph::SetBearing(int bearingX, int bearingY)
//	{
//		bearing = glm::ivec2(bearingX, bearingY);
//	}
//
//}
