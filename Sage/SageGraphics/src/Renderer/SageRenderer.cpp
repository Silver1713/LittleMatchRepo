#include "SageRendererInternal.hpp"
#include "SageRenderer.hpp"


class SageCameraInternal2D;
SageViewport SageRenderer::viewport;
RENDER_CONFIG SageRenderer::default_config{ SageRenderer::SAGE_ENABLE_TEXTURE | SageRenderer::SAGE_ENABLE_ALPHA};
SageCamera* SageRenderer::camera;
SageShader* SageRenderer::default_shader;
void SageRenderer::DrawFilled(SageObject& object, RENDER_CONFIG config)
{
	SageRendererInternal::DrawFilled(object, {
		config.options, config.render_alpha, config.border_width,
		{config.color.r,config.color.g,config.color.b,config.color.a},
		{config.border_color.r,config.border_color.g,config.border_color.b,config.border_color.a},
		config.border_radius, config.shader,
		config.transformation_matrix,
		config.matrix,
		config.current_texture

	});

}

void SageRenderer::SetCurrentView(SageViewport& view)
{
	viewport = view;
	SageRendererInternal::SetCurrentView(view);
}

void SageRenderer::SetCurrentView(SageCamera* view)
{
	camera = view;
	SageRendererInternal::SetCurrentView(view);
}


void SageRenderer::DrawFilled(SageObject& object)
{
	SageRendererInternal::DrawFilled(object);
}





void SageRenderer::SetOptionOn(int options)
{
	SageRenderer::default_config.options |= options;
	SageRendererInternal::default_config.options |= options;
}

void SageRenderer::SetOptionOff(int options)
{
	default_config.options &= ~options;
	SageRendererInternal::default_config.options &= ~options;
}

void SageRenderer::DrawFilled(SageModel& model)
{
	SageRendererInternal::DrawFilled(model);
}

void SageRenderer::DrawFilled(SageModel& model, glm::mat3& matrix, RENDER_CONFIG config)
{

	SageRendererInternal::DrawFilled(model, matrix, {
		config.options, config.render_alpha, config.border_width,
		{config.color.r,config.color.g,config.color.b,config.color.a},
		{config.border_color.r,config.border_color.g,config.border_color.b,config.border_color.a},
		config.border_radius, config.shader,
		config.transformation_matrix,
		config.matrix,
		config.current_texture

		});

}


void SageRenderer::init()
{
	SageRendererInternal::init();
	
}



void SageRenderer::SetAlpha(float alpha)
{
	default_config.render_alpha = alpha;
	SageRendererInternal::SetAlpha(alpha);
}

void SageRenderer::SetBorderColor(glm::vec4 color)
{
	default_config.border_color = color;
	SageRendererInternal::SetBorderColor(color);
}

void SageRenderer::SetBorderRadius(float radius)
{
	default_config.border_radius = radius;
	SageRendererInternal::SetBorderRadius(radius);
}

void SageRenderer::SetBorderWidth(float width)
{
	default_config.border_width = width;
	SageRendererInternal::SetBorderWidth(width);
}

void SageRenderer::SetTransformationMatrix(glm::mat3& matrix)
{
	default_config.transformation_matrix = matrix;
	SageRendererInternal::SetTransformationMatrix(matrix);
}

void SageRenderer::Set_Default_Shader(SageShader* shader)
{
	default_shader = shader;
	SageRendererInternal::Set_Default_Shader(shader);
}


void SageRenderer::DrawLine(SageLine const& line)
{
	SageRendererInternal::DrawLine(line);
}


void SageRenderer::DrawLine(ToastBox::Vec2 start, ToastBox::Vec2 end, ToastBox::Vec4 color)
{
	SageRendererInternal::DrawLine(start, end, color);


}

void SageRenderer::DrawRect(float x, float y, float width, float height, ToastBox::Vec4 color)
{
	SageRendererInternal::DrawRect(x, y, width, height, color);
}


void SageRenderer::DrawPoint(SagePoint const& point)
{
	SageRendererInternal::DrawPoint(point);
}

void SageRenderer::DrawPoint(ToastBox::Vec2 position, ToastBox::Vec4 color, float _s)
{
	SageRendererInternal::DrawPoint(position, color, _s);
}


void SageRenderer::SetColor(glm::vec4 color)
{
	default_config.color = color;
	SageRendererInternal::SetColor(color);
}




RENDER_CONFIG::RENDER_CONFIG(unsigned int options, float render_alpha, float border_width, glm::vec4 color, glm::vec4 border_color, float border_radius, SageShader* shader, glm::mat3 transformation_matrix, ToastBox::Matrix3x3 matrix, SageTexture* current_texture)
{
	this->options = options;
	this->render_alpha = render_alpha;
	this->border_width = border_width;
	this->color = color;
	this->border_color = border_color;
	this->border_radius = border_radius;
	this->shader = shader;
	this->transformation_matrix = transformation_matrix;
	this->matrix = matrix;
	this->current_texture = current_texture;
}

void SageRenderer::ClearColor(ToastBox::Vec4 clr)
{
	SageRendererInternal::ClearColor(clr);

}

