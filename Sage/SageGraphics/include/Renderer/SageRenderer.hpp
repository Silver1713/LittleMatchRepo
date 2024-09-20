#ifndef SAGERENDERER_HPP
#define SAGERENDERER_HPP
#include <map>
#include "SageModel.hpp"
#include "SageObject.hpp"
#include "SageViewport.hpp"
#include "SageShader.hpp"
#include "SageTexture.h"


class SageModel;
class SageObject;

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


struct RENDER_CONFIG
{
	unsigned int options;

	float render_alpha;

	float border_width;
	float border_radius;
	glm::vec4 border_color;

	SageShader* shader;

	glm::mat3 transformation_matrix;
	ToastBox::Matrix3x3 matrix;

	SageTexture* current_texture;

	

};


struct SageRenderer
{
	enum
	{
		SAGE_ENABLE_ALPHA = 1,
		SAGE_ENABLE_BORDER = 2,
		SAGE_ENABLE_VERTEX_COLOR = 4,
		SAGE_ENABLE_TEXTURE = 8,
		SAGE_ENABLE_CAMERA = 16,
	};

	static RENDER_CONFIG default_config;
	static SageViewport viewport;
	static SageShader* default_shader;

	static void init();
	//static SageCameraInternal2D* camera;
	static void Set_Default_Shader(SageShader* shader);
	static void SetCurrentView(SageViewport& view);
	//static void SetCurrentView(SageCameraInternal2D* view);
	static void DrawFilled(SageObject& object, RENDER_CONFIG config);
	static void DrawFilled(SageObject& object);
	static void DrawFilled(SageModel& model, glm::mat3& matrix, RENDER_CONFIG config = { (SAGE_ENABLE_ALPHA | SAGE_ENABLE_BORDER),0,0,{} });
	static void DrawFilled(SageModel& model);

	static void SetOptionOn(int options);
	static void SetOptionOff(int options);

	static void SetBorderWidth(float width);
	static void SetBorderRadius(float radius);
	static void SetBorderColor(glm::vec4 color);
	static void SetAlpha(float alpha);
	static void SetTransformationMatrix(glm::mat3& matrix);

};




#endif //SAFERENDERER_HPP