#include "SageFont.hpp"
#include "SageText.hpp"
#include <gl/glew.h>
#include "glm/ext/matrix_transform.hpp"


SageText::SageText() : font(nullptr), text(""), characters(), transform(), text_glyphs() ,ssbo_data()
{
}

void SageText::Set_Text(const std::string& text)
{
	this->text = text;

	PopulateData();


}


void SageText::Transform::Calculate_Model_Matrix()
{
	glm::mat4 offset_top_left = glm::translate(glm::mat4(1.0f), glm::vec3(.5f*scale.x,.5f*scale.y, 0.0f));
	glm::mat4 scaling = glm::scale(glm::mat4(1.0f), scale);
	glm::mat4 rot_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);

	mdl_mtx =  translation * offset_top_left * rot_matrix * scaling;

}


void SageText::PopulateData()
{
	glm::vec2 cursor = { 0.0f, 0.0f };
	characters.clear();

	for (char& c : text)
	{
		SageGlyph& glyph = font->Get_Glyph(c);
		Character_Data data;

		data.offset = { cursor.x + glyph.bearing.x, cursor.y - glyph.bearing.y, 0.0f, 0.0f };
		data.uv = { glyph.uv[0], glyph.uv[1], glyph.uv[2], glyph.uv[3] };
		data.scale = { glyph.size.x, glyph.size.y };
		cursor.x += glyph.advance;
		characters.push_back(data);
	}

	CreateSSBOResources();
}
void SageText::Set_Font(SageFont* font)
{
	this->font = font;
}

SageFont* SageText::Get_Font()
{
	return font;
}

void SageText::CreateSSBOResources()
{
	glCreateBuffers(1, &ssbo_data);
	glNamedBufferData(ssbo_data, characters.size() * sizeof(Character_Data), characters.data(), GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, ssbo_data);
}


