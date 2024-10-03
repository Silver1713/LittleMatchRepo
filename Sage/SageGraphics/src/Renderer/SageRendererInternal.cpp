#include "SageLine.hpp"
#include "SageModelManager.hpp"
#include "SageShaderManager.hpp"
#include "SageShader.hpp"
#include "SageTexture.h"
#include "SagePoint.hpp"
#include "SageRendererInternal.hpp"
#include "SageCamera.hpp"
#include "glm/gtc/type_ptr.inl"



class SageCameraInternal2D;
SageViewport SageRendererInternal::viewport;
RENDER_CONFIG_INTERNAL SageRendererInternal::default_config{ SageRendererInternal::I_SAGE_ENABLE_TEXTURE | SageRendererInternal::I_SAGE_ENABLE_ALPHA };
SageCamera* SageRendererInternal::camera;
SageShader* SageRendererInternal::default_shader;
void SageRendererInternal::Draw_Filled(SageObject& object, RENDER_CONFIG_INTERNAL config)
{
	SageObject::SageMaterial& mat = object.GetMaterial();
	if (config.options & I_SAGE_ENABLE_BORDER)
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

	if (config.options & I_SAGE_ENABLE_VERTEX_COLOR)
	{
		mat.enable_vertex_color = true;
	}
	else
	{
		mat.enable_vertex_color = false;

	}
	if (config.options & I_SAGE_ENABLE_CAMERA)
	{
		object.Draw(camera);
	}
	else
	{
		object.Draw(&viewport);
	}
	//object.draw(&viewport);
}

void SageRendererInternal::Set_Current_View(SageViewport& view)
{
	viewport = view;
}

void SageRendererInternal::Set_Current_View(SageCamera* view)
{
	camera = view;
}


void SageRendererInternal::Draw_Filled(SageObject& object)
{
	SageObject::SageMaterial& mat = object.GetMaterial();
	if (default_config.options & I_SAGE_ENABLE_BORDER)
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

	if (default_config.options & I_SAGE_ENABLE_VERTEX_COLOR)
	{
		mat.enable_vertex_color = true;
	}
	else
	{
		mat.enable_vertex_color = false;

	}
	if (default_config.options & I_SAGE_ENABLE_CAMERA)
	{
		object.Draw(camera);
	}
	else
	{
		object.Draw(&viewport);
	}
	//object.draw(&viewport);
}





void SageRendererInternal::Set_Option_On(int options)
{
	default_config.options |= options;
}

void SageRendererInternal::Set_Option_Off(int options)
{
	default_config.options &= ~options;
}

void SageRendererInternal::Draw_Filled(SageModel& model)
{
	SageShader* shader = default_shader;


	glBindVertexArray(model.Get_VAO_Handle());


	shader->Activate();
	shader->Set_Uniform("uAlpha", default_config.render_alpha);
	shader->Set_Uniform("uUseColor", static_cast<bool>(default_config.options & I_SAGE_ENABLE_VERTEX_COLOR));
	shader->Set_Uniform("uUseBorderColor", static_cast<bool>(default_config.options & I_SAGE_ENABLE_BORDER));

	ToastBox::Vector4 color = { default_config.border_color.r,default_config.border_color.g,default_config.border_color.b,default_config.border_color.a };
	shader->Set_Uniform("uBorderColor", color);

	shader->Set_Uniform("uBorderSize", default_config.border_width);
	shader->Set_Uniform("uCornerRadius", default_config.border_radius);
	//shader->Set_Uniform("uObjectSize", transform.scale.x, transform.scale.y);
	/*glm::mat3 d = viewport->get_viewport_xform() * transform.model_matrix;
	glm::mat3 m = glm::mat3(1.0f);*/

	shader->Set_Uniform("uModel_xform", default_config.matrix);
	//shader->Set_Uniform("uModel_xform",  viewport->get_viewport_xform() * transform.model_matrix
	bool use_texture = static_cast<bool>(default_config.options & I_SAGE_ENABLE_TEXTURE);
	shader->Set_Uniform("uUseTexture", use_texture);
	if (use_texture)
	{
		glActiveTexture(default_config.current_texture->Get_Texture_Unit());
		shader->Set_Uniform("uTex2D", default_config.current_texture->Get_Texture_Unit());
	}






	if (model.Is_Idx_Enabled())
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//if (this->obj_mesh->model_ref->)

		glDrawElements(GL_TRIANGLES, static_cast<int>(model.Get_Vertex_Indices().size()), GL_UNSIGNED_SHORT, nullptr);
		// Check for errors


	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(model.Get_Vertex_Positions().size()));
	}

	glBindVertexArray(0);
	shader->Deactivate();
	glDisable(GL_BLEND);

}

