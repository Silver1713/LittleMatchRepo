#ifndef INTENRAL_SAGERENDERER_HPP
#define INTENRAL_SAGERENDERER_HPP
#include <map>

#include "SageCamera.hpp"
#include "SageObject.hpp"
#include "SagePoint.hpp"
#include "SageViewport.hpp"



class SageModel;
class SageObject;
struct SageLine;
struct SagePoint;
class SageTexture;
class SageShader;

class SageCamera;




struct RENDER_CONFIG_INTERNAL
{
	unsigned int options;
	glm::vec4 color;
	float render_alpha;


	float border_width;
	float border_radius;
	glm::vec4 border_color;

	SageShader* shader;

	glm::mat3 transformation_matrix;
	ToastBox::Matrix3x3 matrix;

	SageTexture* current_texture;


	RENDER_CONFIG_INTERNAL(unsigned int options = 0, float render_alpha = 1.f, float border_width = 0, glm::vec4 color = { 0,0,0,1 }, glm::vec4 border_color = { 0,0,0,1 }, float border_radius = 0, SageShader* shader = nullptr, glm::mat3 transformation_matrix = glm::mat3(1.f), ToastBox::Matrix3x3 matrix = ToastBox::Matrix3x3(), SageTexture* current_texture = nullptr);





};


struct SageRendererInternal
{
	enum
	{
		I_SAGE_ENABLE_ALPHA = 1,
		I_SAGE_ENABLE_BORDER = 2,
		I_SAGE_ENABLE_VERTEX_COLOR = 4,
		I_SAGE_ENABLE_TEXTURE = 8,
		I_SAGE_ENABLE_CAMERA = 16,
	};
	enum RENDER_TYPE
	{
		TYPE_TRIANGLE,
		TYPE_TRIANGLE_STRIP,
		TYPE_TRIANGLE_FAN,
		TYPE_LINES,
		TYPE_LINES_STRIP,
		TYPE_LINES_LOOP,
		TYPE_POINTS,

	};

	enum RENDER_MODE
	{
		MODE_FILLED,
		MODE_LINES,
		MODE_POINTS,

	};


	enum SHAPE
	{
		SHAPE_SQUARE,
		SHAPE_CIRCLE,
		SHAPE_TRIANGLE,
		SHAPE_POLYGON,
		SHAPE_OBJECT_COUNT
	};

	static RENDER_CONFIG_INTERNAL default_config;
	static SageViewport viewport;
	static SageShader* default_shader;

	static void init();
	static SageCamera* camera;
	static void Set_Default_Shader(SageShader* shader);
	static void Set_Current_View(SageViewport& view);
	static void Set_Current_View(SageCamera* view);
	static void Draw_Filled(SageObject& object, RENDER_CONFIG_INTERNAL config);
	static void Draw_Filled(SageObject& object);
	static void Draw_Filled(SageModel& model, glm::mat3& matrix, RENDER_CONFIG_INTERNAL config = { (I_SAGE_ENABLE_ALPHA | I_SAGE_ENABLE_BORDER) });
	static void Draw_Filled(SageModel& model);

	static void Draw_Line(SageLine const& line, float size=15.f);
	static void Draw_Line(ToastBox::Vec2 start, ToastBox::Vec2 end, ToastBox::Vec4 color, float size=15.f);

	static void Draw_Point(SagePoint const& point);
	static void Draw_Point(ToastBox::Vec2 position, ToastBox::Vec4 color, float size = 15.f);


	static void Draw_Rect(float x, float y, float width, float height, ToastBox::Vec4 color);


	static void SetOptionOn(int options);
	static void SetOptionOff(int options);

	static void Set_Border_Width(float width);
	static void Set_Border_Radius(float radius);
	static void Set_Border_Color(glm::vec4 color);
	static void Set_Color(glm::vec4 color);
	static void Set_Alpha(float alpha);
	static void Set_Transformation_Matrix(glm::mat3& matrix);
	static void Clear_Color(ToastBox::Vec4 clr);

};




#endif //INTENRAL_SAFERENDERER_HPP