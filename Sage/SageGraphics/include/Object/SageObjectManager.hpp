#ifndef SAGE_OBJECT_MANAGER_HPP
#define SAGE_OBJECT_MANAGER_HPP

#include "SageLine.hpp"
#include "SageObject.hpp"

enum PrimitiveObject
{
	PRIMITIVE_OBJECT_RECT,
	PRIMITIVE_OBJECT_TRIANGLE,
	PRIMITIVE_OBJECT_CIRCLE,
	PRIMITIVE_OBJECT_LINE,
	PRIMITIVE_OBJECT_POINT,
	PRIMITIVE_OBJECT_COUNT
};

struct SageObjectManager
{
	static std::map<std::string, SageObject> objects;

	static SageObject& Create_Primitive_Object(char const * _name,  PrimitiveObject _OBJ_SHAPE);
	static SageObject& Create_Primitive_Object(char const* _name, PrimitiveObject _OBJ_SHAPE, glm::vec2 _position, glm::vec2 _scale, glm::vec2 _orientation, glm::vec4 _color = {}, glm::vec4 _border_color = {}, float _border_width = 0, float _border_radius = 0);
	static SageLine Create_Line_Object(char const* name, glm::vec2 start, glm::vec2 end, glm::vec4 color, float width);
	static void Destroy_All_Objects();
};


#endif // SAGE_OBJECT_MANAGER_HPP
