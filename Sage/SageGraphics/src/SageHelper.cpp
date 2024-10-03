#include "GL/glew.h"
#include "SageRenderer.hpp"
#include <iostream>

#include "SageHelper.hpp"
#include "SageMain.hpp"
#include "SageShader.hpp"

#include <vector>
#include "Vector2.h"


int SageHelper::WINDOW_WIDTH{};
int SageHelper::WINDOW_HEIGHT{};

char* SageHelper::WINDOW_TITLE{};

double SageHelper::delta_time{};
double SageHelper::fixed_delta_time{};
double SageHelper::FPS{};
SageWindow* SageHelper::sage_ptr_window{};

GLFWwindow* SageHelper::ptr_window{};

void GLAPIENTRY openglErrorCallback(GLenum _source, GLenum _type, GLuint _id,
	GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	(length);
	(userParam);
	std::cerr << "OpenGL Error:\n";
	std::cerr << "Source: " << _source << "\n";
	std::cerr << "Type: " << _type << "\n";
	std::cerr << "ID: " << _id << "\n";
	std::cerr << "Severity: " << severity << "\n";
	std::cerr << "Message: " << message << "\n";
}

int SageHelper::Init(int width, int height, const char* title, int UPS)
{

	fixed_delta_time = 1.0 / UPS;
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	WINDOW_TITLE = const_cast<char*>(title);


	//Error Callback
	glfwSetErrorCallback(Error_Cb);


	if (glfwInit())
	{
		std::cout << "GLFW initialized" << std::endl;
	}
	else
	{
		std::cerr << "GLFW failed to initialize" << std::endl;
		Exit();
		return 1;
	}


	sage_ptr_window = new SageWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title);


	sage_ptr_window->Activate_Context();

	sage_ptr_window->Set_Framebuffer_Callback();


	if (!ptr_window && !sage_ptr_window->check_active())
	{
		std::cerr << "Failed to create window" << '\n';
		Exit();
		return 1;
	}

	//Initialize GLEW after creating the context
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cerr << "Error: GLEW failed to initialize" << "\n"
			<< "Reason: " << glewGetErrorString(err) << '\n';
		Exit();
		return 1;

	}

	if (GLEW_VERSION_4_5) {
		std::cout << "GLEW Version 4.5 is supported" << std::endl;

	}
	else {


		std::cerr << "Warning: The driver may lack full compatibility with OpenGL 4.5, potentially limiting access to advanced features."
			"\nMake sure that your using a dGPU instead of a iGPU to take advantage of the advanced features of GL 4.5" << '\n';

	}

	return 0;
}

void SageHelper::Update()
{
	Update_Time(1.f);
}


void SageHelper::Update_Time(double update_fps_interval)
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


void SageHelper::Exit()
{
	delete sage_ptr_window;
	glfwTerminate();
}

void SageHelper::Error_Cb(int error, const char* description)
{
	std::cerr << "Error: " << error << " Description: " << description << '\n';
}


SageShader SageHelper::Compile_Shaders_From_File(const char* vertex_shader, const char* fragment_shader)
{
	SageShader shader{};
	bool a = shader.Compile_From_File(SageShader::SAGE_SHADER_TYPE::SAGE_VERTEX_SHADER, vertex_shader);

	bool b = shader.Compile_From_File(SageShader::SAGE_SHADER_TYPE::SAGE_FRAGMENT_SHADER, fragment_shader);
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
	shader.Get_Program_Handle();
	return shader;
}

std::vector<ToastBox::Vec2> SageHelper::AABBVertices(ToastBox::Vec2 _center, float _sidelength)
{
	std::vector<ToastBox::Vec2> vertices;
	float halfside = _sidelength / 2.0f;
	ToastBox::Vec2 bottom_left;
	bottom_left = { _center.x - halfside,_center.y - halfside };
	vertices.push_back(bottom_left);
	ToastBox::Vec2 bottom_right;
	bottom_right = { _center.x + halfside, _center.y - halfside };
	vertices.push_back(bottom_right);
	ToastBox::Vec2 top_right;
	top_right = { _center.x + halfside, _center.y + halfside };
	vertices.push_back(top_right);
	ToastBox::Vec2 top_left;
	top_left = { _center.x - halfside, _center.y + halfside };
	vertices.push_back(top_left);

	return vertices;
}



