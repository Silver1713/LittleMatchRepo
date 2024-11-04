/* Start Header ************************************************************************/
/*!
\file		SageObjectManager.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		This header file allow opengl objects to be instantiated and created which
			allow the VAO,VBO data to be reused.


			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#ifndef SAGE_OBJECT_MANAGER_HPP
#define SAGE_OBJECT_MANAGER_HPP
#include <map>
#include "SageLine.hpp"
#include "SageObject.hpp"

/*!*****************************************************************************
\brief
	Represent the type of primitive objects available in the engine.

*******************************************************************************/
enum PrimitiveObject
{
	PRIMITIVE_OBJECT_RECT, //!< Rect
	PRIMITIVE_OBJECT_TRIANGLE, //!< Triangle
	PRIMITIVE_OBJECT_CIRCLE, //!< Circle
	PRIMITIVE_OBJECT_LINE, //!< Line
	PRIMITIVE_OBJECT_POINT, //!< Point
	PRIMITIVE_OBJECT_COUNT //!< Number of primitive type.
};
/*!*****************************************************************************
\brief
	Encapsulate a object manager that manage the openGL objects providing
	functionality to create,manage and destroy openGL objects in the game
	world.

*******************************************************************************/
struct SageObjectManager
{
	static std::map<std::string, SageObject> objects; //!< The list of objects in the game world.
	/*!*****************************************************************************
	\brief
		Create a primitive object

		This function will create a primitive object given, the type and the
		name of the object. This object will contain the default values.

	\param _name
		The name of the object
	\param _OBJ_SHAPE
		The shape of the object.

	\return
		A reference to the created game object in the objects buffer.

	*******************************************************************************/
	static SageObject& Create_Primitive_Object(char const * _name,  PrimitiveObject _OBJ_SHAPE);
	/*!*****************************************************************************
	\brief
		Create a primitive object

		This function will create a primitive object given, the type and the
		name of the object. This object will contain the values as define by the
		input
	\param _name
		The name of the object
	\param _OBJ_SHAPE
		The shape of the object.
	\param _position
		The Position of the object
	\param _color
		Color of the object
	\param _border_color
		Border color of the object
	\param _border_width
		The border width of the object
	\param _border_rad
		The border radius of the object.
	\return
		A reference to the created game object in the objects buffer.

	*******************************************************************************/
	static SageObject& Create_Primitive_Object(char const* _name, PrimitiveObject _OBJ_SHAPE, glm::vec2 _position, glm::vec2 _scale, glm::vec2 _orientation, glm::vec4 _color = {}, glm::vec4 _border_color = {}, float _border_width = 0, float _border_radius = 0);
	/*!*****************************************************************************
	\brief
		Create a Line object to be drawn by the renderer

		This function will create a line object given name, start and end points and
		the width and color of the line.
	\param _name
		The name of the object
	\param start
		Starting point on the line
	\param end
		Ending point on the line
	\param _color
		Color of the object
	\param width
		THe size of the line.
	\return
		The newly created SageLine object.

	*******************************************************************************/
	static SageLine Create_Line_Object(char const* name, glm::vec2 start, glm::vec2 end, glm::vec4 color, float width);
	/*!*****************************************************************************
	\brief
		Clears the object buffers.
	*******************************************************************************/
	static void Destroy_All_Objects();
};


#endif // SAGE_OBJECT_MANAGER_HPP
