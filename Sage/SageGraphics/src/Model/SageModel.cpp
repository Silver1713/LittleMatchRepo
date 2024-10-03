#include "SageModel.hpp"

#include <iostream>

#include "SageModelManager.hpp"

int SageModel::model_count{};

SageModel::SageModel(const char* name, std::vector<glm::vec2>* pos, std::vector<glm::vec2>* texture, std::vector<glm::vec4>* clr, std::vector<GLushort>* idx)
	: model_id(model_count++), model_name(name), vao_hdl(0), vbo_hdl(0),
	ebo_hdl(0), tex_hdl(0), base_shader_ptr(nullptr), is_enabled(false), enable_vertex_color(false), enable_vertex_texture(false), enable_vertex_indices(false),
	shape_type(), mdl_render_type()
{
	
	if (!pos)
	{
		std::cerr << "Error: Vertex position data is required for model creation." << '\n';
		std::exit(EXIT_FAILURE);
	}
	pos_vtx = std::vector{ *pos };
	if (texture != nullptr)
	{
		tex_coords = std::vector{ *texture };
		enable_vertex_texture = true;
	}
	if (clr != nullptr)
	{
		clr_vtx = std::vector{ *clr };
		enable_vertex_color = true;
	}
	if (idx != nullptr)
	{
		idx_vtx = std::vector{ *idx };
		enable_vertex_indices = true;
	}

}


void SageModel::setup_gpu_buffer()
{
	// Create VAO VBO and load data
	glCreateBuffers(1, &vbo_hdl);

	// Check flags
	size_t vbo_size = (enable_vertex_color) ? (sizeof(glm::vec2) * pos_vtx.size() + sizeof(glm::vec4) * clr_vtx.size()) : (sizeof(glm::vec2) * pos_vtx.size());

	if (enable_vertex_texture)
		vbo_size += sizeof(glm::vec2) * tex_coords.size();

	if (shape_type == PrimitiveShape::PRIMITIVE_LINE || shape_type == PrimitiveShape::PRIMITIVE_POINTS)
	{
		glNamedBufferData(vbo_hdl, static_cast<GLsizeiptr>(vbo_size), nullptr, GL_DYNAMIC_DRAW);
	}
	else
	{
		glNamedBufferStorage(vbo_hdl, static_cast<GLsizeiptr>(vbo_size), nullptr, GL_DYNAMIC_STORAGE_BIT);
	}

	glNamedBufferSubData(vbo_hdl, 0, static_cast<GLsizeiptr>(sizeof(glm::vec2)) * static_cast<GLsizeiptr>(pos_vtx.size()), pos_vtx.data());

	if (enable_vertex_texture)
		glNamedBufferSubData(vbo_hdl, static_cast<GLsizeiptr>(sizeof(glm::vec2)) * static_cast<GLsizeiptr>(pos_vtx.size()), static_cast<GLsizeiptr>(sizeof(glm::vec2)) * static_cast<GLsizeiptr>(tex_coords.size()), tex_coords.data());

	if (enable_vertex_color)
		glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size() + ((enable_vertex_texture) ? (sizeof glm::vec2 * tex_coords.size()) : 0) , sizeof(glm::vec4) * clr_vtx.size(), clr_vtx.data());

	glCreateVertexArrays(1, &vao_hdl);
	// Position
	glEnableVertexArrayAttrib(vao_hdl, 0); // vtx_position at location 0
	glVertexArrayVertexBuffer(vao_hdl, 0, vbo_hdl, 0, sizeof(glm::vec2));
	glVertexArrayAttribFormat(vao_hdl, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao_hdl, 0, 0);

	if (enable_vertex_texture)
	{
		glEnableVertexArrayAttrib(vao_hdl, 1); // vtx_texture at location 2
		glVertexArrayVertexBuffer(vao_hdl, 1, vbo_hdl, static_cast<GLsizeiptr>(sizeof(glm::vec2) * pos_vtx.size()), sizeof(glm::vec2)); // data location in VBO
		glVertexArrayAttribFormat(vao_hdl, 1, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao_hdl, 1, 1);

	}

	if (enable_vertex_color)
	{
		glEnableVertexArrayAttrib(vao_hdl, 2); // vtx_color at location 1
		glVertexArrayVertexBuffer(vao_hdl, 2, vbo_hdl, sizeof(glm::vec2) * pos_vtx.size() + ((enable_vertex_texture) ? (sizeof glm::vec2 * tex_coords.size()) : 0), sizeof(glm::vec4)); // data location in VBO
		glVertexArrayAttribFormat(vao_hdl, 2, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao_hdl, 2, 2);
	}

	if (enable_vertex_indices)
	{
		glCreateBuffers(1, &ebo_hdl);
		glNamedBufferStorage(ebo_hdl, static_cast<GLsizeiptr>(sizeof(GLushort) * idx_vtx.size()), idx_vtx.data(), GL_DYNAMIC_STORAGE_BIT);
		glVertexArrayElementBuffer(vao_hdl, ebo_hdl);
	}
	else ebo_hdl = 0;

	glBindVertexArray(0);
	is_enabled = true;
}


