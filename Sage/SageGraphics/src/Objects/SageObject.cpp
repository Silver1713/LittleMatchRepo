#include "Vector4.h"
#include "SageObject.hpp"

#include <iostream>
#include <ostream>
#include <glm/ext/matrix_transform.hpp>

#include "SageCamera.hpp"
#include "SageCameraInternal.hpp"
#include "SageHelper.hpp"
#include "glm/gtc/type_ptr.inl"


long int SageObject::object_count{};
long int SageObject::current_object_count{};
SageObject::SageObject() : object_id(0), object_name("default"), obj_mesh(), transform(), material()
{

}

void SageObject::init(char const* name, SageModel* model)
{
	//Name, model, vertex count
	object_name = name;
	obj_mesh.model_ref = model;
	obj_mesh.vtx_cnt = model->get_vertex_positions().size();
	obj_mesh.idx_cnt = model->get_vertex_indices().size();


	material.shader_ref = model->get_shader_program();





	object_id = object_count++;

	current_object_count++;

	is_enabled = true;

	set_alpha(1.f);
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
	shader->SetUniform("uAlpha", material.mat_transparency);
	shader->SetUniform("uUseColor", !material.enable_vertex_color);
	shader->SetUniform("uUseBorderColor", material.enable_border_color);
	shader->SetUniform("uColor", material.color.r, material.color.g, material.color.b, material.color.a);
	ToastBox::Vector4 color = { material.border_color.r, material.border_color.g, material.border_color.b,material.border_color.a };
	shader->SetUniform("uBorderColor", color);

	shader->SetUniform("uBorderSize", material.border_width);
	shader->SetUniform("uCornerRadius", material.border_radius);
	shader->SetUniform("uObjectSize", transform.scale.x, transform.scale.y);
	glm::mat3 d = viewport->get_viewport_xform() * transform.model_matrix;
	glm::mat3 m = glm::mat3(1.0f);

	glm::vec2 result = d * glm::vec3(0, 0, 1);
	ToastBox::Matrix3x3 mtx = glm::value_ptr(viewport->get_viewport_xform() * transform.model_matrix);
	shader->SetUniform("uModel_xform", mtx);
	//shader->SetUniform("uModel_xform",  viewport->get_viewport_xform() * transform.model_matrix);
	shader->SetUniform("uUseTexture", material.enable_texture);
	if (material.enable_texture)
	{
		material.texture_ref->bind_texture();
		glActiveTexture(material.texture_ref->get_texture_unit());
		shader->SetUniform("uTex2D", material.texture_ref->get_texture_unit());
	}






	if (obj_mesh.model_ref->is_idx_enabled())
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//if (this->obj_mesh->model_ref->)
		glDrawElements(GL_TRIANGLE_FAN, static_cast<GLsizei>(obj_mesh.idx_cnt), GL_UNSIGNED_SHORT, nullptr);
		// Check for errors
		


	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(obj_mesh.vtx_cnt));
	}

	glBindVertexArray(0);
	shader->Deactivate();
	glDisable(GL_BLEND);


}

//Draw with default shader
void SageObject::draw(SageCamera* cam)
{

	SageShader* shader = obj_mesh.model_ref->get_shader_program();
	SageCamera* c = cam;

	glBindVertexArray(obj_mesh.model_ref->get_vao_handle());


	shader->Activate();
	shader->SetUniform("uAlpha", material.mat_transparency);
	shader->SetUniform("uUseColor", !material.enable_vertex_color);
	shader->SetUniform("uUseBorderColor", material.enable_border_color);
	shader->SetUniform("uColor", material.color.r, material.color.g, material.color.b, material.color.a);
	ToastBox::Vector4 color = { material.border_color.r, material.border_color.g, material.border_color.b,material.border_color.a };
	shader->SetUniform("uBorderColor", color);

	shader->SetUniform("uBorderSize", material.border_width);
	shader->SetUniform("uCornerRadius", material.border_radius);
	shader->SetUniform("uObjectSize", transform.scale.x, transform.scale.y);
	ToastBox::Matrix3x3 mtx = glm::value_ptr( transform.model_matrix);
	
	//glm::mat3 ca = static_cast<SageCameraInternal2D*>(c->GetCamera())->GetViewProjectionMatrix() * transform.model_matrix;
	ToastBox::Matrix3x3 m1, m2, m3;
	
	m3.Matrix3Transpose(~c->get_projection_view_matrix() * ~mtx);
	glm::vec3 r2 = transform.model_matrix * glm::vec3(1, 1, 1);
	shader->SetUniform("uModel_xform", m3);
	shader->SetUniform("uUseTexture", material.enable_texture);
	if (material.enable_texture)
	{
		
		material.texture_ref->bind_texture();
		
		shader->SetUniform("uTex2D", material.texture_ref->get_texture_unit());
	}






	if (obj_mesh.model_ref->is_idx_enabled())
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//if (this->obj_mesh->model_ref->)
		glDrawElements(GL_TRIANGLE_FAN, static_cast<GLsizei>(obj_mesh.idx_cnt), GL_UNSIGNED_SHORT, nullptr);
		// Check for errors


	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(obj_mesh.vtx_cnt));
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


void SageObject::disable_object()
{
	is_enabled = false;
}



