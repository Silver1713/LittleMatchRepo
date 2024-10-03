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

	static SageObject& Create_Primitive_Object(char const * name,  PrimitiveObject OBJ_SHAPE);
	static SageObject& Create_Primitive_Object(char const* name, PrimitiveObject OBJ_SHAPE, glm::vec2 position, glm::vec2 scale, glm::vec2 orientation, glm::vec4 color = {}, glm::vec4 borderColor = {}, float borderWidth = 0, float borderRadius = 0);
	static SageLine Create_Line_Object(char const* name, glm::vec2 start, glm::vec2 end, glm::vec4 color, float width);
	static void Destroy_All_Objects();
};


#endif // SAGE_OBJECT_MANAGER_HPP