void SageRendererInternal::Draw_Filled(SageModel& model, glm::mat3& matrix, RENDER_CONFIG_INTERNAL config)
{

	SageShader* shader = default_shader;


	glBindVertexArray(model.Get_VAO_Handle());


	shader->Activate();
	shader->Set_Uniform("uAlpha", config.render_alpha);
	shader->Set_Uniform("uUseColor", static_cast<bool>(config.options & I_SAGE_ENABLE_VERTEX_COLOR));
	shader->Set_Uniform("uUseBorderColor", static_cast<bool>(config.options & I_SAGE_ENABLE_BORDER));

	ToastBox::Vector4 color = { config.border_color.r,config.border_color.g,config.border_color.b,config.border_color.a };
	shader->Set_Uniform("uBorderColor", color);

	shader->Set_Uniform("uBorderSize", config.border_width);
	shader->Set_Uniform("uCornerRadius", config.border_radius);
	//shader->Set_Uniform("uObjectSize", transform.scale.x, transform.scale.y);
	/*glm::mat3 d = viewport->get_viewport_xform() * transform.model_matrix;
	glm::mat3 m = glm::mat3(1.0f);*/

	shader->Set_Uniform("uModel_xform", matrix);
	//shader->Set_Uniform("uModel_xform",  viewport->get_viewport_xform() * transform.model_matrix
	bool use_texture = static_cast<bool>(config.options & I_SAGE_ENABLE_TEXTURE);
	shader->Set_Uniform("uUseTexture", use_texture);
	if (use_texture)
	{
		glActiveTexture(config.current_texture->Get_Texture_Unit());
		shader->Set_Uniform("uTex2D", config.current_texture->Get_Texture_Unit());
	}






	if (model.Is_Idx_Enabled())
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//if (this->obj_mesh->model_ref->)

		glDrawElements(GL_TRIANGLES, static_cast<int>(model.Get_Vertex_Indices().size()), GL_UNSIGNED_SHORT, nullptr);
		// Check for errors


	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(model.Get_Vertex_Positions().size()));
	}

	glBindVertexArray(0);
	shader->Deactivate();
	glDisable(GL_BLEND);


}


void SageRendererInternal::Init()
{
	default_config.options = 0;
	if (SageShaderManager::shaders.find("BASE_SHADER") != SageShaderManager::shaders.end())
	{
		default_shader = &SageShaderManager::shaders["BASE_SHADER"];
	}
	else
	{
		SageShaderManager::Search_And_Create_Shader_Program("BASE_SHADER", "BaseVertexShader", "BaseFragmentShader");
		default_shader = &SageShaderManager::shaders["BASE_SHADER"];

	}

	Set_Option_On(I_SAGE_ENABLE_ALPHA | I_SAGE_ENABLE_BORDER);

	default_config.border_radius = 15.f;
	default_config.border_width = 15.f;
	default_config.border_color = { 0,0,0,1 };
	default_config.render_alpha = 1.f;

	// Initialize Primitives

	SageModelManager::CreatePrimitiveModel("PRIMITIVE_RECT", static_cast<int>(PrimitiveShape::PRIMITIVE_SQUARE), RENDER_TYPE::TYPE_TRIANGLE);
	SageModelManager::CreatePrimitiveModel("PRIMITIVE_CIRCLE", static_cast<int>(PrimitiveShape::PRIMITIVE_CIRCLE), RENDER_TYPE::TYPE_TRIANGLE_FAN);
	SageModelManager::CreatePrimitiveModel("PRIMITIVE_LINE", static_cast<int>(PrimitiveShape::PRIMITIVE_LINE), RENDER_TYPE::TYPE_LINES);
	SageModelManager::CreatePrimitiveModel("PRIMITIVE_POINT", static_cast<int>(PrimitiveShape::PRIMITIVE_POINTS), RENDER_TYPE::TYPE_POINTS);

	// initialize VAO
	SageModelManager::models["PRIMITIVE_RECT"].setup_gpu_buffer();
	SageModelManager::models["PRIMITIVE_CIRCLE"].setup_gpu_buffer();
	SageModelManager::models["PRIMITIVE_LINE"].setup_gpu_buffer();
	SageModelManager::models["PRIMITIVE_POINT"].setup_gpu_buffer();

	SageModelManager::models["PRIMITIVE_RECT"].AssignShaderProgram(default_shader);
	SageModelManager::models["PRIMITIVE_CIRCLE"].AssignShaderProgram(default_shader);
	SageModelManager::models["PRIMITIVE_LINE"].AssignShaderProgram(default_shader);
	SageModelManager::models["PRIMITIVE_POINT"].AssignShaderProgram(default_shader);

	SageModelManager::models["PRIMITIVE_RECT"].Set_Render_Type(RENDER_TYPE::TYPE_TRIANGLE);
	SageModelManager::models["PRIMITIVE_CIRCLE"].Set_Render_Type(RENDER_TYPE::TYPE_TRIANGLE_FAN);
	SageModelManager::models["PRIMITIVE_LINE"].Set_Render_Type(RENDER_TYPE::TYPE_LINES);
	SageModelManager::models["PRIMITIVE_POINT"].Set_Render_Type(RENDER_TYPE::TYPE_POINTS);


}



