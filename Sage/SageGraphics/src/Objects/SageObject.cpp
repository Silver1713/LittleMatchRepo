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

void SageObject::Init(char const* _name, SageModel* _model)
{
	//Name, model, vertex count
	object_name = _name;
	obj_mesh.model_ref = _model;
	obj_mesh.vtx_cnt = _model->Get_Vertex_Positions().size();
	obj_mesh.idx_cnt = _model->Get_Vertex_Indices().size();


	material.shader_ref = _model->Get_Shader_Program();





	object_id = object_count++;

	current_object_count++;

	is_enabled = true;

	Set_Alpha(1.f);
}


void SageObject::Attach_Texture(SageTexture* _texture)
{
	if (_texture == nullptr)
	{
		material.enable_texture = false;
		return;
	}

	material.texture_ref = _texture;
}








void SageObject::Update()
{
	transform.Calculate_Model_Matrix();
	transform.orientation.x += static_cast<float>(transform.orientation.y * SageHelper::delta_time);

}



glm::mat3x3 SageObject::SageTransform2D::Calculate_Model_Matrix()
{
	glm::mat3  translation = { 1, 0, 0, 0, 1, 0, position.x, position.y, 1 };
	glm::mat3  rotation = { cos(orientation.x), sin(orientation.x), 0, -sin(orientation.x), cos(orientation.x), 0, 0, 0, 1 };
	glm::mat3 scaling = { scale.x, 0, 0, 0, scale.y, 0, 0, 0, 1 };

	model_matrix = translation * rotation * scaling;

	return model_matrix;
}


// Draw with default shader
void SageObject::Draw(SageViewport* vp)
{
	SageShader* shader = obj_mesh.model_ref->Get_Shader_Program();
	SageViewport* viewport = vp;

	glBindVertexArray(obj_mesh.model_ref->Get_VAO_Handle());


	shader->Activate();
	shader->Set_Uniform("uAlpha", material.mat_transparency);
	shader->Set_Uniform("uUseColor", !material.enable_vertex_color);
	shader->Set_Uniform("uUseBorderColor", material.enable_border_color);
	shader->Set_Uniform("uColor", material.color.r, material.color.g, material.color.b, material.color.a);
	ToastBox::Vector4 color = { material.border_color.r, material.border_color.g, material.border_color.b,material.border_color.a };
	shader->Set_Uniform("uBorderColor", color);

	shader->Set_Uniform("uBorderSize", material.border_width);
	shader->Set_Uniform("uCornerRadius", material.border_radius);
	shader->Set_Uniform("uObjectSize", transform.scale.x, transform.scale.y);
	glm::mat3 d = viewport->get_viewport_xform() * transform.model_matrix;
	glm::mat3 m = glm::mat3(1.0f);

	glm::vec2 result = d * glm::vec3(0, 0, 1);
	ToastBox::Matrix3x3 mtx = glm::value_ptr(viewport->get_viewport_xform() * transform.model_matrix);
	shader->Set_Uniform("uModel_xform", mtx);
	//shader->Set_Uniform("uModel_xform",  viewport->get_viewport_xform() * transform.model_matrix);
	shader->Set_Uniform("uUseTexture", material.enable_texture);
	if (material.enable_texture)
	{
		material.texture_ref->Bind_Texture();
		glActiveTexture(material.texture_ref->Get_Texture_Unit());
		shader->Set_Uniform("uTex2D", material.texture_ref->Get_Texture_Unit());
	}






	if (obj_mesh.model_ref->Is_Idx_Enabled())
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
void SageObject::Draw(SageCamera* _cam)
{

	SageShader* shader = obj_mesh.model_ref->Get_Shader_Program();
	SageCamera* c = _cam;

	glBindVertexArray(obj_mesh.model_ref->Get_VAO_Handle());


	shader->Activate();
	shader->Set_Uniform("uAlpha", material.mat_transparency);
	shader->Set_Uniform("uUseColor", !material.enable_vertex_color);
	shader->Set_Uniform("uUseBorderColor", material.enable_border_color);
	shader->Set_Uniform("uColor", material.color.r, material.color.g, material.color.b, material.color.a);
	ToastBox::Vector4 color = { material.border_color.r, material.border_color.g, material.border_color.b,material.border_color.a };
	shader->Set_Uniform("uBorderColor", color);

	shader->Set_Uniform("uBorderSize", material.border_width);
	shader->Set_Uniform("uCornerRadius", material.border_radius);
	shader->Set_Uniform("uObjectSize", transform.scale.x, transform.scale.y);
	ToastBox::Matrix3x3 mtx = glm::value_ptr( transform.model_matrix);
	
	//glm::mat3 ca = static_cast<SageCameraInternal2D*>(c->Get_Camera())->Get_View_Projection_Matrix() * transform.model_matrix;
	ToastBox::Matrix3x3 m1, m2, m3;
	
	m3.Matrix3Transpose(~c->Get_Projection_View_Matrix() * ~mtx);
	glm::vec3 r2 = transform.model_matrix * glm::vec3(1, 1, 1);
	shader->Set_Uniform("uModel_xform", m3);
	shader->Set_Uniform("uUseTexture", material.enable_texture);
	if (material.enable_texture)
	{
		
		material.texture_ref->Bind_Texture();
		
		shader->Set_Uniform("uTex2D", material.texture_ref->Get_Texture_Unit());
	}






	if (obj_mesh.model_ref->Is_Idx_Enabled())
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

void SageObject::Set_Alpha(float _transparency)
{
	material.mat_transparency = _transparency;
}


void SageObject::Disable_Object()
{
	is_enabled = false;
}



