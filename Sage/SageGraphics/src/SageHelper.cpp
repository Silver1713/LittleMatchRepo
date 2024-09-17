
#include <GL/glew.h>
#include <iostream>

#include "SageHelper.hpp"
#include "SageMain.hpp"
#include "SageShader.hpp"




int SageHelper::WINDOW_WIDTH{};
int SageHelper::WINDOW_HEIGHT{};

char* SageHelper::WINDOW_TITLE{};

double SageHelper::delta_time{};
double SageHelper::fixed_delta_time{};
double SageHelper::FPS{};
SageWindow* SageHelper::sage_ptr_window{};

GLFWwindow* SageHelper::ptr_window{};
std::map<int, std::byte> SageHelper::key_map;

void GLAPIENTRY openglErrorCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	std::cerr << "OpenGL Error:\n";
	std::cerr << "Source: " << source << "\n";
	std::cerr << "Type: " << type << "\n";
	std::cerr << "ID: " << id << "\n";
	std::cerr << "Severity: " << severity << "\n";
	std::cerr << "Message: " << message << "\n";
}

int SageHelper::init(int width, int height, const char* title, int UPS)
{
	fixed_delta_time = 1.0 / UPS;
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	WINDOW_TITLE = const_cast<char*>(title);

	
	//Error Callback
	glfwSetErrorCallback(error_cb);


	if (glfwInit())
	{
		std::cout << "GLFW initialized" << std::endl;
	}
	else
	{
		std::cerr << "GLFW failed to initialize" << std::endl;
		exit();
		return 1;
	}


	sage_ptr_window = new SageWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title);
	//ptr_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	//glfwMakeContextCurrent(ptr_window);

	sage_ptr_window->Activate_Context();
	
	sage_ptr_window->set_framebuffer_callback();


	if (!ptr_window && !sage_ptr_window->check_active())
	{
		std::cerr << "Failed to create window" << '\n';
		exit();
		return 1;
	}

	//Initialize GLEW after creating the context
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cerr << "Error: GLEW failed to initialize" << "\n"
			<< "Reason: " << glewGetErrorString(err) << '\n';
		exit();
		return 1;

	}

	if (GLEW_VERSION_4_5) {
		std::cout << "GLEW Version 4.5 is supported" << std::endl;

	}
	else {
#if _DEBUG
		std::cout << "Current graphic driver do not support GLEW 4.5.." << '\n' <<
			"It could also be that you're using integrated GPU (cuz laptop)" << '\n'
			<< "Here's the version FYI: " << glGetString(GL_VERSION) << '\n';
#endif
#if NDEBUG
		std::cerr << "Warning: The driver may lack full compatibility with OpenGL 4.5, potentially limiting access to advanced features."
			"\nMake sure that your using a dGPU instead of a iGPU to take advantage of the advanced features of GL 4.5" << '\n';

#endif
	}




	//Event Callbacks
	/*glfwSetFramebufferSizeCallback(ptr_window, framebuffer_size_cb);
	glfwSetKeyCallback(ptr_window, key_cb);
	glfwSetMouseButtonCallback(ptr_window, mouse_button_cb);
	glfwSetCursorPosCallback(ptr_window, mouse_pos_cb);
	glfwSetScrollCallback(ptr_window, mouse_scroll_cb);*/


	//Default Cursor

	/*glfwSetInputMode(ptr_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);





	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(openglErrorCallback, nullptr);*/

	glfwSetKeyCallback(glfwGetCurrentContext(), key_cb);
	return 0;
}



void SageHelper::update()
{
	update_time(1.f);
#if _DEBUG
#endif
}


void SageHelper::update_time(double update_fps_interval)
{
	static double last_time = glfwGetTime();
	double current_time = glfwGetTime();
	delta_time = current_time - last_time;
	last_time = current_time;

	static double last_fps_time{};

	last_fps_time += delta_time;

	if (last_fps_time >= update_fps_interval)
	{
		FPS = 1.0 / delta_time;
		last_fps_time = 0;
	}







}


void SageHelper::draw()
{
#if _DEBUG

#endif
}

void SageHelper::exit()
{

	glfwTerminate();
}


void SageHelper::key_cb(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	switch (action)
	{
	case GLFW_PRESS:
		key_map[key] = std::byte{ 1 };
#if _DEBUG
		std::cout << "Key is Pressed\n";
#endif
		break;
	case GLFW_RELEASE:
		key_map[key] = std::byte{ 0 };
#if _DEBUG
		std::cout << "Key is Released\n";
#endif
		break;
	case GLFW_REPEAT:
		key_map[key] = std::byte{ 2 };
#if _DEBUG
		std::cout << "Key is Hold\n";
#endif
		break;
	default:
		break;
	}



}

void SageHelper::mouse_button_cb(GLFWwindow* window, int button, int action, int mods)
{
#if _DEBUG
	std::cout << "Mouse Button: " << button << " Action: " << action << " Mods: " << mods << '\n';
#endif
}

void SageHelper::mouse_pos_cb(GLFWwindow* window, double xpos, double ypos)
{
#if _DEBUG
	std::cout << "Mouse Position: x:" << xpos << ", y:" << ypos << '\n';
#endif
}

void SageHelper::mouse_scroll_cb(GLFWwindow* window, double xoffset, double yoffset)
{
#if _DEBUG
	std::cout << "Mouse Scroll: x:" << xoffset << ", y:" << yoffset << '\n';
#endif

}


bool SageHelper::Get_Key(int key)
{
	return key_map[key] == std::byte{ 1 };
}

bool SageHelper::Get_Key_Pressed(int key)
{
	return key_map[key] == std::byte{ 2 } || key_map[key] == std::byte{ 1 };
}

void SageHelper::framebuffer_size_cb(GLFWwindow* window, int width, int height)
{
#if _DEBUG
	std::cout << "Framebuffer Size: width: " << width << ", height: " << height << '\n';
#endif
}


void SageHelper::error_cb(int error, const char* description)
{
	std::cerr << "Error: " << error << " Description: " << description << '\n';
}


SageShader SageHelper::CompileShadersFromFile(const char* vertex_shader, const char* fragment_shader)
{
	SageShader shader{};
	bool a = shader.CompileFromFile(SageShader::SAGE_SHADER_TYPE::SAGE_VERTEX_SHADER, vertex_shader);

	bool b = shader.CompileFromFile(SageShader::SAGE_SHADER_TYPE::SAGE_FRAGMENT_SHADER, fragment_shader);
	if (a & b)
	{
		std::cout << "Shaders compiled successfully" << '\n';
	}
	else
	{
		std::cerr << "Shaders failed to compile" << '\n';
		std::exit(EXIT_FAILURE);
	}

	bool c = shader.Link();
	if (c)
	{
		std::cout << "Shaders linked successfully" << '\n';
	}
	else
	{
		std::cerr << "Shaders failed to link" << '\n';
		std::exit(EXIT_FAILURE);
	}
	bool d = shader.Validate();

	if (d)
	{
		std::cout << "Shaders validated successfully" << '\n';
	}
	else
	{
		std::cerr << "Shaders failed to validate" << '\n';
		std::exit(EXIT_FAILURE);
	}
	shader.GetProgramHandle();
	return shader;
}


