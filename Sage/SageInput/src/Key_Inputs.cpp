#include "Key_Inputs.h"

#include <iostream>

#include "GLFW_Handler.h"
#include "SageInput_PIML.h"
#if 0
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
#endif

void SAGE_Input_Handler::customSageInputPIMPLDelete(void*& p)
{
	delete static_cast<SageInput_PIML*>(p);

	p = nullptr;

}

std::unique_ptr<void, decltype(&SAGE_Input_Handler::customSageInputPIMPLDelete)> SAGE_Input_Handler::impl_pointer{std::make_unique<SageInput_PIML>().release()	, customSageInputPIMPLDelete};

bool SAGE_Input_Handler::Get_Key_Pressed(int keycode)
{
	
	return SageInput_PIML::Get_Key_Pressed(keycode);
}

bool SAGE_Input_Handler::Get_Key(int keycode)
{
	return SageInput_PIML::Get_Key(keycode);
}

bool SAGE_Input_Handler::Get_Mouse_Clicked(int mouse)
{
	return SageInput_PIML::Get_Mouse_Clicked(mouse);
}

bool SAGE_Input_Handler::Get_Mouse(int mouse)
{
	return SageInput_PIML::Get_Mouse(mouse);
}

void SAGE_Input_Handler::update()
{
	GLFW_Input_Handler::Poll_Events();
}

void SAGE_Input_Handler::init()
{
	SageInput_PIML::Set_Callback();
}



