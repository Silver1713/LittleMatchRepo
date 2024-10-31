///* Start Header ************************************************************************/
///*!
//\file		SageFont.hpp
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
//#ifndef SAGEFONT_HPP
//#define SAGEFONT_HPP
//
//#include <ft2build.h>
//#include <string>
//
//#include "Matrix4x4.h"
//#include "Vector4.h"
//#include <vector>
//#include <map>
//
//#include "SageGlyph.hpp"
//#include "glm/glm.hpp"
//
//#include FT_FREETYPE_H
//
//class SageShader;
//class SageModel;
//namespace TextRenderer
//{
//	
//	class SageFont
//	{
//		SageShader* shader;
//		SageModel* model;
//
//
//		unsigned font_texture_handle;
//
//		unsigned ssbo_handle;
//
//		std::string font_path;
//		std::string font_name;
//
//		unsigned font_size;
//
//		FT_Face font_face;
//		FT_Library* font_library;
//
//		std::map<char, SageGlyph> glyph_map;
//
//		void IntializeOpenGLResources();
//	public:
//		SageFont();
//		~SageFont();
//
//		void Load(const char * path, FT_Library* lib);
//		void Update();
//		void Unload();
//
//
//		SageGlyph LoadGlyph(char c);
//
//
//		unsigned GetFontSize();
//		std::string GetFontPath();
//		std::string GetFontIdentifier();
//
//		void SetShader(SageShader* shader);
//		void SetFontSize(unsigned size);
//
//
//		void LoadFontPath(const std::string& path);
//		void AddGlyph(char c, SageGlyph& glyph);
//		void AddGlyph(char c, ToastBox::Vec4 uv, ToastBox::Vec2 size, ToastBox::Vec2 bearing, size_t advance);
//
//		SageGlyph& GetGlyph(char c);
//		SageGlyph& GetGlyph(char c, float x, float y);
//
//
//		void UnloadGlyph();
//
//
//		unsigned Get_VAO_Handle();
//
//
//
//		SageModel* Get_Mesh();
//		SageShader* GetShader();
//	};
//
//	
//}
//
//
//
//#endif //SAGEFONT_HPP