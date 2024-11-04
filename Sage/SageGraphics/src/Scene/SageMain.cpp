
#include <iostream>
#include <array>
#include <sstream>

#include "Main.h"
#include "SageModel.hpp"
#include "SageShader.hpp"
#include "SageModelManager.hpp"
#include "SageObjectManager.hpp"
#include "SageObject.hpp"
#include "SageShaderManager.hpp"
//#include "SageCameraInternal.hpp"
#include "SageMain.hpp"

#include "SageCamera.hpp"
#include "SageHelper.hpp"

SageModel model;
SageViewport vp;
SageTexture p;
SageCamera cp;


void SageMain::init()
{
	//SageShaderManager::Add_Shader_Include("graphic_lib", "../SageGraphics/shaders/");
	//SageRenderer::init();

	
	/*vp = { glm::vec2{0,0}, {SageHelper::WINDOW_WIDTH, SageHelper::WINDOW_HEIGHT} };
	vp.calculate_viewport_xform();
	
	cp.init({ 0,0 }, { SageHelper::WINDOW_WIDTH / 1.f, SageHelper::WINDOW_HEIGHT / 1.f }, 0.f, SageCamera::SageCameraType::SAGE_ORTHO);




	SageRenderer::Set_Current_View(vp);
	SageRenderer::Set_Current_View(&cp);


	SageRenderer::camera->update();
	vp.setViewport();*/

}

void SageMain::update()
{
	// Camera movement
	//float camSpeed = 500.f;
	//if (SageHelper::Get_Key_Pressed(GLFW_KEY_D))
	//{
	//	
	//	camera.move_camera({ 1,0 }, camSpeed);

	//}
	//else if (SageHelper::Get_Key_Pressed(GLFW_KEY_A))
	//{
	//	camera.move_camera({ -1,0 }, camSpeed);
	//}
	//else if (SageHelper::Get_Key_Pressed(GLFW_KEY_W))
	//{
	//	camera.move_camera({ 0,1 }, camSpeed);
	//}
	//else if (SageHelper::Get_Key_Pressed(GLFW_KEY_S))
	//{
	//	camera.move_camera({ 0,-1 }, camSpeed);
	//}

	//for (auto& obj : SageObjectManager::objects)
	//{
	//	obj.second.update();
	//}

	//SageRenderer::camera->update();
}

void SageMain::draw()
{



	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	std::ostringstream ss{ "Scene 1" };

	ss << "Scene 1 | " << "FPS: " << std::fixed << SageHelper::FPS;
	//glfwSetWindowTitle(SageHelper::ptr_window, ss.str().c_str());
	SageHelper::sage_ptr_window->Set_Title(ss.str().c_str());

	




	//for (auto& obj : SageObjectManager::objects)
	//{
	//	SageRenderer::Draw_Filled(obj.second);
	//}
	//
	//glfwSetWindowTitle(SageHelper::ptr_window, "Scene 1");
}

void SageMain::exit()
{
	// Memory leak Preproduction
	//TODO: Clean up
}