SageModel::~SageModel()
{
	model_count--;
	if (is_enabled)
	{
		glDeleteBuffers(1, &vbo_hdl);
		if (enable_vertex_indices)
			glDeleteBuffers(1, &ebo_hdl);
		glDeleteVertexArrays(1, &vao_hdl);
	}
}


// Assign Shader Program to the model
void SageModel::AssignShaderProgram(SageShader* shader)
{
	base_shader_ptr = shader;
}

// Getters
GLuint& SageModel::Get_EBO_Handle()
{
	return ebo_hdl;
}

GLuint SageModel::Get_EBO_Handle() const
{
	return ebo_hdl;
}

GLuint& SageModel::Get_Texture_Handle()
{
	return tex_hdl;
}

GLuint SageModel::Get_Texture_Handle() const
{
	return tex_hdl;
}
GLuint& SageModel::Get_VAO_Handle()
{
	return vao_hdl;

}

GLuint SageModel::Get_VAO_Handle() const
{
	return vao_hdl;
}

GLuint& SageModel::Get_VBO_Handle()
{
	return vbo_hdl;
}

GLuint SageModel::Get_VBO_Handle() const
{
	return vbo_hdl;
}

int SageModel::get_shape_type()
{
	return static_cast<int>(shape_type);
}




void SageModel::Set_Render_Type(int type)
{
	mdl_render_type = static_cast<RENDER_TYPE>(type);

}

void SageModel::Set_Shape_Type(int shape)
{
	shape_type = static_cast<PrimitiveShape>(shape);

}


void SageModel::Set_Render_Type(RENDER_TYPE type)
{
	mdl_render_type = type;
}

void SageModel::Set_Shape_Type(PrimitiveShape shape)
{
	shape_type = shape;
}


std::vector<glm::vec4>& SageModel::Get_Vertex_Colors()
{
	return clr_vtx;
}

std::vector<glm::vec2>& SageModel::Get_Vertex_Positions()
{
	return pos_vtx;
}

std::vector<glm::vec2>& SageModel::Get_Vertex_Texture_Coords()
{
	return tex_coords;
}


std::vector<GLushort>& SageModel::Get_Vertex_Indices()
{
	return idx_vtx;
}


SageShader* SageModel::Get_Shader_Program() const
{
	return base_shader_ptr;
}


bool SageModel::Is_Idx_Enabled() const
{
	return enable_vertex_indices;
}

void SageModel::Update_Vtx_Buffer_GPU()
{
	glNamedBufferSubData(vbo_hdl, 0, static_cast<GLsizeiptr>(sizeof(glm::vec2) * pos_vtx.size()), pos_vtx.data());
}










