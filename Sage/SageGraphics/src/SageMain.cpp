
#include <iostream>
#include <array>
#include <sstream>

#include "Main.h"
#include "SageModel.hpp"
#include "SageShader.hpp"
#include "SageModelManager.hpp"
#include "SageObjectManager.hpp"
#include "SageObject.hpp"
const char* base_vtx_path = "../SageGraphics/shaders/BaseVertexShader.glsl";
const char* base_frag_path = "../SageGraphics/shaders/BaseFragmentShader.glsl";

SageModel model;
SageShader shdr;
//SageObject obj;
SageViewport vp;

SageTexture* p;

void SageMain::init()
{
	p = new SageTexture("../SageIO/image/digipen_splash_screen.png");
	vp = { glm::vec2{0,0}, {SageHelper::WINDOW_WIDTH, SageHelper::WINDOW_HEIGHT} };
	vp.calculate_viewport_xform();
	SageRenderer::SetViewport(vp);

	



	SageObjectManager::CreatePrimitiveObject("Rect1", PRIMITIVE_OBJECT_RECT, { 0,0 }, { 1000,500 }, { 0,0 }, { 1,0,1,1 },
		{ 0,0,0,1 }, 0.5f);

	SageObjectManager::CreatePrimitiveObject("Rect2", PRIMITIVE_OBJECT_RECT, { 1000,2000 }, { 1000,500 }, { 0,0 }, { 1,1,0,1 },
		{ 0,0,0,1 }, 0.5f);
	SageObjectManager::CreatePrimitiveObject("Rect3", PRIMITIVE_OBJECT_RECT, { 2000,4000 }, { 1000,500 }, { 0,0 }, { 0,1,1,1 },
		{ 0,0,0,1 }, 0.5f);

	SageObjectManager::objects["Rect1"].transform.position = { 0,0 };
	//set scale
	SageObjectManager::objects["Rect1"].transform.scale = { 1000,500 };
	SageObjectManager::objects["Rect1"].transform.orientation = { 0,0 };


	// 2nd object
	SageObjectManager::objects["Rect2"].transform.position = { -500,2000 };
	SageObjectManager::objects["Rect2"].transform.scale = { 1000,500 };
	SageObjectManager::objects["Rect2"].transform.orientation = { 0,0 };

	// 3rd object

	// Random transform
	SageObjectManager::objects["Rect3"].transform.position = { 0,0 };
	SageObjectManager::objects["Rect3"].transform.scale = { 5000,5000 };
	SageObjectManager::objects["Rect3"].transform.orientation = { 0,0 };

	SageObject* obj = &SageObjectManager::objects["Rect3"];
	
	obj->GetMaterial().enable_texture = true;
	obj->attach_texture(p);



	//CreaTE 2500 objects randomize position and scale and color

	/*for (int i =0; i < 2499; i++)
	{
		SageObjectManager::CreatePrimitiveObject(std::to_string(i).c_str() ,PRIMITIVE_OBJECT_RECT, { 0,0 }, { 1000,500 }, { 0,0 }, { 1,0,1,1 },
			{ 0,0,0,1 }, 0.5f);

		SageObjectManager::objects[std::to_string(i).c_str()].transform.position = { rand() % 2000 - 1000, rand() % 2000 - 1000 };
		SageObjectManager::objects[std::to_string(i).c_str()].transform.scale = { rand() % 2000 - 1000, rand() % 2000 - 1000 };
		SageObjectManager::objects[std::to_string(i).c_str()].transform.orientation = { 0,0 };

		SageObjectManager::objects[std::to_string(i).c_str()].GetMaterial().color = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1 };

	}*/


	vp.setViewport();

}

void SageMain::update()
{
	for (auto& obj : SageObjectManager::objects)
	{
		obj.second.update();
	}


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
			true,false,15.f,0.f,{0,0,0,1},false
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



