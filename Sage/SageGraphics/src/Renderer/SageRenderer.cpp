#include "SageRendererInternal.hpp"
#include "SageRenderer.hpp"


class SageCameraInternal2D;
SageViewport SageRenderer::viewport;
RENDER_CONFIG SageRenderer::default_config{ SageRenderer::SAGE_ENABLE_TEXTURE | SageRenderer::SAGE_ENABLE_ALPHA};
SageCamera* SageRenderer::camera;
SageShader* SageRenderer::default_shader;
void SageRenderer::Draw_Filled(SageObject& object, RENDER_CONFIG config)
{
	SageRendererInternal::Draw_Filled(object, {
		config.options, config.render_alpha, config.border_width,
		{config.color.r,config.color.g,config.color.b,config.color.a},
		{config.border_color.r,config.border_color.g,config.border_color.b,config.border_color.a},
		config.border_radius, config.shader,
		config.transformation_matrix,
		config.matrix,
		config.current_texture

	});

}

void SageRenderer::Set_Current_View(SageViewport& view)
{
	viewport = view;
	SageRendererInternal::Set_Current_View(view);
}

void SageRenderer::Set_Current_View(SageCamera* view)
{
	camera = view;
	SageRendererInternal::Set_Current_View(view);
}


void SageRenderer::Draw_Filled(SageObject& object)
{
	SageRendererInternal::Draw_Filled(object);
}





void SageRenderer::Set_Option_On(int options)
{
	SageRenderer::default_config.options |= options;
	SageRendererInternal::default_config.options |= options;
}

void SageRenderer::Set_Option_Off(int options)
{
	default_config.options &= ~options;
	SageRendererInternal::default_config.options &= ~options;
}

void SageRenderer::Draw_Filled(SageModel& model)
{
	SageRendererInternal::Draw_Filled(model);
}

void SageRenderer::Draw_Filled(SageModel& model, glm::mat3& matrix, RENDER_CONFIG config)
{

	SageRendererInternal::Draw_Filled(model, matrix, {
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



void SageRenderer::Set_Alpha(float alpha)
{
	default_config.render_alpha = alpha;
	SageRendererInternal::Set_Alpha(alpha);
}

void SageRenderer::Set_Border_Color(glm::vec4 color)
{
	default_config.border_color = color;
	SageRendererInternal::Set_Border_Color(color);
}

void SageRenderer::Set_Border_Radius(float radius)
{
	default_config.border_radius = radius;
	SageRendererInternal::Set_Border_Radius(radius);
}

void SageRenderer::Set_Border_Width(float width)
{
	default_config.border_width = width;
	SageRendererInternal::Set_Border_Width(width);
}

void SageRenderer::Set_Transformation_Matrix(glm::mat3& matrix)
{
	default_config.transformation_matrix = matrix;
	SageRendererInternal::Set_Transformation_Matrix(matrix);
}

void SageRenderer::Set_Default_Shader(SageShader* shader)
{
	default_shader = shader;
	SageRendererInternal::Set_Default_Shader(shader);
}


void SageRenderer::Draw_Line(SageLine const& line)
{
	SageRendererInternal::Draw_Line(line);
}


void SageRenderer::Draw_Line(ToastBox::Vec2 start, ToastBox::Vec2 end, ToastBox::Vec4 color, float size)
{
	SageRendererInternal::Draw_Line(start, end, color, size);


}

void SageRenderer::Draw_Rect(float x, float y, float width, float height, ToastBox::Vec4 color)
{
	SageRendererInternal::Draw_Rect(x, y, width, height, color);
}


void SageRenderer::Draw_Point(SagePoint const& point)
{
	SageRendererInternal::Draw_Point(point);
}

void SageRenderer::Draw_Point(ToastBox::Vec2 position, ToastBox::Vec4 color, float _s)
{
	SageRendererInternal::Draw_Point(position, color, _s);
}


void SageRenderer::Set_Color(glm::vec4 color)
{
	default_config.color = color;
	SageRendererInternal::Set_Color(color);
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

void SageRenderer::Clear_Color(ToastBox::Vec4 clr)
{
	SageRendererInternal::Clear_Color(clr);

}

