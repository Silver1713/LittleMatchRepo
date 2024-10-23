#include "EditorScene.hpp"

#include <imgui_impl_opengl3_loader.h>
#include <iostream>
#include <ostream>

#include "SageFrameBuffer.hpp"
#include "SageHelper.hpp"
#include "SageRenderer.hpp"

SageCamera EditorScene::camera;
SageViewport EditorScene::vp;

void EditorScene::Load()
{
	camera.init({ 0,0 }, { 1920, 1080 }, 0.f, SageCamera::SageCameraType::SAGE_ORTHO);
	vp = SageViewport({ 0,0 }, { 1920, 1080 });
}


void EditorScene::Init()
{
	camera.init({ 50,0 }, { static_cast<float>(SageHelper::WINDOW_WIDTH),  static_cast<float>(SageHelper::WINDOW_HEIGHT) }, 0.f, SageCamera::SageCameraType::SAGE_ORTHO);
	vp.set_dims({ static_cast<float>(SageHelper::WINDOW_WIDTH),  static_cast<float>(SageHelper::WINDOW_HEIGHT) });
	vp.calculate_viewport_xform();

	SageRenderer::Set_Current_View(&camera);
	SageRenderer::Set_Current_View(vp);

	vp.setViewport();

	
	
}


void EditorScene::Input()
{

}



void EditorScene::Update()
{
	
	//vp.setViewport();
	vp.calculate_viewport_xform();
	camera.update();
}


void EditorScene::Draw()
{
	//SageRenderer::Enable_OnScreenRender();
	SageRenderer::Clear_Color({0, 0, 1, 1});

	ToastBox::Vec2 pos = { 100,100 };

	int r = 5, c = 5;

	for (int x = 0; x < r; x++)
	{
		for (int y = 0; y < c; y++)
		{
			SageRenderer::Draw_Point({ pos.x + (x * 100), pos.y + (y * 100) }, { 1,0,0,1 }, 15.f);
		}
	}

	SageRenderer::Set_Option_Off(SageRenderer::SAGE_ENABLE_TEXTURE | SageRenderer::SAGE_ENABLE_BORDER);
	SageRenderer::Draw_Rect(500, 800, 200, 100, { 0,0,1,1 });
	
}

void EditorScene::Free()
{

}

void EditorScene::Unload()
{

}


