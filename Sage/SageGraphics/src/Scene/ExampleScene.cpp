
#include <iostream>
#include <array>
#include <sstream>
#include "ExampleScene.h" 
#include "Main.h"
#include "SageCamera.hpp"
#include "SageModel.hpp"
#include "SageShader.hpp"
#include "SageModelManager.hpp"
#include "SageObjectManager.hpp"
#include "SageObject.hpp"
#include "SageShaderManager.hpp"
//#include "SageCameraInternal.hpp"

//
SageViewport v_p;


SageCamera camera2d;

SageInstance instance;

//OpenGL err callback
void APIENTRY SageOpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::cout << "GL ERROR: " << message << std::endl;
}

void ExampleScene::init()
{
	// Set callback
	
	glDebugMessageCallback(SageOpenGLDebugCallback, nullptr);
	// Enable
	glEnable(GL_DEBUG_OUTPUT);
	SageShaderManager::Add_Shader_Include("graphic_lib", "../SageGraphics/shaders/");
	SageRenderer::Init();
	SageModel* mdl = &SageModelManager::models["PRIMITIVE_RECT"];
	instance.Init(&SageModelManager::models["PRIMITIVE_RECT"]);
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPointSize(15.f);*/
	for (int i=0; i < 10000;i++)
	{
		
		int randx = rand() % SageHelper::WINDOW_WIDTH;
		int randy = rand() % SageHelper::WINDOW_HEIGHT;

		float rand_sizex = (rand() % 50) + 10;
		float rand_sizey = (rand() % 50) + 10;
		glm::vec4 randomColor = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1 };
		instance.Append_Instance({ randx,randy }, { rand_sizex, rand_sizey }, { 0,0 }, randomColor, 1);
	}


	//SageRenderer::Init();

	//_p.Load_Texture("../SageIO/image/digipen_splash_screen.png", SageTexture::TEXTURE_UNIT_TYPE::SAGE_COLOR_TEXTURE_UNIT);
	v_p = { glm::vec2{0,0}, {SageHelper::WINDOW_WIDTH, SageHelper::WINDOW_HEIGHT} };
	v_p.calculate_viewport_xform();
	camera2d.init({ 0,0 }, { static_cast<float>(SageHelper::WINDOW_WIDTH), static_cast<float>(
			              SageHelper::WINDOW_HEIGHT)
	              }, 0.f);




	SageRenderer::Set_Current_View(v_p);



	//SageObjectManager::Create_Primitive_Object("Rect3", PRIMITIVE_OBJECT_RECT, { 2000,4000 }, { 1000,500 }, { 0,0 }, { 0,0,1,1 },
	//	{ 0,0,0,1 }, 0.5f);
	//SageObjectManager::Create_Primitive_Object("Circle3", PRIMITIVE_OBJECT_CIRCLE, { 2000,4000 }, { 1000,500 }, { 0,0 }, { 0,0,1,1 },
	//	{ 0,0,0,1 }, 0.5f);




	//


	///*SageObjectManager::CreatePrimitiveObject("Rect1", PRIMITIVE_OBJECT_CIRCLE, { 0,0 }, { 50,50 }, { 0,0 }, { 1,0,1,1 },
	//	{ 0,0,0,1 }, 0.5f);*/

	//	/*SageObjectManager::CreatePrimitiveObject("Rect2", PRIMITIVE_OBJECT_RECT, { 1000,2000 }, { 1000,500 }, { 0,0 }, { 1,1,0,1 },
	//		{ 0,0,0,1 }, 0.5f);
	//	*/

	//	//SageObjectManager::objects["Rect1"].transform.position = { 0,0 };
	//	////set scale
	//	//SageObjectManager::objects["Rect1"].transform.scale = { 100.f,100.f };
	//	//SageObjectManager::objects["Rect1"].transform.orientation = { 0,0 };


	//	//// 2nd object
	//	//SageObjectManager::objects["Rect2"].transform.position = { -100,200 };
	//	//SageObjectManager::objects["Rect2"].transform.scale = { 200,200 };
	//	//SageObjectManager::objects["Rect2"].transform.orientation = { 0,0 };

	//	 // 3rd object

	//	 // Random transform
	//	SageObjectManager::objects["Circle3"].transform.position = {0.f,0 };
	//	SageObjectManager::objects["Circle3"].transform.scale = { 50.f,50.f };
	//	SageObjectManager::objects["Circle3"].transform.orientation = { 0,0 };

	//	SageObjectManager::objects["Rect3"].transform.position = { 30.f,180.f };
	//	SageObjectManager::objects["Rect3"].transform.scale = { 150.f,50.f };
	//	SageObjectManager::objects["Rect3"].transform.orientation = { 0,0 };
	//	SageObjectManager::objects["Rect3"].GetMaterial().color = { 1,0,1,1 };
	////	SageObject* obj = &SageObjectManager::objects["Circle3"];
	//	

	//	//obj->GetMaterial().enable_texture = true;
	//	//obj->attach_texture(&p);



	//	//// CreaTE 2500 objects randomize position and scale and color

	//	//for (int i =0; i < 2499; i++)
	//	//{
	//	//	SageObjectManager::CreatePrimitiveObject(std::to_string(i).c_str() ,PRIMITIVE_OBJECT_RECT, { 0,0 }, { 1000,500 }, { 0,0 }, { 1,0,1,1 },
	//	//		{ 0,0,0,1 }, 0.5f);

	//	//	SageObjectManager::objects[std::to_string(i).c_str()].transform.position = { rand() % SageHelper::WINDOW_WIDTH - 1000, rand() % 2000 - 1000 };
	//	//	SageObjectManager::objects[std::to_string(i).c_str()].transform.scale = { rand() % 2000 - 1000, rand() % 2000 - 1000 };
	//	//	SageObjectManager::objects[std::to_string(i).c_str()].transform.orientation = { 0,0 };

	//	//	SageObjectManager::objects[std::to_string(i).c_str()].GetMaterial().color = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1 };

	//	//}


	v_p.setViewport();

	SageRenderer::Set_Current_View(&camera2d);
	

}

