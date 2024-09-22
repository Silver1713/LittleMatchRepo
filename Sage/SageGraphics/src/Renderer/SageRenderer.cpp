#include "SageLine.hpp"
#include "SageModelManager.hpp"
#include "SageShaderManager.hpp"
#include "SageShader.hpp"
#include "SageTexture.h"
#include "SagePoint.hpp"
#include "SageRenderer.hpp"
#include "SageCamera.hpp"
#include "glm/gtc/type_ptr.inl"
class SageCameraInternal2D;
SageViewport SageRenderer::viewport;
RENDER_CONFIG SageRenderer::default_config{ SageRenderer::SAGE_ENABLE_TEXTURE | SageRenderer::SAGE_ENABLE_ALPHA};
SageCamera* SageRenderer::camera;
SageShader* SageRenderer::default_shader;
void SageRenderer::DrawFilled(SageObject& object, RENDER_CONFIG config)
{
	SageObject::SageMaterial& mat = object.GetMaterial();
	if (config.options & SAGE_ENABLE_BORDER)
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
		object.draw(camera);
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

void SageRenderer::SetCurrentView(SageCamera* view)
{
	camera = view;
}


void SageRenderer::DrawFilled(SageObject& object)
{
	SageObject::SageMaterial& mat = object.GetMaterial();
	if (default_config.options & SAGE_ENABLE_BORDER)
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
		object.draw(camera);
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

void SageRenderer::DrawFilled(SageModel& model)
{
	SageShader* shader = default_shader;


	glBindVertexArray(model.get_vao_handle());


	shader->Activate();
	shader->SetUniform("uAlpha", default_config.render_alpha);
	shader->SetUniform("uUseColor", static_cast<bool>(default_config.options & SAGE_ENABLE_VERTEX_COLOR));
	shader->SetUniform("uUseBorderColor", static_cast<bool>(default_config.options & SAGE_ENABLE_BORDER));

	ToastBox::Vector4 color = { default_config.border_color.r,default_config.border_color.g,default_config.border_color.b,default_config.border_color.a };
	shader->SetUniform("uBorderColor", color);

	shader->SetUniform("uBorderSize", default_config.border_width);
	shader->SetUniform("uCornerRadius", default_config.border_radius);
	//shader->SetUniform("uObjectSize", transform.scale.x, transform.scale.y);
	/*glm::mat3 d = viewport->get_viewport_xform() * transform.model_matrix;
	glm::mat3 m = glm::mat3(1.0f);*/

	shader->SetUniform("uModel_xform", default_config.matrix);
	//shader->SetUniform("uModel_xform",  viewport->get_viewport_xform() * transform.model_matrix
	bool use_texture = static_cast<bool>(default_config.options & SAGE_ENABLE_TEXTURE);
	shader->SetUniform("uUseTexture", use_texture);
	if (use_texture)
	{
		glActiveTexture(default_config.current_texture->get_texture_unit());
		shader->SetUniform("uTex2D", default_config.current_texture->get_texture_unit());
	}






	if (model.is_idx_enabled())
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//if (this->obj_mesh->model_ref->)

		glDrawElements(GL_TRIANGLES, model.get_vertex_indices().size(), GL_UNSIGNED_SHORT, nullptr);
		// Check for errors


	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, model.get_vertex_positions().size());
	}

	glBindVertexArray(0);
	shader->Deactivate();
	glDisable(GL_BLEND);

}

void SageRenderer::DrawFilled(SageModel& model, glm::mat3& matrix, RENDER_CONFIG config)
{

	SageShader* shader = default_shader;


	glBindVertexArray(model.get_vao_handle());


	shader->Activate();
	shader->SetUniform("uAlpha", config.render_alpha);
	shader->SetUniform("uUseColor", static_cast<bool>(config.options & SAGE_ENABLE_VERTEX_COLOR));
	shader->SetUniform("uUseBorderColor", static_cast<bool>(config.options & SAGE_ENABLE_BORDER));

	ToastBox::Vector4 color = { config.border_color.r,config.border_color.g,config.border_color.b,config.border_color.a };
	shader->SetUniform("uBorderColor", color);

	shader->SetUniform("uBorderSize", config.border_width);
	shader->SetUniform("uCornerRadius", config.border_radius);
	//shader->SetUniform("uObjectSize", transform.scale.x, transform.scale.y);
	/*glm::mat3 d = viewport->get_viewport_xform() * transform.model_matrix;
	glm::mat3 m = glm::mat3(1.0f);*/

	shader->SetUniform("uModel_xform", matrix);
	//shader->SetUniform("uModel_xform",  viewport->get_viewport_xform() * transform.model_matrix
	bool use_texture = static_cast<bool>(config.options & SAGE_ENABLE_TEXTURE);
	shader->SetUniform("uUseTexture", use_texture);
	if (use_texture)
	{
		glActiveTexture(config.current_texture->get_texture_unit());
		shader->SetUniform("uTex2D", config.current_texture->get_texture_unit());
	}






	if (model.is_idx_enabled())
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//if (this->obj_mesh->model_ref->)

		glDrawElements(GL_TRIANGLES, model.get_vertex_indices().size(), GL_UNSIGNED_SHORT, nullptr);
		// Check for errors


	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, model.get_vertex_positions().size());
	}

	glBindVertexArray(0);
	shader->Deactivate();
	glDisable(GL_BLEND);


}


