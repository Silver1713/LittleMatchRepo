
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
const char* base_vtx_path = "../SageGraphics/shaders/BaseVertexShader.glsl";
const char* base_frag_path = "../SageGraphics/shaders/BaseFragmentShader.glsl";

SageModel model;
SageViewport vp;
SageTexture p;

//SageCameraInternal2D camera;

void SageMain::init()
{
	SageShaderManager::add_shader_include("graphic_lib", "../SageGraphics/shaders/");
	
	//p.load_texture("../SageIO/image/digipen_splash_screen.png", SageTexture::TEXTURE_UNIT_TYPE::SAGE_COLOR_TEXTURE_UNIT);
	vp = { glm::vec2{0,0}, {SageHelper::WINDOW_WIDTH, SageHelper::WINDOW_HEIGHT} };
	vp.calculate_viewport_xform();
	//camera.Init({ 0,0 }, { SageHelper::WINDOW_WIDTH, SageHelper::WINDOW_HEIGHT }, { 0,0 });
	


	
	SageRenderer::SetCurrentView(vp);




	



	//SageObjectManager::CreatePrimitiveObject("Rect1", PRIMITIVE_OBJECT_CIRCLE, { 0,0 }, { 10,50 }, { 0,0 }, { 1,0,1,1 },
	//	{ 0,0,0,1 }, 0.5f);

	/*SageObjectManager::CreatePrimitiveObject("Rect2", PRIMITIVE_OBJECT_RECT, { 1000,2000 }, { 1000,500 }, { 0,0 }, { 1,1,0,1 },
		{ 0,0,0,1 }, 0.5f);
	SageObjectManager::CreatePrimitiveObject("Rect3", PRIMITIVE_OBJECT_RECT, { 2000,4000 }, { 1000,500 }, { 0,0 }, { 0,1,1,1 },
		{ 0,0,0,1 }, 0.5f);*/

	//SageObjectManager::objects["Rect1"].transform.position = { 0,0 };
	////set scale
	//SageObjectManager::objects["Rect1"].transform.scale = { 100.f,100.f };
	//SageObjectManager::objects["Rect1"].transform.orientation = { 0,0 };


	//// 2nd object
	//SageObjectManager::objects["Rect2"].transform.position = { -100,200 };
	//SageObjectManager::objects["Rect2"].transform.scale = { 200,200 };
	//SageObjectManager::objects["Rect2"].transform.orientation = { 0,0 };

	// // 3rd object

	// // Random transform
	//SageObjectManager::objects["Rect3"].transform.position = { 0,0 };
	//SageObjectManager::objects["Rect3"].transform.scale = { 100,0 };
	//SageObjectManager::objects["Rect3"].transform.orientation = { 0,0 };

	//SageObject* obj = &SageObjectManager::objects["Rect3"];
	
	/*obj->GetMaterial().enable_texture = true;
	obj->attach_texture(&p);*/



	//// CreaTE 2500 objects randomize position and scale and color

	//for (int i =0; i < 2499; i++)
	//{
	//	SageObjectManager::CreatePrimitiveObject(std::to_string(i).c_str() ,PRIMITIVE_OBJECT_RECT, { 0,0 }, { 1000,500 }, { 0,0 }, { 1,0,1,1 },
	//		{ 0,0,0,1 }, 0.5f);

	//	SageObjectManager::objects[std::to_string(i).c_str()].transform.position = { rand() % SageHelper::WINDOW_WIDTH - 1000, rand() % 2000 - 1000 };
	//	SageObjectManager::objects[std::to_string(i).c_str()].transform.scale = { rand() % 2000 - 1000, rand() % 2000 - 1000 };
	//	SageObjectManager::objects[std::to_string(i).c_str()].transform.orientation = { 0,0 };

	//	SageObjectManager::objects[std::to_string(i).c_str()].GetMaterial().color = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1 };

	//}


	vp.setViewport();

}

void SageMain::update()
{
	// Camera movement
	float camSpeed = 500.f;
	/*if (SageHelper::Get_Key_Pressed(GLFW_KEY_D))
	{
		camera.move_camera({ 1,0 }, camSpeed);

	}
	else if (SageHelper::Get_Key_Pressed(GLFW_KEY_A))
	{
		camera.move_camera({ -1,0 }, camSpeed);
	}
	else if (SageHelper::Get_Key_Pressed(GLFW_KEY_W))
	{
		camera.move_camera({ 0,1 }, camSpeed);
	}
	else if (SageHelper::Get_Key_Pressed(GLFW_KEY_S))
	{
		camera.move_camera({ 0,-1 }, camSpeed);
	}*/

	for (auto& obj : SageObjectManager::objects)
	{
		obj.second.update();
	}

	//camera.Update();
}

void SageMain::draw()
{



	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	std::ostringstream ss{ "Scene 1" };

	ss << "Scene 1 | " << "FPS: " << std::fixed << SageHelper::FPS;
	//glfwSetWindowTitle(SageHelper::ptr_window, ss.str().c_str());
	SageHelper::sage_ptr_window->set_title(ss.str().c_str());




	for (auto& obj : SageObjectManager::objects)
	{
		SageRenderer::DrawFilled(obj.second, {
			false,true,15.f,0.f,{0,0,0,1},false
			});
	}

	// SageHelper::sage_ptr_window->set_title("Scene 1");
	//glfwSetWindowTitle(SageHelper::ptr_window, "Scene 1");
}

void SageMain::exit()
{
	// Memory leak Preproduction
	//TODO: Clean up
}



