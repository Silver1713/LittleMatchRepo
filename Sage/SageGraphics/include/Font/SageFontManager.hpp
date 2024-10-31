//#ifndef SAGE_FONT_MANAGER_HPP
//#define SAGE_FONT_MANAGER_HPP
//#include <map>
//#include <memory>
//#include <string>
//#include <vector>
//#include <freetype/freetype.h>
//
//#include "SageText.hpp"
//
//namespace TextRenderer
//{
//	class SageFont;
//	struct SageFontManager
//	{
//		static FT_Library library;
//		static std::map<std::string ,std::unique_ptr<TextRenderer::SageFont>> fonts;
//		static SageFont* active_font;
//
//		static void Startup();
//		static void LoadFont(const char* name,const char* font_path);
//		static void SetActiveFont(const char* font_name);
//		static SageFont* GetActiveFont();
//		static SageText CreateTextObject(const char* txt, glm::vec2 _position, glm::vec4 _clr, int scale, const char* font_name);
//
//
//	};
//} // namespace TextRenderer
//
//#endif // SAGE_FONT_MANAGER_HPP