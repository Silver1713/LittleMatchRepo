/* Start Header ************************************************************************/
/*!
\file		SageRenderer.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The public interface that implement the renderer class that handles rendering of
			objects and models to the screen. This class make calls to the private interface
			implemented in the internal class.


			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/



#ifndef SAGERENDERER_HPP
#define SAGERENDERER_HPP

#include "SageCamera.hpp"
#include "SageViewport.hpp"
#include "SagePoint.hpp"
#include "Vector4.h"


class SageModel; //!< Forward declaration of the SageModel class
class SageObject; //!< Forward declaration of the SageObject class
struct SageLine; //!< Forward declaration of the SageLine struct
struct SagePoint; //!< Forward declaration of the SagePoint struct
class SageTexture; //!< Forward declaration of the SageTexture class
class SageShader; //!< Forward declaration of the SageShader class

class SageCamera; //!< Forward declaration of the SageCamera class


/*!*****************************************************************************
\brief
	Represent the type of rendering that can be done by the renderer.
	This enum class encapsulate the list the type of rendering that can be
	done using the renderer.

*******************************************************************************/
enum class RENDER_TYPE
{
	TYPE_TRIANGLE, //!< Triangle
	TYPE_TRIANGLE_STRIP, //!< Triangle strip
	TYPE_TRIANGLE_FAN, //!< Triangle fan
	TYPE_LINES, //!< Lines
	TYPE_LINES_STRIP, //!< Line strip
	TYPE_LINES_LOOP, //!< Line loop
	TYPE_POINTS, //!< Points

};
/*!*****************************************************************************
\brief
	Eneum class that represent the render mode of the renderer.
	Filled - Draw the mesh filled
	Lines - Draw lines
	Point - Draw points

*******************************************************************************/
enum RENDER_MODE
{
	MODE_FILLED, //!< Filled
	MODE_LINES, //!< Lines
	MODE_POINTS, //!< Points

};

/*!*****************************************************************************
\brief
	Encapsulate the type of shape a mesh can have.
	This enumeration contain a list of possible shapes that a mesh can have.

*******************************************************************************/
enum SHAPE
{
	SHAPE_SQUARE, //!< Square
	SHAPE_CIRCLE, //!< Circle
	SHAPE_TRIANGLE, //!< Triangle
	SHAPE_POLYGON, //!< Custom shape with non-preset vao, vbo or ebo data.
	SHAPE_OBJECT_COUNT //!< Number of shapes
};


/*!*****************************************************************************
\brief
	Rendererer configuration struct that contain the configuration of the renderer.

	This struct encapsulate the configuration of the renderer which is used to
	modify the behaviour of the renderer. It contain options like color, alpha and
	the border width and color. Further the it also utlize bitmasking to enable or
	disable options like enabling vertex color, texture, border and camera.
*******************************************************************************/
struct RENDER_CONFIG
{
	unsigned int options; //!< Bitmask options
	glm::vec4 color; //!< Color of the object
	float render_alpha; //!< Alpha value of the object


	float border_width; //!< Width of the border
	float border_radius; //!< Radius of the border
	glm::vec4 border_color; //!< Color of the border

	SageShader* shader; //!< Shader to be used when rendering

	glm::mat3 transformation_matrix; //!< Transformation matrix
	ToastBox::Matrix3x3 matrix; //!< Custom Transformation matrix

	SageTexture* current_texture; //!< default texture to be used when rendering

	/*!*****************************************************************************
	\brief
		Default constructor for the RENDER_CONFIG struct.
		When no parameters are given, the default values are set to the struct.
		allowing for a default configuration to be created.

	\param options
		Bitmask options to be set. Default is 0
	\param render_alpha
		Alpha value of the object. Default is 1.f
	\param border_width
		Width of the border. Default is 0
	\param color
		Color of the object. Default is {0,0,0,1}
	\param border_color
		Color of the border. Default is {0,0,0,1}
	\param border_radius
		Radius of the border. Default is 0
	\param shader
		Shader to be used when rendering. It default to nullptr
	\param transformation_matrix
		Transformation matrix. Default is identity matrix
	\param matrix
		Custom transformation matrix. Default is identity matrix
	\param current_texture
		Default texture to be used when rendering. It set to nullptr by default
	*******************************************************************************/
	RENDER_CONFIG(unsigned int options = 0, float render_alpha = 1.f, float border_width = 0, glm::vec4 color = { 0,0,0,1 }, glm::vec4 border_color = { 0,0,0,1 }, float border_radius = 0, SageShader* shader = nullptr, glm::mat3 transformation_matrix = glm::mat3(1.f), ToastBox::Matrix3x3 matrix = ToastBox::Matrix3x3(), SageTexture* current_texture = nullptr);

};

/*!*****************************************************************************
\brief
	Encapsulate the renderer class that handle the rendering of objects and models.

	This struct contain the public interface of the renderer class that is used to
	draw objects and models to the screen. It also contain the default configuration
	used when no configuration are specified. Furthermore, it contain the active
	viewport and camera that is used when rendering objects and models.

*******************************************************************************/
struct SageRenderer
{