void SageRendererInternal::Set_Alpha(float alpha)
{
	default_config.render_alpha = alpha;
}

void SageRendererInternal::Set_Border_Color(glm::vec4 color)
{
	default_config.border_color = color;
}

void SageRendererInternal::Set_Border_Radius(float radius)
{
	default_config.border_radius = radius;
}

void SageRendererInternal::Set_Border_Width(float width)
{
	default_config.border_width = width;
}

void SageRendererInternal::Set_Transformation_Matrix(glm::mat3& matrix)
{
	default_config.transformation_matrix = matrix;
}

void SageRendererInternal::Set_Default_Shader(SageShader* _shader)
{
	default_shader = _shader;
}


void SageRendererInternal::Draw_Line(SageLine const& line, float size)
{
	SageShader* shader = default_shader;
	glBindVertexArray(line.line->Get_VAO_Handle());
	shader->Activate();
	shader->Set_Uniform("uAlpha", default_config.render_alpha);
	shader->Set_Uniform("uUseColor", true);
	shader->Set_Uniform("uUseBorderColor", false);

	ToastBox::Vector4 color = { default_config.border_color.r,default_config.border_color.g,default_config.border_color.b,default_config.border_color.a };
	shader->Set_Uniform("uBorderColor", color);
	shader->Set_Uniform("uColor", ToastBox::Vec4{ line.color.x ,line.color.y,line.color.z, line.color.a });

	shader->Set_Uniform("uBorderSize", default_config.border_width);
	shader->Set_Uniform("uCornerRadius", default_config.border_radius);

	glLineWidth(size);




	if (default_config.options & I_SAGE_ENABLE_CAMERA)
	{

		shader->Set_Uniform("uModel_xform", camera->Get_Projection_View_Matrix());
	}
	else
	{
		//ToastBox::Matrix3x3 mtx = { glm::value_ptr(line.transformation_matrix) };
		ToastBox::Matrix3x3 vp_xf = { glm::value_ptr(viewport.get_viewport_xform()) };

		shader->Set_Uniform("uModel_xform", vp_xf);
	}

	bool use_texture = false;
	shader->Set_Uniform("uUseTexture", false);
	if (use_texture)
	{
		glActiveTexture(default_config.current_texture->Get_Texture_Unit());
		shader->Set_Uniform("uTex2D", default_config.current_texture->Get_Texture_Unit());
	}

	if (line.line->Is_Idx_Enabled())
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//if (this->obj_mesh->model_ref->)

		glDrawElements(GL_LINES, static_cast<int>(line.line->Get_Vertex_Indices().size()), GL_UNSIGNED_SHORT, nullptr);
		// Check for errors
	}
	else
	{
		glDrawArrays(GL_LINES, 0, static_cast<int>(line.line->Get_Vertex_Positions().size()));
	}

	glBindVertexArray(0);
	shader->Deactivate();
	glDisable(GL_BLEND);
}


