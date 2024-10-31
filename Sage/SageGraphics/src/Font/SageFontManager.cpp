#include "SageFontManager.hpp"
#include "SageFont.hpp"
#include <iostream>


FT_Library SageFontManager::library;
std::map<std::string, std::unique_ptr<SageFont>> SageFontManager::fonts{};
SageFont* SageFontManager::active_font{};
void SageFontManager::Startup()
{
	if (FT_Init_FreeType(&library))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}
}

FT_Library* SageFontManager::get_library()
{
	return &library;
}


void SageFontManager::LoadFont(const char* name, const char* font_path)
{
	std::unique_ptr<SageFont> font = std::make_unique<SageFont>();
	font->Load_Font(font_path);
	fonts[name] = std::move(font);

	active_font = fonts[name].get();
}


SageText SageFontManager::Create_Text(const char* content)
{
	SageText text;
	text.Set_Font(active_font);
	text.Set_Text(content);

	return text;
}