	enum //!< Bitmask options for the renderer configuration, currenet options are 4 bits
	{
		SAGE_ENABLE_ALPHA = 1, //!< Enable transparency
		SAGE_ENABLE_BORDER = 2, //!< Enable border
		SAGE_ENABLE_VERTEX_COLOR = 4, //!< Use vertex color
		SAGE_ENABLE_TEXTURE = 8, //!< Use texture
		SAGE_ENABLE_CAMERA = 16,//!< Enable camera when rendering, when disable renderer will use screen space else it will use world space.
	};

	static RENDER_CONFIG default_config; //!< The default configuration used when no configuration are specified
	static SageViewport viewport; //!< The active viewport for rendering.
	static SageShader* default_shader; //!< The default shader program used for rendering when no shader is specified.
	static SageCamera* camera; //!< The active camera used for rendering.



	/*!*****************************************************************************
	\brief
		Initialize the renderer class.

		This function initialize the renderer class by setting the default configuration and
		setting the default shader program to be used when rendering. Furthermore, it also
		initalize the common primitives that is used when rendering objects and models.
		These primitives are the square, circle and triangle. This function prepare
		the renderer for rendering objects and models.
	*******************************************************************************/
	static void Init();
	/*!*****************************************************************************
	\brief
		Set the default shader program of the renderer.
		It take in a pointer to a shader program and set it as the default shader
		program.
	\param shader
		The shader program to be set as the default shader program.
	*******************************************************************************/
	static void Set_Default_Shader(SageShader* shader);
	/*!*****************************************************************************
	\brief
		Set the active viewport of the renderer.
		This overload set the active viewport of the renderer to the given viewport.
		it take in a reference to a viewport object and return nothing.

	\param view
		The viewport object to be set to use when rendering.
	*******************************************************************************/
	static void Set_Current_View(SageViewport& view);
	/*!*****************************************************************************
	\brief
		Set the active camera of the renderer.
		This overload set the active camera of the renderer to the given camera.
		it take in a pointer to a camera object and return nothing.

	\param view
		The camera object to be set to use when rendering.
	*******************************************************************************/
	static void Set_Current_View(SageCamera* view);
	/*!*****************************************************************************
	\brief
		Draw the given object to the screen with the given render configuration.

		The function take in a reference to a SageObject and a renderer configuration
		structure which allow the renderer to draw the object to the screen with the
		given configuration.
	\param object
		The object to be drawn to the screen.
	\param config
		The configuration of the renderer when drawing the object.
	*******************************************************************************/
	static void Draw_Filled(SageObject& object, RENDER_CONFIG config);
	/*!*****************************************************************************
	\brief
		Draw the given object to the screen with the given render configuration.

		This function only take in a reference to a SageObject and draw the object to
		the screen. It will use the default configuration when drawing the object.
	\param object
		The object to be drawn to the screen.
	*******************************************************************************/
	static void Draw_Filled(SageObject& object);
	/*!*****************************************************************************
	\brief
		Draw the given object to the screen with the given render configuration. 

		This function draw the given model to the screen. It take in a reference to
		a model object , containing the mesh data and its attributes and a transformation
		matrix which is to be concatenated with the camera or viewport matrix, allowing
		the model to be drawn on the screen. It also take in a render configuration struct
		that contain the configuration of the renderer when drawing the model.
	\param model
			The model to be drawn to the screen.
	\param matrix
			The transformation matrix to be applied to the model.
	\param config
			The configuration of the renderer when drawing the model.
	*******************************************************************************/
	static void Draw_Filled(SageModel& model, glm::mat3& matrix, RENDER_CONFIG config = { (SAGE_ENABLE_ALPHA | SAGE_ENABLE_BORDER) });
	/*!*****************************************************************************
	\brief
		Draww the given model to the screen with the default configuration.

		This function draw the given model to the screen. It take in a reference to
		a model object , containing the mesh data and its attributes and a transformation
		matrix which is to be concatenated with the camera or viewport matrix, allowing
		the model to be drawn on the screen. Since no configuration is given, the default
		configuraiton is used when drawing the model. The default transformation and their
		associated values can be changes using the member functions of the renderer.
	\param model
			The model to be drawn to the screen.
	*******************************************************************************/
	static void Draw_Filled(SageModel& model);
	/*!*****************************************************************************
	\brief
		Draw a line to the screen.

		This function take in a reference to am line model containing the start and end
		points of the line , the color of the line and the width of the line. It uses
		the active view when drawing the line to the screen. When using just the viewport
		the line will be drawn in screen space, with the camera the line will be drawn
		in the world space coordinates.

		The default configuration is used when drawing the line. Baring, the values in the
		SageLine struct, which will override the default configuration.
	\param SageLine
		The line to be drawn to the screen.
	*******************************************************************************/
	static void Draw_Line(SageLine const& line);
	/*!*****************************************************************************
	\brief
		Draw a line to the screen.

		This function take in a arbitary start and end point, the color of the line and
		the size of the line defaulted to 15.f. When the camera is active, the position
		will be define in world space coordinates, else it will be in screen space.

		Since no configuration is given, the default configuration is used when drawing
		the line.

	\param start
		The start point of the line.
	\param end
		The end point of the line.
	\param color
		The color of the line.
	\param size
		The width of the line. This size is defaulted to 15.
	*******************************************************************************/
	static void Draw_Line(ToastBox::Vec2 start, ToastBox::Vec2 end, ToastBox::Vec4 color, float size = 15.f);
	/*!*****************************************************************************
	\brief
		Draw an arbitary point to the screen.

		This function take in a reference to a point object containing the position of
		the point and the color of the point. If, the camera is enableed, the point
		will be rendered in world space coordinates, else it will be rendered in screen
		space coordinates. Some data in the default configuration will be override by
		the point object.
	\param point
		The point object to be drawn to the screen.
	*******************************************************************************/
	static void Draw_Point(SagePoint const& point);
	/*!*****************************************************************************
	\brief
		Draw an arbitary point to the screen.

		This function take in a position, color and size of the point to be drawn to the
		screen. If the camera is active, the position will be in world space coordinates,
		else it will be in screen space coordinates. The default configuration is used
		when drawing the point.
	\param position
		The position of the point to be drawn.
	\param color
		The color of the point.
	\param size
		The size of the point. Defaulted to 15.f
	*******************************************************************************/
	static void Draw_Point(ToastBox::Vec2 position, ToastBox::Vec4 color, float size = 15.f);

