
#include "SageFontManager.hpp"
#include <iostream>
#include <array>
#include <sstream>
#include "ExampleScene.h" 
#include "Main.h"
#include "SageCamera.hpp"
#include "SageModelManager.hpp"
#include "SageObjectManager.hpp"
#include "SageObject.hpp"
#include "SageFrameBuffer.hpp"
#include "SageShaderManager.hpp"

#include "backward.hpp"

//

backward::SignalHandling sh;

SageViewport v_p;



SageCamera camera2d;

SageInstance instance;

SageFrameBuffer* frame_buffer;


//TextRenderer::SageFontManager fontManager;
//TextRenderer::SageText text;

//OpenGL err callback
void APIENTRY SageOpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::cout << "GL ERROR: " << message << std::endl;
}

void ExampleScene::init()
{
	

	//glDebugMessageCallback(SageOpenGLDebugCallback, nullptr);
	//// Enable
	//glEnable(GL_DEBUG_OUTPUT);
	//SageShaderManager::Add_Shader_Include("graphic_lib", "../SageGraphics/shaders/");
	//SageRenderer::Init();
	//SageModel* mdl = &SageModelManager::models["PRIMITIVE_RECT"];
	////instance.Init(&SageModelManager::models["PRIMITIVE_RECT"]);

	//// Set callback
	//fontManager.Startup();
	//fontManager.LoadFont("default", "../SageGraphics/font/TextFont.ttf");
	//fontManager.SetActiveFont("default");
	//text = fontManager.CreateTextObject("A", { 100,100 }, { 0,0,0,1 }, 48 , "default");

	//text.transform.position = { 0.f,0.f,0.f };
	//text.transform.scale = { 1000.f,1000.f,0.f };

	//text.SetPosition(text.transform.position);
	//

	/*glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPointSize(15.f);*/
	/*for (int i=0; i < 5;i++)
	{
		
		int randx = rand() % SageHelper::WINDOW_WIDTH;
		int randy = rand() % SageHelper::WINDOW_HEIGHT;

		float rand_sizex = (rand() % 50) + 10;
		float rand_sizey = (rand() % 50) + 10;
		glm::vec4 randomColor = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1 };
		instance.Append_Instance({ randx,randy }, { rand_sizex, rand_sizey }, { 0,0 }, randomColor, 1);
	}*/


	SageRenderer::Init();

	//_p.Load_Texture("../SageIO/image/digipen_splash_screen.png", SageTexture::TEXTURE_UNIT_TYPE::SAGE_COLOR_TEXTURE_UNIT);
	v_p = { glm::vec2{0,0}, {SageHelper::WINDOW_WIDTH, SageHelper::WINDOW_HEIGHT} };
	v_p.calculate_viewport_xform();
	camera2d.init({ 0,0 }, { static_cast<float>(SageHelper::WINDOW_WIDTH), static_cast<float>(
			              SageHelper::WINDOW_HEIGHT)
	              }, 0.f);




	SageRenderer::Set_Current_View(v_p);



	v_p.setViewport();

	SageRenderer::Set_Current_View(&camera2d);

	frame_buffer = new SageFrameBuffer(SageHelper::WINDOW_WIDTH, SageHelper::WINDOW_HEIGHT);

	SageRenderer::Set_Framebuffer(frame_buffer);
	//Check if framebuffer is attached using glGetIntegerv(GL_FRAMEBUFFER_BINDING, &frame_buffer_id);
	GLint bufferID;

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &bufferID);

	std::cout << "Frame buffer id: " << bufferID << std::endl;

	GLenum err = glGetError();

}

void ExampleScene::update()
{
	camera2d.update();
	instance.Update();
	//text.Update();

	GLenum g = glGetError();


}

void ExampleScene::draw()
{

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SageRenderer::Set_Option_Off(SageRenderer::SAGE_ENABLE_BORDER);
	SageRenderer::Set_Option_On(SageRenderer::SAGE_ENABLE_CAMERA);
	SageRenderer::Set_Alpha(1.f);
	SageRenderer::Set_Option_Off(SageRenderer::SAGE_ENABLE_CAMERA);
	SageRenderer::Enable_OffScreenRender();
	//SageRenderer::Draw_Filled_Instance(instance);
	SageRenderer::Enable_OnScreenRender();
	//SageRenderer::Draw_Filled_Instance(instance);
	
	//SageRenderer::Render_Text(text);


	

	
	

	
	std::cout << SageHelper::FPS << std::endl;

	
}

void ExampleScene::exit()
{
	// Memory leak Preproduction
	//TODO: Clean up
}