void ExampleScene::update()
{
	camera2d.update();
	instance.Update();
	 
	/*float camSpeed = 100.f;
	if (SageHelper::Get_Key_Pressed(GLFW_KEY_D))
	{
		
		camera2d.Move_Camera({ 1,0 }, camSpeed);

	}
	else if (SageHelper::Get_Key_Pressed(GLFW_KEY_A))
	{
		camera2d.Move_Camera({ -1,0 }, camSpeed);
	}
	else if (SageHelper::Get_Key_Pressed(GLFW_KEY_W))
	{
		camera2d.Move_Camera({ 0,1 }, camSpeed);
	}
	else if (SageHelper::Get_Key_Pressed(GLFW_KEY_S))
	{
		camera2d.Move_Camera({ 0,-1 }, camSpeed);
	}

	for (auto& obj : SageObjectManager::objects)
	{
		obj.second.Update();
	}

	camera2d.update();*/
}

void ExampleScene::draw()
{
	

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SageRenderer::Set_Option_Off(SageRenderer::SAGE_ENABLE_BORDER);
	SageRenderer::Set_Option_On(SageRenderer::SAGE_ENABLE_CAMERA);
	SageRenderer::Set_Alpha(1.f);
	SageRenderer::Set_Option_Off(SageRenderer::SAGE_ENABLE_CAMERA);
	SageRenderer::Draw_Filled_Instance(instance);
	//Check for GLERR
	

	//SageRenderer::Draw_Rect(0, 0, 500, 1000, { 0,1,0,1 });

	//glclearcolor(0, 0, 0, 1);
	//glclear(gl_color_buffer_bit);
	//std::ostringstream ss{ "scene 1" };

	//ss << "scene 1 | " << "fps: " << std::fixed << sagehelper::fps;
	////glfwsetwindowtitle(sagehelper::ptr_window, ss.str().c_str());
	//sagehelper::sage_ptr_window->set_title(ss.str().c_str());




	//SageRenderer::Set_Option_On(SageRenderer::SAGE_ENABLE_CAMERA);
	//SageRenderer::Set_Option_Off(SageRenderer::SAGE_ENABLE_BORDER);
	//for (auto& obj : SageObjectManager::objects)
	//{
	//	//obj.second.GetMaterial().color = { 0,1,0,1 };
	//	SageRenderer::Set_Alpha(1.f);
	//	//SageRenderer::Set_Option_On();/
	//	
	//	SageRenderer::Draw_Filled(obj.second);
	//	float scale = obj.second.transform.scale.x;
	//	if (obj.second.obj_mesh.model_ref->get_shape_type() == static_cast<int>(
	//		PrimitiveShape::PRIMITIVE_CIRCLE))
	//	{
	//		scale *= 2;
	//	}
	//	std::vector<ToastBox::Vec2> aabb = SageHelper::AABBVertices({ obj.second.transform.position.x,obj.second.transform.position.y }, scale);
	//	for (ToastBox::Vec2& v : aabb)
	//	{
	//		
	//		SageRenderer::Draw_Point(v, { 1,0,0,1 }, 5.f);

	//	}
	//	for (int i =0; i < aabb.size(); i++)
	//	{
	//		if (i < aabb.size() - 1)
	//		{
	//			SageRenderer::Draw_Line(aabb[i], aabb[i + 1], { 1,0,0,1 });
	//		}
	//		else
	//		{
	//			SageRenderer::Draw_Line(aabb[i], aabb[0], { 1,0,0,1 });
	//		}
	//	}
	//}
	std::cout << SageHelper::FPS << std::endl;

	//ToastBox::Vec2 start = { 0,0 };
	//ToastBox::Vec2 end = { 100,0 };
	//SageRenderer::Draw_Line(start, end, ToastBox::Vec4{ 0,0,1,1 });

	//SageRenderer::Set_Option_Off(SageRenderer::SAGE_ENABLE_CAMERA | SageRenderer::SAGE_ENABLE_BORDER);
	//SageRenderer::Draw_Rect(1000,500,50,50, {1,0,0,1});
	//SageRenderer::Draw_Line({ 0,0 }, { 500,200 }, { 1,0,0,1 });
	////SageRenderer::Draw_Point({ 500,100 }, { 0,0,1,1 }, 15.f);

	//std::cout << camera2d.Screen_To_World({ 0,-250.f }).x << " " << camera2d.Screen_To_World({ 500,1000.f }).y << std::endl;
	//SageRenderer::Draw_Point(camera2d.World_To_Screen({ 0,-250.f }), { 0,1,1,1 }, 15.f);
}

void ExampleScene::exit()
{
	// Memory leak Preproduction
	//TODO: Clean up
}



