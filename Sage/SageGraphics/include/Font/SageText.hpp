//#ifndef SAGE_TEXT_HPP
//#define SAGE_TEXT_HPP
//
//#include <GL/glew.h>
//
//#include "SageFont.hpp"
//#include "Vector2.h"
//#include "Vector4.h"
//
//namespace TextRenderer
//{
//	class SageText
//	{
//		struct CharacterData {
//			alignas(16) glm::vec4 color;    // 16-byte aligned
//			alignas(16) glm::vec4 position; // 16-byte aligned
//			alignas(8) glm::vec2 scale;    // 8-byte aligned
//			GLint character;    // 4-byte aligned
//		};
//
//		SageFont* font;
//		unsigned ssbo_character;
//		std::string text;
//		glm::vec2 position;
//		glm::vec4 color;
//		int font_size; 
//
//
//		int capacity; // start with 100 characters
//		int size; // number of characters in the text
//
//		std::vector<CharacterData> characters;
//
//		void IntializeSSBOResources();
//	public:
//
//		struct Transform
//		{
//			glm::vec3 position;
//			glm::vec3 scale;
//			glm::vec3 rotation;
//
//			glm::mat4 model;
//
//
//			void UpdateModelMatrix();
//
//		} transform;
//
//		struct Material
//		{
//			glm::vec4 color;
//		} material;
//	
//		SageText();
//		SageText(const char* text, glm::vec2 position = { 0,0 }, glm::vec4 color = { 0,0,0,1 }, int scale = 15, SageFont* font = nullptr);
//		~SageText();
//
//		void init(const char* text, glm::vec2 position = { 0,0 }, glm::vec4 color = { 0,0,0,1 }, int scale = 15, SageFont* font = nullptr);
//
//		void SetFont(SageFont* font);
//
//
//		void Setup_SSBO();
//		void SetPosition(glm::vec2 position);
//		void SetColor(glm::vec4 color);
//		void SetScale(float scale);
//
//		void Update();
//
//		SageFont* GetFont();
//
//		void SetText(std::string text);
//
//
//		unsigned count() const;
//
//		glm::vec2 const& GetPosition() const;
//		glm::vec4 const& GetColor() const;
//		float const& GetScale() const;
//
//
//		void Bind();
//		void Unbind();
//
//		std::vector<CharacterData>& GetCharacters();
//	};
//} // namespace TextRenderer
//#endif // !SAGE_TEXT_HPP