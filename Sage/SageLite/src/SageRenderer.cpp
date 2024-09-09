#include "SageRenderer.hpp"

SageViewport SageRenderer::viewport;
void SageRenderer::DrawFilled(SageObject& object, RENDER_CONFIG config)
{
	SageObject::SageMaterial& mat = object.GetMaterial();
	if (config.enableBorder)
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

	if (config.useVertexColor)
	{
		mat.enable_vertex_color = true;
	}
	else
	{
		mat.enable_vertex_color = false;
		
	}

	object.draw(&viewport);
}

void SageRenderer::SetViewport(SageViewport& view)
{
	viewport = view;
}
