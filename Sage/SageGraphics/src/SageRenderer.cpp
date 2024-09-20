#include "SageRenderer.hpp"

#include "SageShaderManager.hpp"

SageViewport SageRenderer::viewport;
RENDER_CONFIG SageRenderer::default_config{ SageRenderer::SAGE_ENABLE_TEXTURE | SageRenderer::SAGE_ENABLE_ALPHA, 1.f,15.f,15.f ,{0,0,0,1},
nullptr, {}, {}, nullptr };
//SageCameraInternal2D* SageRenderer::camera;
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