void SageRenderer::init()
{
	default_config.options = 0;
	if (SageShaderManager::shaders.find("BASE_SHADER") != SageShaderManager::shaders.end())
	{
		default_shader = &SageShaderManager::shaders["BASE_SHADER"];
	}
	else
	{
		SageShaderManager::search_and_create_shader_program("BASE_SHADER", "BaseVertexShader", "BaseFragmentShader");
		default_shader = &SageShaderManager::shaders["BASE_SHADER"];

	}

	SetOptionOn(SAGE_ENABLE_ALPHA | SAGE_ENABLE_BORDER);

	default_config.border_radius = 15.f;
	default_config.border_width = 15.f;
	default_config.border_color = { 0,0,0,1 };
	default_config.render_alpha = 1.f;

	// Initialize Primitives

	SageModelManager::CreatePrimitiveModel("PRIMITIVE_RECT", PRIMITIVE_SQUARE, RENDER_TYPE::TYPE_TRIANGLE);
	SageModelManager::CreatePrimitiveModel("PRIMITIVE_CIRCLE", PRIMITIVE_CIRCLE, RENDER_TYPE::TYPE_TRIANGLE_FAN);
	SageModelManager::CreatePrimitiveModel("PRIMITIVE_LINE", PRIMITIVE_LINE, RENDER_TYPE::TYPE_LINES);
	SageModelManager::CreatePrimitiveModel("PRIMITIVE_POINT", PRIMITIVE_POINTS, RENDER_TYPE::TYPE_POINTS);

	// initialize VAO
	SageModelManager::models["PRIMITIVE_RECT"].setup_gpu_buffer();
	SageModelManager::models["PRIMITIVE_CIRCLE"].setup_gpu_buffer();
	SageModelManager::models["PRIMITIVE_LINE"].setup_gpu_buffer();
	SageModelManager::models["PRIMITIVE_POINT"].setup_gpu_buffer();

	SageModelManager::models["PRIMITIVE_RECT"].AssignShaderProgram(default_shader);
	SageModelManager::models["PRIMITIVE_CIRCLE"].AssignShaderProgram(default_shader);
	SageModelManager::models["PRIMITIVE_LINE"].AssignShaderProgram(default_shader);
	SageModelManager::models["PRIMITIVE_POINT"].AssignShaderProgram(default_shader);

	SageModelManager::models["PRIMITIVE_RECT"].set_render_type(RENDER_TYPE::TYPE_TRIANGLE);
	SageModelManager::models["PRIMITIVE_CIRCLE"].set_render_type(RENDER_TYPE::TYPE_TRIANGLE_FAN);
	SageModelManager::models["PRIMITIVE_LINE"].set_render_type(RENDER_TYPE::TYPE_LINES);
	SageModelManager::models["PRIMITIVE_POINT"].set_render_type(RENDER_TYPE::TYPE_POINTS);

	
}



void SageRenderer::SetAlpha(float alpha)
{
	default_config.render_alpha = alpha;
}

void SageRenderer::SetBorderColor(glm::vec4 color)
{
	default_config.border_color = color;
}

void SageRenderer::SetBorderRadius(float radius)
{
	default_config.border_radius = radius;
}

void SageRenderer::SetBorderWidth(float width)
{
	default_config.border_width = width;
}

void SageRenderer::SetTransformationMatrix(glm::mat3& matrix)
{
	default_config.transformation_matrix = matrix;
}

void SageRenderer::Set_Default_Shader(SageShader* shader)
{
	default_shader = shader;
}


