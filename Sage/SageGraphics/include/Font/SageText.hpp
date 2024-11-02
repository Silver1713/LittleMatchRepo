
#ifndef SAGE_TEXT_HPP
#define SAGE_TEXT_HPP
#include <string>

#include "SageGlyph.hpp"
class SageFont;
class SageText
{

	std::string text;
	SageFont* font;
	std::vector<SageGlyph*> text_glyphs;


	unsigned int ssbo_data;

	void PopulateData();

	void CreateSSBOResources();

public:

	SageText();
	struct Character_Data
	{
		alignas(16) glm::vec4 offset;
		alignas(16) glm::vec4 uv;
		alignas(8) glm::vec2 scale;
	};


	struct Transform
	{
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation;

		glm::mat4 mdl_mtx;
		void Calculate_Model_Matrix();
	} transform;

	std::vector<Character_Data> characters;




	void Set_Text(const std::string& text);
	void Set_Font(SageFont* font);
	SageFont* Get_Font();
};

#endif // !SAGE_TEXT_HPP