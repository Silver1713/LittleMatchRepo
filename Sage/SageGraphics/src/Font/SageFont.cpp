///* Start Header ************************************************************************/
///*!
//\file		SageFont.cpp
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
//
//#include "SageModelManager.hpp"
//#include "SageShaderManager.hpp"
//#include "SageFont.hpp"
//
//#include <iostream>
//#include <ostream>
//
//namespace TextRenderer
//{
//
//
//	SageFont::SageFont() : shader{}, model{}, font_texture_handle {}, ssbo_handle{}, font_path{}, font_name{}
//		, font_size{}, font_face{}, font_library{}, glyph_map{}{}
//	SageFont::~SageFont() {}
//
//
//
//	void SageFont::IntializeOpenGLResources()
//	{
//		// Get Model
//		shader = &SageShaderManager::Get_Shader_Program("TEXT_SHADER");
//		model = &SageModelManager::GetModel("PRIMITIVE_RECT");
//
//
//
//		glCreateTextures(GL_TEXTURE_2D, 1, &font_texture_handle);
//		// Set texture parameters
//		glTextureParameteri(font_texture_handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTextureParameteri(font_texture_handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//		glTextureParameteri(font_texture_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTextureParameteri(font_texture_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	}
//
//
//	void SageFont::Load(const char* path, FT_Library* lib)
//	{
//		IntializeOpenGLResources();
//		GLenum err = glGetError();
//		this->font_path = path;
//		this->font_library = lib;
//		font_size = 24; //	Default font size
//		// Load font face
//		FT_Error error = FT_New_Face(*font_library, font_path.c_str(), 0, &font_face);
//		if (error)
//		{
//			std::cout << "Error: Could not load font face.\n";
//			std::exit(1);
//		}
//
//		font_name = font_face->family_name;
//
//
//
//		// Set font size
//		FT_Set_Pixel_Sizes(font_face, 0, font_size);
//
//
//
//	}
//
//
//
//	SageGlyph SageFont::LoadGlyph(char c)
//	{
//		FT_Set_Pixel_Sizes(font_face, 0, font_size);
//		// Load character glyph
//		if (FT_Load_Char(font_face, c, FT_LOAD_DEFAULT))
//		{
//			std::cout << "Error: Could not load glyph for character " << c << std::endl;
//			return SageGlyph();
//		}
//		if (font_face->glyph->format == FT_GLYPH_FORMAT_OUTLINE) {
//			// Force rasterize outline to a bitmap
//			if (FT_Render_Glyph(font_face->glyph, FT_RENDER_MODE_NORMAL)) {
//				std::cout << "Error: Could not rasterize outline glyph for character " << c << std::endl;
//				return SageGlyph();
//			}
//		}
//		GLenum err = glGetError();
//		// Generate texture
//		unsigned texture_handle;
//		int a = FT_Get_Char_Index(font_face, c);
//		//Bitmap dimensions
//		GLsizei width = font_face->glyph->bitmap.width;
//		GLsizei height = font_face->glyph->bitmap.rows;
//
//
//
//		if (!width || !height)
//		{
//			return SageGlyph(0, width, height, 0, 0, font_face->glyph->advance.x >> 6);
//		}
//		GLenum err5 = glGetError();
//		if (!font_face->glyph->bitmap.buffer) return{};
//		glCreateTextures(GL_TEXTURE_2D, 1, &texture_handle);
//		glTextureStorage2D(texture_handle, 1, GL_R8, width, height);
//		GLenum err3 = glGetError();
//		glTextureSubImage2D(texture_handle, 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, font_face->glyph->bitmap.buffer);
//		// Set texture parameters
//		glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		GLenum err2 = glGetError();
//		glTextureParameteri(texture_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTextureParameteri(texture_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		GLenum err1 = glGetError();
//		// Create glyph
//		SageGlyph glyph(texture_handle, width, height, font_face->glyph->bitmap_left, font_face->glyph->bitmap_top, font_face->glyph->advance.x >> 6);
//		// Add glyph to map
//		AddGlyph(c, glyph);
//
//		return glyph;
//	}
//
//
//
//	void SageFont::AddGlyph(char c, SageGlyph& glyph)
//	{
//		glyph_map[c] = glyph;
//	}
//
//
//	unsigned SageFont::GetFontSize()
//	{
//		return font_size;
//	}
//
//	std::string SageFont::GetFontIdentifier()
//	{
//		return font_name;
//	}
//
//	std::string SageFont::GetFontPath()
//	{
//		return font_path;
//	}
//
//	void SageFont::SetFontSize(unsigned size)
//	{
//		font_size = size;
//		FT_Set_Pixel_Sizes(font_face, 0, font_size);
//		UnloadGlyph();
//	}
//
//	void SageFont::UnloadGlyph()
//	{
//		for (auto& glyph : glyph_map)
//		{
//			if (glyph.second.texture_handle)
//				glDeleteTextures(1, &glyph.second.texture_handle);
//		}
//		glyph_map.clear();
//	}
//
//	SageGlyph& SageFont::GetGlyph(char c)
//	{
//		if (!glyph_map.contains(c))
//		{
//			LoadGlyph(c);
//			return glyph_map[c];
//		}
//		else return glyph_map[c];
//	}
//
//	void SageFont::Unload()
//	{
//		UnloadGlyph();
//		glDeleteTextures(1, &font_texture_handle);
//		glDeleteBuffers(1, &ssbo_handle);
//		FT_Done_Face(font_face);
//	}
//
//
//	void SageFont::LoadFontPath(const std::string& path)
//	{
//		font_path = path;
//	}
//
//
//
//	SageModel* SageFont::Get_Mesh()
//	{
//		return model;
//	}
//
//	SageShader* SageFont::GetShader()
//	{
//		return shader;
//	}
//
//
//
//
//
//
//
//
//
//	
//
//
//
//
//}
