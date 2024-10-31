//#include <iostream>
//#include <ostream>
//#include "SageText.hpp"
//#include "SageFontManager.hpp"
//#include "glm/ext/matrix_transform.hpp"
//
//
//
//namespace TextRenderer
//{
//	SageText::SageText() : font{ nullptr }, ssbo_character{}, text{}, position{}, color{}, font_size{}, capacity{}, size{}, characters{}
//	{
//	}
//	SageText::SageText(const char* txt, glm::vec2 _position, glm::vec4 _clr, int scale, SageFont* font) : font{ font }, ssbo_character{}, text{ text }, position{ _position }, color{ _clr }, font_size{ scale }, capacity{}, size{}, characters{}
//	{
//		
//		if (txt)
//		{
//			text = txt;
//			size = text.size();
//			position = _position;
//			transform.position = glm::vec3(_position, 0);
//			transform.scale = glm::vec3(scale, scale, 1);
//			transform.rotation = glm::vec3(0, 0, 0);
//
//			material.color = color;
//
//			transform.model = glm::mat4(1);
//			transform.UpdateModelMatrix();
//
//			characters.clear();
//
//			glm::vec2 starting_position = { 0,0 };
//			for (char& c : text)
//			{
//				CharacterData data;
//				SageGlyph glyph = font->LoadGlyph(c);
//				data.character = c;
//
//				data.position = glm::vec4(transform.position.x, transform.position.y, 0.f, 1.0f);
//
//				data.scale = glm::vec4(glyph.size.x, glyph.size.y, 0.0f, 1.0f);
//				data.color = {0,0,0,1.f};
//
//				characters.push_back(data);
//
//				position.x += (glyph.advance);
//			}
//		}
//
//		Setup_SSBO();
//	}
//	
//	void SageText::Setup_SSBO()
//	{
//
//		IntializeSSBOResources();
//
//		glNamedBufferSubData(ssbo_character, 0, sizeof(CharacterData) * characters.size(), characters.data());
//		// Bind the SSBO to the binding point
//		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, ssbo_character); // 5 : binding point
//
//
//
//	}
//
//	void SageText::Unbind()
//	{
//		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, 0);
//
//	}
//
//	void SageText::SetFont(SageFont* _font)
//	{
//		font = _font;
//	}
//
//	std::vector<SageText::CharacterData>& SageText::GetCharacters()
//	{
//		return characters;
//	}
//
//
//	void SageText::Bind()
//	{
//		// Bind the SSBO to the binding point
//		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, ssbo_character); // 5 : binding point
//	}
//
//	void SageText::Transform::UpdateModelMatrix()
//	{
//		glm::mat4 top_left_offset = glm::translate(glm::mat4(1), glm::vec3(0.5f,0.5,0));
//		glm::mat4 translation = glm::translate(glm::mat4(1), position);
//		glm::mat4 scaling = glm::scale(glm::mat4(1), scale);
//		glm::mat4 rotation_matrix = { 1 };
//
//		model =  translation  * rotation_matrix * scaling * top_left_offset;
//
//
//	}
//
//	SageText::~SageText()
//	{
//		glDeleteBuffers(1, &ssbo_character);
//	}
//
//	void SageText::IntializeSSBOResources()
//	{
//		glCreateBuffers(1, &ssbo_character);
//		glNamedBufferData(ssbo_character, sizeof(CharacterData) * 32, nullptr, GL_DYNAMIC_DRAW);
//		glObjectLabel(GL_BUFFER, ssbo_character, -1, "Character Data SSBO");
//	}
//
//	void SageText::SetText(std::string txt)
//	{
//		GLenum err = glGetError();
//		if (!font)
//		{
//			std::cerr << "Font is not set\n";
//			return;
//		}
//		float xpos = position.x;
//		text = txt;
//		for (char& c : text)
//		{
//			CharacterData data;
//			SageGlyph glyph = font->LoadGlyph(c);
//			GLenum err = glGetError();
//			data.character = c;
//
//			data.position = glm::vec4(xpos + glyph.bearing.x, position.y - glyph.bearing.y, 0.0f, 1.0f);
//
//			data.scale = glm::vec4(glyph.size.x, glyph.size.y, 0.0f, 1.0f);
//			data.color = color;
//
//			characters.push_back(data);
//
//			xpos += (glyph.advance);
//
//
//		}
//		GLenum s = glGetError();
//	}
//
//
//	glm::vec4 const& SageText::GetColor() const
//	{
//		return color;
//	}
//
//	glm::vec2 const& SageText::GetPosition() const
//	{
//		return position;
//	}
//
//	SageFont* SageText::GetFont()
//	{
//		return font;
//	}
//
//	float const& SageText::GetScale() const
//	{
//		return font_size;
//	}
//
//	void SageText::SetPosition(glm::vec2 _position)
//	{
//		position = _position;
//	}
//
//	void SageText::SetColor(glm::vec4 color)
//	{
//		this->color = color;
//		for (CharacterData& data : characters)
//		{
//			data.color = color;
//		}
//	}
//
//	void SageText::SetScale(float scale)
//	{
//		font_size = scale;
//
//	}
//
//
//	void SageText::Update()
//	{
//		transform.UpdateModelMatrix();
//	}
//
//	unsigned SageText::count() const
//	{
//		return text.size();
//	}
//
//
//
//
//
//
//}
