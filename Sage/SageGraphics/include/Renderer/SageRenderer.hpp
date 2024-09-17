#ifndef SAGERENDERER_HPP
#define SAGERENDERER_HPP
#include <map>
#include "SageModel.hpp"
#include "SageObject.hpp"
#include "SageViewport.hpp"


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
	bool enableBorder;
	bool useVertexColor;

	float border_width;
	float border_radius;


	glm::vec4 border_color;


	bool useCamera;

};


struct SageRenderer
{
	static SageViewport viewport;
	//static SageCameraInternal2D* camera;
	static void SetCurrentView(SageViewport& view);
	//static void SetCurrentView(SageCameraInternal2D* view);
	static void DrawFilled(SageObject& object , RENDER_CONFIG config={false,false,0,0,{},false});

};


#endif //SAFERENDERER_HPP