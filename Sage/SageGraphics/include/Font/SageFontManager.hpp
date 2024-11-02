#ifndef SAGE_FONT_MANAGER_HPP
#define SAGE_FONT_MANAGER_HPP
#include "SageFont.hpp"
#include "SageText.hpp"
#include <memory>
#include <string>
#include "freetype/freetype.h"
#include <map>




struct SageFontManager
{
	static FT_Library library;
	static std::map<std::string, std::unique_ptr<SageFont>> fonts;
	static SageFont* active_font;

	static void Startup();
	static void LoadFont(const char* name, const char* font_path);
	//static void SetActiveFont(const char* font_name);
	//static SageFont* GetActiveFont();
	//static SageText CreateTextObject(const char* txt, glm::vec2 _position, glm::vec4 _clr, int scale, const char* font_name);
	static FT_Library* get_library();
	static SageText Create_Text(const char* content);
};

#endif // SAGE_FONT_MANAGER_HPP