void SageRendererInternal::Draw_Line(ToastBox::Vec2 start, ToastBox::Vec2 end, ToastBox::Vec4 color, float size)
{
	SageLine line({ start.getX(), start.getY() }, { end.getX(), end.getY() }, { color.x,color.y,color.z,color.a }, size);
	line.line = &SageModelManager::models["PRIMITIVE_LINE"];

	line.Update_Dist(line.start, line.end);

	Draw_Line(line, line.width);


}

void SageRendererInternal::Draw_Rect(float x, float y, float width, float height, ToastBox::Vec4 color)
{
	SageObject obj;
	obj.Init("RECT", &SageModelManager::models["PRIMITIVE_RECT"]);
	obj.transform.position = { x,y };
	obj.transform.scale = { width,height };
	obj.GetMaterial().color = { color.x,color.y,color.z,color.a };
	obj.transform.Calculate_Model_Matrix();
	Draw_Filled(obj);
}


void SageRendererInternal::Draw_Point(SagePoint const& point)
{
	SageShader* shader = default_shader;
	SageModel* model = point.point;
	glBindVertexArray(model->Get_VAO_Handle());
	shader->Activate();
	shader->Set_Uniform("uAlpha", default_config.render_alpha);
	shader->Set_Uniform("uUseColor", true);
	shader->Set_Uniform("uUseBorderColor", false);

	ToastBox::Vector4 color = { default_config.border_color.r,default_config.border_color.g,default_config.border_color.b,default_config.border_color.a };
	shader->Set_Uniform("uBorderColor", color);
	shader->Set_Uniform("uColor", ToastBox::Vec4{ point.color.x ,point.color.y,point.color.z, point.color.a });

	shader->Set_Uniform("uBorderSize", default_config.border_width);
	shader->Set_Uniform("uCornerRadius", default_config.border_radius);


	if (default_config.options & I_SAGE_ENABLE_CAMERA)
	{
		ToastBox::Matrix3x3 mtx = { glm::value_ptr(point.transformation_matrix) };

		ToastBox::Matrix3x3 m3;

		m3.Matrix3Transpose(~camera->Get_Projection_View_Matrix() * ~mtx);
		shader->Set_Uniform("uModel_xform", m3);
	}
	else
	{
		ToastBox::Matrix3x3 mtx = { glm::value_ptr(point.transformation_matrix) };
		ToastBox::Matrix3x3 vp_xf = { glm::value_ptr(viewport.get_viewport_xform()) };
		ToastBox::Matrix3x3 m1, m2, m3;
		m1.Matrix3Transpose(mtx);
		m2.Matrix3Transpose(vp_xf);
		m3.Matrix3Transpose(m2 * m1);
		shader->Set_Uniform("uModel_xform", m3);
	}

	bool use_texture = false;
	shader->Set_Uniform("uUseTexture", false);
	if (use_texture)
	{
		glActiveTexture(default_config.current_texture->Get_Texture_Unit());
		shader->Set_Uniform("uTex2D", default_config.current_texture->Get_Texture_Unit());
	}

	glPointSize(point.size);

	if (point.point->Is_Idx_Enabled())
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//if (this->obj_mesh->model_ref->)

		glDrawElements(GL_POINTS, static_cast<int>(model->Get_Vertex_Indices().size()), GL_UNSIGNED_SHORT, nullptr);
		// Check for errors
	}
	else
	{
		glDrawArrays(GL_POINTS, 0, static_cast<int>(model->Get_Vertex_Positions().size()));
	}

	glBindVertexArray(0);
	shader->Deactivate();
	glDisable(GL_BLEND);
}

void SageRendererInternal::Draw_Point(ToastBox::Vec2 position, ToastBox::Vec4 color, float _s)
{
	SagePoint point({ position.getX(), position.getY() }, { color.x,color.y,color.z,color.a }, _s);
	point.point = &SageModelManager::models["PRIMITIVE_POINT"];
	point.calculate_transform();
	Draw_Point(point);
}


void SageRendererInternal::Set_Color(glm::vec4 color)
{
	default_config.color = color;
}




RENDER_CONFIG_INTERNAL::RENDER_CONFIG_INTERNAL(unsigned int options, float render_alpha, float border_width, glm::vec4 color, glm::vec4 border_color, float border_radius, SageShader* shader, glm::mat3 transformation_matrix, ToastBox::Matrix3x3 matrix, SageTexture* current_texture)
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

void SageRendererInternal::Clear_Color(ToastBox::Vec4 clr)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(clr.x, clr.y, clr.z, clr.a);

}

