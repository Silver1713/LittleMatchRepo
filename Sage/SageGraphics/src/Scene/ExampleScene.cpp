
#include <iostream>
#include <array>
#include <sstream>
#include "ExampleScene.h" // TODO: Change this to the path of your header file
#include "Main.h"
#include "SageCamera.hpp"
#include "SageModel.hpp"
#include "SageShader.hpp"
#include "SageModelManager.hpp"
#include "SageObjectManager.hpp"
#include "SageObject.hpp"
#include "SageShaderManager.hpp"
//#include "SageCameraInternal.hpp"


SageViewport v_p;
SageTexture _p;

SageCamera camera2d;




void ExampleScene::init()
{
	SageShaderManager::add_shader_include("graphic_lib", "../SageGraphics/shaders/");
	SageRenderer::init();

	_p.load_texture("../SageIO/image/digipen_splash_screen.png", SageTexture::TEXTURE_UNIT_TYPE::SAGE_COLOR_TEXTURE_UNIT);
	v_p = { glm::vec2{0,0}, {SageHelper::WINDOW_WIDTH, SageHelper::WINDOW_HEIGHT} };
	v_p.calculate_viewport_xform();
	camera2d.init({ 0,0 }, { static_cast<float>(SageHelper::WINDOW_WIDTH), static_cast<float>(
			              SageHelper::WINDOW_HEIGHT)
	              }, 0.f);




	SageRenderer::SetCurrentView(v_p);




	SageObjectManager::CreatePrimitiveObject("Rect3", PRIMITIVE_OBJECT_RECT, { 2000,4000 }, { 1000,500 }, { 0,0 }, { 0,1,1,1 },
		{ 0,0,0,1 }, 0.5f);



	/*SageObjectManager::CreatePrimitiveObject("Rect1", PRIMITIVE_OBJECT_CIRCLE, { 0,0 }, { 50,50 }, { 0,0 }, { 1,0,1,1 },
		{ 0,0,0,1 }, 0.5f);*/

		/*SageObjectManager::CreatePrimitiveObject("Rect2", PRIMITIVE_OBJECT_RECT, { 1000,2000 }, { 1000,500 }, { 0,0 }, { 1,1,0,1 },
			{ 0,0,0,1 }, 0.5f);
		*/

		//SageObjectManager::objects["Rect1"].transform.position = { 0,0 };
		////set scale
		//SageObjectManager::objects["Rect1"].transform.scale = { 100.f,100.f };
		//SageObjectManager::objects["Rect1"].transform.orientation = { 0,0 };


		//// 2nd object
		//SageObjectManager::objects["Rect2"].transform.position = { -100,200 };
		//SageObjectManager::objects["Rect2"].transform.scale = { 200,200 };
		//SageObjectManager::objects["Rect2"].transform.orientation = { 0,0 };

		 // 3rd object

		 // Random transform
		SageObjectManager::objects["Rect3"].transform.position = {0.f,0 };
		SageObjectManager::objects["Rect3"].transform.scale = { 50.f,50.f };
		SageObjectManager::objects["Rect3"].transform.orientation = { 0,0 };

		SageObject* obj = &SageObjectManager::objects["Rect3"];
		

		//obj->GetMaterial().enable_texture = true;
		//obj->attach_texture(&p);



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


	v_p.setViewport();

	SageRenderer::SetCurrentView(&camera2d);
	

}

void ExampleScene::update()
{
	 
	float camSpeed = 100.f;
	if (SageHelper::Get_Key_Pressed(GLFW_KEY_D))
	{
		
		camera2d.MoveCamera({ 1,0 }, camSpeed);

	}
	else if (SageHelper::Get_Key_Pressed(GLFW_KEY_A))
	{
		camera2d.MoveCamera({ -1,0 }, camSpeed);
	}
	else if (SageHelper::Get_Key_Pressed(GLFW_KEY_W))
	{
		camera2d.MoveCamera({ 0,1 }, camSpeed);
	}
	else if (SageHelper::Get_Key_Pressed(GLFW_KEY_S))
	{
		camera2d.MoveCamera({ 0,-1 }, camSpeed);
	}

	for (auto& obj : SageObjectManager::objects)
	{
		obj.second.update();
	}

	camera2d.update();
}

void ExampleScene::draw()
{



	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	std::ostringstream ss{ "Scene 1" };

	ss << "Scene 1 | " << "FPS: " << std::fixed << SageHelper::FPS;
	//glfwSetWindowTitle(SageHelper::ptr_window, ss.str().c_str());
	SageHelper::sage_ptr_window->set_title(ss.str().c_str());



	SageRenderer::SetOptionOn(SageRenderer::SAGE_ENABLE_CAMERA);
	SageRenderer::SetOptionOff(SageRenderer::SAGE_ENABLE_BORDER);
	for (auto& obj : SageObjectManager::objects)
	{
		obj.second.GetMaterial().color = { 0,1,0,1 };
		SageRenderer::SetAlpha(1.f);
		//SageRenderer::SetOptionOn();/
		
		SageRenderer::DrawFilled(obj.second);
	}
	ToastBox::Vec2 start = { 0,0 };
	ToastBox::Vec2 end = { 100,0 };
	SageRenderer::DrawLine(start, end, ToastBox::Vec4{ 0,0,1,1 });

	SageRenderer::SetOptionOff(SageRenderer::SAGE_ENABLE_CAMERA | SageRenderer::SAGE_ENABLE_BORDER);
	SageRenderer::DrawRect(1000,500,50,50, {1,0,0,1});
	SageRenderer::DrawLine({ 0,0 }, { 500,200 }, { 1,0,0,1 });
	//SageRenderer::DrawPoint({ 500,100 }, { 0,0,1,1 }, 15.f);

	std::cout << camera2d.Screen_To_World({ 0,-250.f }).x << " " << camera2d.Screen_To_World({ 500,1000.f }).y << std::endl;
	SageRenderer::DrawPoint(camera2d.World_To_Screen({ 0,-250.f }), { 0,1,1,1 }, 15.f);
}

void ExampleScene::exit()
{
	// Memory leak Preproduction
	//TODO: Clean up
}


