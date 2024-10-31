#include "SageFont.hpp"
#include "SageText.hpp"
#include "glm/ext/matrix_transform.hpp"


void SageText::Set_Text(const std::string& text)
{
	this->text = text;

	PopulateData();


}


void SageText::Transform::Calculate_Model_Matrix()
{
	glm::mat4 offset_top_left = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 0.0f));
	glm::mat4 scaling = glm::scale(glm::mat4(1.0f), scale);
	glm::mat4 rot_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);

	mdl_mtx = translation  * rot_matrix * scaling * offset_top_left;

}


void SageText::PopulateData()
{
	glm::vec2 cursor = { 0.0f, 0.0f };
	for (char& c : text)
	{
		SageGlyph& glyph = font->Get_Glyph(c);
		Character_Data data;

		data.offset = { cursor.x + glyph.bearing.x, cursor.y - glyph.bearing.y, 0.0f, 0.0f };
		data.uv = { glyph.uv[0], glyph.uv[1], glyph.uv[2], glyph.uv[3] };

		cursor.x += glyph.advance;
		characters.push_back(data);
	}
}
void SageText::Set_Font(SageFont* font)
{
	this->font = font;
}