void SageRenderer::DrawLine(SageLine const& line)
{
	SageShader* shader = default_shader;
	glBindVertexArray(line.line->get_vao_handle());
	shader->Activate();
	shader->SetUniform("uAlpha", default_config.render_alpha);
	shader->SetUniform("uUseColor", true);
	shader->SetUniform("uUseBorderColor", false);

	ToastBox::Vector4 color = { default_config.border_color.r,default_config.border_color.g,default_config.border_color.b,default_config.border_color.a };
	shader->SetUniform("uBorderColor", color);
	shader->SetUniform("uColor",ToastBox::Vec4{ line.color.x ,line.color.y,line.color.z, line.color.a});

	shader->SetUniform("uBorderSize", default_config.border_width);
	shader->SetUniform("uCornerRadius", default_config.border_radius);
	

	if (default_config.options & SAGE_ENABLE_CAMERA)
	{
		
		shader->SetUniform("uModel_xform", camera->get_projection_view_matrix());
	}
	else
	{
		//ToastBox::Matrix3x3 mtx = { glm::value_ptr(line.transformation_matrix) };
		ToastBox::Matrix3x3 vp_xf = { glm::value_ptr(viewport.get_viewport_xform()) };
		
		shader->SetUniform("uModel_xform", vp_xf);
	}
	
	bool use_texture = false;
	shader->SetUniform("uUseTexture", false);
	if (use_texture)
	{
		glActiveTexture(default_config.current_texture->get_texture_unit());
		shader->SetUniform("uTex2D", default_config.current_texture->get_texture_unit());
	}

	if (line.line->is_idx_enabled())
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//if (this->obj_mesh->model_ref->)

		glDrawElements(GL_LINES, line.line->get_vertex_indices().size(), GL_UNSIGNED_SHORT, nullptr);
		// Check for errors
	}
	else
	{
		glDrawArrays(GL_LINES, 0, line.line->get_vertex_positions().size());
	}

	glBindVertexArray(0);
	shader->Deactivate();
	glDisable(GL_BLEND);
}


void SageRenderer::DrawLine(ToastBox::Vec2 start, ToastBox::Vec2 end, ToastBox::Vec4 color)
{
	SageLine line({ start.getX(), start.getY()}, {end.getX(), end.getY()}, {color.x,color.y,color.z,color.a}, 15.f);
	line.line = &SageModelManager::models["PRIMITIVE_LINE"];

	line.update_dist(line.start,line.end);

	DrawLine(line);


}

void SageRenderer::DrawRect(float x, float y, float width, float height, ToastBox::Vec4 color)
{
	SageObject obj;
	obj.init("RECT", &SageModelManager::models["PRIMITIVE_RECT"]);
	obj.transform.position = { x,y };
	obj.transform.scale = { width,height };
	obj.GetMaterial().color = { color.x,color.y,color.z,color.a };
	obj.transform.calculate_model_matrix();
	DrawFilled(obj);
}


void SageRenderer::DrawPoint(SagePoint const& point)
{
	SageShader* shader = default_shader;
	SageModel* model = point.point;
	glBindVertexArray(model->get_vao_handle());
	shader->Activate();
	shader->SetUniform("uAlpha", default_config.render_alpha);
	shader->SetUniform("uUseColor", true);
	shader->SetUniform("uUseBorderColor", false);

	ToastBox::Vector4 color = { default_config.border_color.r,default_config.border_color.g,default_config.border_color.b,default_config.border_color.a };
	shader->SetUniform("uBorderColor", color);
	shader->SetUniform("uColor", ToastBox::Vec4{ point.color.x ,point.color.y,point.color.z, point.color.a });

	shader->SetUniform("uBorderSize", default_config.border_width);
	shader->SetUniform("uCornerRadius", default_config.border_radius);


	if (default_config.options & SAGE_ENABLE_CAMERA)
	{
		ToastBox::Matrix3x3 mtx = { glm::value_ptr(point.transformation_matrix) };
		shader->SetUniform("uModel_xform", camera->get_projection_view_matrix() * mtx);
	}
	else
	{
		ToastBox::Matrix3x3 mtx = { glm::value_ptr(point.transformation_matrix) };
		ToastBox::Matrix3x3 vp_xf = { glm::value_ptr(viewport.get_viewport_xform()) };
		ToastBox::Matrix3x3 m1, m2, m3;
		m1.Matrix3Transpose(mtx);
		m2.Matrix3Transpose(vp_xf);
		m3.Matrix3Transpose(m2 * m1);
		shader->SetUniform("uModel_xform", m3);
	}

	bool use_texture = false;
	shader->SetUniform("uUseTexture", false);
	if (use_texture)
	{
		glActiveTexture(default_config.current_texture->get_texture_unit());
		shader->SetUniform("uTex2D", default_config.current_texture->get_texture_unit());
	}

	glPointSize(point.size);

	if (point.point->is_idx_enabled())
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//if (this->obj_mesh->model_ref->)

		glDrawElements(GL_POINTS, model->get_vertex_indices().size(), GL_UNSIGNED_SHORT, nullptr);
		// Check for errors
	}
	else
	{
		glDrawArrays(GL_POINTS, 0, model->get_vertex_positions().size());
	}

	glBindVertexArray(0);
	shader->Deactivate();
	glDisable(GL_BLEND);
}

void SageRenderer::DrawPoint(ToastBox::Vec2 position, ToastBox::Vec4 color, float _s)
{
	SagePoint point({ position.getX(), position.getY() }, { color.x,color.y,color.z,color.a }, _s);
	point.point = &SageModelManager::models["PRIMITIVE_POINT"];
	point.calculate_transform();
	DrawPoint(point);
}


void SageRenderer::SetColor(glm::vec4 color)
{
	default_config.color = color;
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


