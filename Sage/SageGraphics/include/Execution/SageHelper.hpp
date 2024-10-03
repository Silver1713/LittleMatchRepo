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
	static std::map<int, std::byte> key_map;

	static double delta_time;
	static double fixed_delta_time;
	static double FPS;

	static int Init(int width, int height, const char* title, int UPS = 60);
	static void Update();
	static void Draw();
	static void Exit();

	// Callbacks
	static void Error_Cb(int error, const char* description);

	static void Framebuffer_Size_Cb(GLFWwindow* window, int width, int height);
	// Input - Keyboard
	static void Key_Cb(GLFWwindow* window, int key, int scancode, int action, int mods);

	// Input - Mouse Button
	static void mouse_button_cb(GLFWwindow* window, int button, int action, int mods);

	// Input - Mouse Cursor
	static void mouse_pos_cb(GLFWwindow* window, double xpos, double ypos);

	// Input - Mouse Scroll
	static void mouse_scroll_cb(GLFWwindow* window, double xoffset, double yoffset);

	/*******************************************************************************/
	/*!
	 * Get key press in the current frame
	 * @param key The key to check
	 * @return True, when the key is pressed
	 */
	/********************************************************************************/
	static bool Get_Key(int key);

	/********************************************************************************/
	/*!
	 * Get key press in the previous frame, this only get key that is pressed once and not
	 * held down.
	 * @param key  The key to check
	 * @return True, when the key is pressed
	 */
	/*********************************************************************************/
	static bool Get_Key_Pressed(int key);


	static SageShader Compile_Shaders_From_File(const char* _vertex_shader, const char* _fragment_shader);
	
	static void Update_Time(double _update_interval);




	static std::vector<ToastBox::Vec2> AABBVertices(ToastBox::Vec2 _center, float _sidelength);


};




#endif // SAGE_HELPER_HPP


