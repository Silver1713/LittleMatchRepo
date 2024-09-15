#include "SageObject.hpp"

#include <iostream>
#include <ostream>
#include <glm/ext/matrix_transform.hpp>

long int SageObject::object_count{};
long int SageObject::current_object_count{};
SageObject::SageObject() : object_id(0), object_name("default"), obj_mesh(), transform(), material()
{

}

void SageObject::init(char const * name, SageModel* model)
{
	//Name, model, vertex count
	object_name = name;
	obj_mesh.model_ref = model;
	obj_mesh.vtx_cnt = model->get_vertex_positions().size();
	obj_mesh.idx_cnt = model->get_vertex_indices().size();

	
	material.shader_ref = model->get_shader_program();

	

	

	object_id = object_count++;

	current_object_count++;
}


void SageObject::attach_texture(SageTexture* texture)
{
	if (texture == nullptr)
	{
		material.enable_texture = false;
		return;
	}

	material.texture_ref = texture;
}








void SageObject::update()
{
	transform.calculate_model_matrix();
	transform.orientation.x += static_cast<float>(transform.orientation.y * SageHelper::delta_time);

}



glm::mat3x3 SageObject::SageTransform2D::calculate_model_matrix()
{
	glm::mat3  translation = { 1, 0, 0, 0, 1, 0, position.x, position.y, 1 };
	glm::mat3  rotation = { cos(orientation.x), sin(orientation.x), 0, -sin(orientation.x), cos(orientation.x), 0, 0, 0, 1 };
	glm::mat3 scaling = { scale.x, 0, 0, 0, scale.y, 0, 0, 0, 1 };

	model_matrix = translation * rotation * scaling;

	return model_matrix;
}


// Draw with default shader
void SageObject::draw(SageViewport* vp)
{
	SageShader* shader = obj_mesh.model_ref->get_shader_program();
	SageViewport* viewport = vp;

	glBindVertexArray(obj_mesh.model_ref->get_vao_handle());
	
	shader->Activate();
	shader->SetUniform("uTransparency", material.mat_transparency);
	shader->SetUniform("uUseColor", !material.enable_vertex_color);
	shader->SetUniform("uUseBorderColor", material.enable_border_color);

	shader->SetUniform("uColor", material.color);
	shader->SetUniform("uBorderColor", material.border_color);

	shader->SetUniform("uBorderSize", material.border_width);
	shader->SetUniform("uCornerRadius", material.border_radius);
	shader->SetUniform("uObjectSize", transform.scale);
	shader->SetUniform("uModel_xform",  viewport->get_viewport_xform() * transform.model_matrix);
	shader->SetUniform("uUseTexture", material.enable_texture);
	if (material.enable_texture)
	{
		glActiveTexture(GL_TEXTURE0 + material.texture_ref->get_texture_unit());
		shader->SetUniform("uTex2D", material.texture_ref->get_texture_unit());
	}




	
	
	if (obj_mesh.model_ref->is_idx_enabled())
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawElements(GL_TRIANGLES, obj_mesh.idx_cnt, GL_UNSIGNED_SHORT, nullptr);
		// Check for errors

		
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, obj_mesh.vtx_cnt);
	}

	glBindVertexArray(0);
	shader->Deactivate();
	glDisable(GL_BLEND);
	
	
}


SageObject::SageMaterial& SageObject::GetMaterial()
{
	return material;
}

void SageObject::set_alpha(float transparency)
{
	material.mat_transparency = transparency;
}


