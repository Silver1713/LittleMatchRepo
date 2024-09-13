#include "Key_Inputs.h"
#include "GLFW_Handler.h"

class SAGE_Input_Handler::impl
{
public:
	// Check if specific key is pressed once
	static bool Get_Key_Pressed(int keycode)
	{
		return GLFW_Input_Handler::Get_Key_Pressed(keycode);
	}

	// Check if specific key is held down
	static bool Get_Key(int keycode)
	{
		return GLFW_Input_Handler::Get_Key(keycode);
	}

	// Check if mouse is clicked once
	static bool Get_Mouse_Clicked(int mouse)
	{
		return GLFW_Input_Handler::Get_Key_Pressed(mouse);
	}

	// Check if mouse is held down
	static bool Get_Mouse(int mouse)
	{
		return GLFW_Input_Handler::Get_Key(mouse);
	}

	static void poll()
	{
		GLFW_Input_Handler::Poll_Events();
	}

	static void setcallback()
	{
		// Link Callback
		 glfwSetKeyCallback(glfwGetCurrentContext(), GLFW_Input_Handler::key_cb);
		 glfwSetMouseButtonCallback(glfwGetCurrentContext(), GLFW_Input_Handler::mouse_cb);
	}
};

bool SAGE_Input_Handler::Get_Key_Pressed(int keycode)
{
	return impl::Get_Key_Pressed(keycode);
}

bool SAGE_Input_Handler::Get_Key(int keycode)
{
	return impl::Get_Key(keycode);
}

bool SAGE_Input_Handler::Get_Mouse_Clicked(int mouse)
{
	return impl::Get_Mouse_Clicked(mouse);
}

bool SAGE_Input_Handler::Get_Mouse(int mouse)
{
	return impl::Get_Mouse(mouse);
}

void SAGE_Input_Handler::update()
{
	GLFW_Input_Handler::Poll_Events();
}

void SAGE_Input_Handler::init()
{
	impl::setcallback();
}



std::unique_ptr<SAGE_Input_Handler::impl> SAGE_Input_Handler::impl_pointer{std::make_unique<SAGE_Input_Handler::impl>()};