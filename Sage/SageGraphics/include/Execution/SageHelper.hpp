#ifndef SAGE_HELPER_HPP
#define  SAGE_HELPER_HPP
#include "GLFW/glfw3.h"

#include <map>
#include "SageWindow.hpp"
#include "SageShader.hpp"


struct SageHelper
{

	static int WINDOW_WIDTH, WINDOW_HEIGHT;
	static char* WINDOW_TITLE;
	static SageWindow* sage_ptr_window;
	static GLFWwindow* ptr_window;

	static double delta_time;
	static double fixed_delta_time;
	static double FPS;

	static int Init(int width, int height, const char* title, int UPS = 60);
	static void Update();
	static void Exit();

	static void Error_Cb(int error, const char* description);
	static SageShader Compile_Shaders_From_File(const char* _vertex_shader, const char* _fragment_shader);
	
	static void Update_Time(double _update_interval);

	static std::vector<ToastBox::Vec2> AABBVertices(ToastBox::Vec2 _center, float _sidelength);


};




#endif // SAGE_HELPER_HPP


