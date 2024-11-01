//#include <iostream>
//#include <ostream>
//
//#include "SageFont.hpp"
//#include "SageText.hpp"
//#include "SageFontManager.hpp"
//#include "SageRenderer.hpp"
//
//
//
//FT_Library TextRenderer::SageFontManager::library{};
//std::map<std::string, std::unique_ptr<TextRenderer::SageFont>> TextRenderer::SageFontManager::fonts;
//TextRenderer::SageFont* TextRenderer::SageFontManager::active_font{};
//
//void TextRenderer::SageFontManager::Startup()
//{
//	FT_Error error = FT_Init_FreeType(&library);
//	if (error)
//	{
//		std::cout << "Error: Could not initialize FreeType library.\n";
//		std::exit(1);
//	}
//}
//
//
//void TextRenderer::SageFontManager::LoadFont(const char* name, const char* font_path)
//{
//	std::unique_ptr<TextRenderer::SageFont> font = std::make_unique<TextRenderer::SageFont>(); 
//	font->Load(font_path,&library);
//
//	
//	font->SetFontSize(24);
//	fonts[name] = std::move(font);
//}
//
//TextRenderer::SageText TextRenderer::SageFontManager::CreateTextObject(const char* txt, glm::vec2 _position, glm::vec4 _clr, int scale, const char* font_name)
//{
//	TextRenderer::SageText text;
//
//	text.SetFont(TextRenderer::SageFontManager::fonts[font_name].get());
//	text.SetText(txt);
//
//
//
//	text.SetPosition(_position);
//	text.SetColor(_clr);
//	text.SetScale(scale);
//
//
//	text.Setup_SSBO();
//	return text;
//
//}
//
//void TextRenderer::SageFontManager::SetActiveFont(const char* font_name)
//{
//	active_font = fonts[font_name].get();
//
//	SageRenderer::Set_Font(active_font);
//}
//
//TextRenderer::SageFont* TextRenderer::SageFontManager::GetActiveFont()
//{
//	return active_font;
//
//}
//
//
