

#define GLFW_EXPOSE_NATIVE_WIN32
#include <iostream>
#include  <Windows.h>
#include <gtest/gtest.h>
#include <GLFW/glfw3.h>
#include "KeyInputs.h"
#include "GLFWHandler.h"
#include <GLFW/glfw3native.h>




GLFWwindow* window;
std::stringstream buffer;
std::streambuf* old;



void SimulateKeyPress(int key , int action)
{
	HWND win = glfwGetWin32Window(window);
	PostMessage(win, action, key, 0);
}

GLFWwindow* createWindow()
{
	if (!glfwInit())
	{
		std::cout << "GLFW failed to initialize" << std::endl;
		return nullptr;
	}

	window = glfwCreateWindow(800, 600, "Test Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "GLFW failed to create window" << std::endl;
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	//Set callbacks to the  internal input handler
	glfwSetKeyCallback(window, GLFWInputHandler::Key_Cb);
	glfwSetMouseButtonCallback(window, GLFWInputHandler::mouse_cb);
	return window;
}

void destroyWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

// Test for client interface.
TEST(GLFWTest, GLFWInit)
{
	window = createWindow();
	ASSERT_TRUE(window != nullptr);
}

TEST(InputTestSuite, GLFWMAPPING)
{
	// Test if the key mapping is correct
	ASSERT_EQ(GLFW_KEY_0, SAGE_KEY_0);
	ASSERT_EQ(GLFW_KEY_W, SAGE_KEY_W);
	ASSERT_EQ(GLFW_KEY_7, SAGE_KEY_7);

	ASSERT_EQ(GLFW_KEY_F12, SAGE_KEY_F12);

	ASSERT_FALSE(SAGE_KEY_COMMA == GLFW_KEY_PERIOD);

	ASSERT_EQ(GLFW_KEY_LAST, SAGE_KEY_LAST);


}

TEST(inputTestSuite, TapKeyFromClient)
{
	GLFWInputHandler::Key_Cb(window, GLFW_KEY_G, 0, GLFW_PRESS, 0);

	EXPECT_EQ(SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_G), true);
}

TEST(inputTestSuite, HoldKeyFromClient)
{
	GLFWInputHandler::Key_Cb(window, GLFW_KEY_G, 0, GLFW_REPEAT, 0);
	GLFWInputHandler::Key_Cb(window, GLFW_KEY_I, 0, GLFW_PRESS, 0);

	EXPECT_EQ(SAGEInputHandler::Get_Key(SAGE_KEY_G) && SAGEInputHandler::Get_Key(SAGE_KEY_I), true);
}

TEST(inputTestSuite, ReleaseKeyFromClient)
{
	GLFWInputHandler::Key_Cb(window, GLFW_KEY_E, 0, GLFW_PRESS, 0);
	EXPECT_EQ(SAGEInputHandler::Get_Key(SAGE_KEY_E), true);
	GLFWInputHandler::Key_Cb(window, GLFW_KEY_E, 0, GLFW_RELEASE, 0);

	EXPECT_EQ(SAGEInputHandler::Get_Key(SAGE_KEY_E), false);
}

TEST(inputTestSuite, Windows_InputKeyAOnce)
{
	WORD key = 'A'; // A
	SimulateKeyPress(key, 0); // Interact with microsoft windows.
	GLFWInputHandler::Poll_Events();
	ASSERT_EQ(SAGEInputHandler::Get_Key_Pressed(SAGE_KEY_A), true);
}

TEST(inputTestSuite, Windows_InputKeyARepeat)
{
	WORD key = 'A'; // A
	
	SimulateKeyPress(key, KEYEVENTF_KEYUP); // Interact with microsoft windows.
	
	GLFWInputHandler::Poll_Events();

	
	ASSERT_EQ(SAGEInputHandler::Get_Key(SAGE_KEY_A), false);
}



/// TEST CASES, for your use
void start_cout_record()
{
    buffer.clear();
    old = std::cout.rdbuf(buffer.rdbuf());
}

void stop_cout_record()
{
    std::cout.rdbuf(old);
}



TEST(GLFWTest, LOOP)
{
	while (!glfwWindowShouldClose(window))
	{
		SAGEInputHandler::update();

		if (SAGEInputHandler::Get_Key(SAGE_KEY_W))
		{
			EXPECT_TRUE(true);
			break;
		}

	}
}