	/*!*****************************************************************************
	\brief
		Draw a rectangle or a square to the screen.

		This function take in a position define in both the world and screen space,
		depending if the camera is enabled or not. It also take in the size
		of the rectangle or square and the color of the object. Since no
		render configuration is given, the default configuration is used when
		rendering. The given inputs will override the default configuration
		allowing different configuration to be used when rendering the object.

	\param x
		The x position of the rect.
	\param y
		The y position of the rect.
	\param width
		The width of the rect.
	\param height
		The height of the rect.
	\param color
		The color of the rect.
	*******************************************************************************/
	static void Draw_Rect(float x, float y, float width, float height, ToastBox::Vec4 color);

	/*!*****************************************************************************
	\brief
		Enable the bit for the associated bitmask options.

		This function take the bitmask options to be enabled and set the bit
		to 1. This will enable the options associated with the bitmask. This
		function modifies the default configuration of the renderer.

	\param options
		The bitmask options to be enabled.
	*******************************************************************************/
	static void Set_Option_On(int options);
	/*!*****************************************************************************
	\brief
		Disable the bit for the associated bitmask options.

		This function take the bitmask options to be enabled and set the bit
		to 0. This will disable the options associated with the bitmask. This
		function modifies the default configuration of the renderer.

	\param options
		The bitmask options to be disabled.
	*******************************************************************************/
	static void Set_Option_Off(int options);
	/*!*****************************************************************************
	\brief
		Set the default border width of the renderer.

		This function take in a value representing the width of the border and
		set the default border width of the renderer. This function modifies
		the default configuration of the renderer.

	\param width
		The width of the border.
	*******************************************************************************/
	static void Set_Border_Width(float width);
	/*!*****************************************************************************
	\brief
		Set the default border radius of the renderer.

		This function take in a value representing the border radius of the border and
		set the default border radius of the renderer. This function modifies
		the default configuration of the renderer.

	\param radius
		The radius of the border.
	*******************************************************************************/
	static void Set_Border_Radius(float radius);
	/*!*****************************************************************************
	\brief
		Set the default border color of the renderer.

		This function take in a value representing the border color of the border and
		set the default border color of the renderer. This function modifies
		the default configuration of the renderer.

	\param color
		The color of the border.
	*******************************************************************************/
	static void Set_Border_Color(glm::vec4 color);
	/*!*****************************************************************************
	\brief
		Set the default  color of the renderer.

		This function take in a value representing the default color of the renderer
		and set the default color configuration of the renderer. This function modifies
		the default configuration of the renderer.

	\param color
		The color of the items to be drawn.
	*******************************************************************************/
	static void Set_Color(glm::vec4 color);
	/*!*****************************************************************************
	\brief
		Set the default alpha value of the renderer.

		This function take in a alpha value representing the visibility of the
		model or object to be drawn. This function modifies the default configuration
		that the renderer uses when drawing objects and models.

	\param alpha
		The alpha value of the object to be drawn.
	*******************************************************************************/
	static void Set_Alpha(float alpha);
	/*!*****************************************************************************
	\brief
		Set the transformation matrix used when rendering objects and models.

		This function take in a transformation matrix to be used when rendering
		with default configuration. This function modifies the default matrix
		used when no matrix data is given.

	\param matrix
		The default transformation matrix to be used when rendering.
	*******************************************************************************/
	static void Set_Transformation_Matrix(glm::mat3& matrix);
	/*!*****************************************************************************
	\brief
		Clear the screen with the given color.

		This function take in a color and fill the framebuffer with the given color.
		Effectively, this clear the screen with the given color.

	\param clr
		The color to be used to clear the screen.
	*******************************************************************************/
	static void Clear_Color(ToastBox::Vec4 clr);

};




#endif //SAFERENDERER_HPP