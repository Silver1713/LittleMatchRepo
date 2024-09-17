#include "SageRenderer.hpp"

SageViewport SageRenderer::viewport;
RENDER_CONFIG SageRenderer::default_config{SageRenderer::SAGE_ENABLE_TEXTURE | SageRenderer::SAGE_ENABLE_ALPHA, 15.f,15.f, {0,0,0,1}};
//SageCameraInternal2D* SageRenderer::camera;
void SageRenderer::DrawFilled(SageObject& object, RENDER_CONFIG config)
{
	SageObject::SageMaterial& mat = object.GetMaterial();
	if (config.options & SAGE_ENABLE_Border)
	{
		mat.enable_border_color = true;
		mat.border_color = config.border_color;
		mat.border_width = config.border_width;
		mat.border_radius = config.border_radius;
	}
	else
	{
		mat.enable_border_color = false;
	}

	if (config.options & SAGE_ENABLE_VERTEX_COLOR)
	{
		mat.enable_vertex_color = true;
	}
	else
	{
		mat.enable_vertex_color = false;
		
	}
	if (config.options & SAGE_ENABLE_CAMERA)
	{
		//object.draw(camera);
	}
	else
	{
		object.draw(&viewport);
	}
	//object.draw(&viewport);
}

void SageRenderer::SetCurrentView(SageViewport& view)
{
	viewport = view;
}

//void SageRenderer::SetCurrentView(SageCameraInternal2D* view)
//{
//	camera = view;
//}


void SageRenderer::DrawFilled(SageObject& object)
{
	SageObject::SageMaterial& mat = object.GetMaterial();
	if (default_config.options & SAGE_ENABLE_Border)
	{
		mat.enable_border_color = true;
		mat.border_color = default_config.border_color;
		mat.border_width = default_config.border_width;
		mat.border_radius = default_config.border_radius;
	}
	else
	{
		mat.enable_border_color = false;
	}

	if (default_config.options & SAGE_ENABLE_VERTEX_COLOR)
	{
		mat.enable_vertex_color = true;
	}
	else
	{
		mat.enable_vertex_color = false;

	}
	if (default_config.options & SAGE_ENABLE_CAMERA)
	{
		//object.draw(camera);
	}
	else
	{
		object.draw(&viewport);
	}
	//object.draw(&viewport);
}


void SageRenderer::SetOptionOn(int options)
{
	default_config.options |= options;
}

void SageRenderer::SetOptionOff(int options)
{
	default_config.options &= ~options;
}

