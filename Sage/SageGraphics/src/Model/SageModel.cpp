#include "SageModel.hpp"

#include <iostream>

#include "SageModelManager.hpp"

int SageModel::model_count{};

SageModel::SageModel(const char* name, std::vector<glm::vec2>* pos, std::vector<glm::vec2>* texture, std::vector<glm::vec4>* clr, std::vector<GLushort>* idx)
	: model_id(model_count++), model_name(name), vao_hdl(0), vbo_hdl(0),
	ebo_hdl(0), tex_hdl(0), base_shader_ptr(nullptr), Is_Enabled(false), Enable_Vertex_Color(false), Enable_Vertex_Texture(false), Enable_Vertex_Indices(false),
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
		Enable_Vertex_Texture = true;
	}
	if (clr != nullptr)
	{
		clr_vtx = std::vector{ *clr };
		Enable_Vertex_Color = true;
	}
	if (idx != nullptr)
	{
		idx_vtx = std::vector{ *idx };
		Enable_Vertex_Indices = true;
	}

}


void SageModel::setup_gpu_buffer()
{
	// Create VAO VBO and load data
	glCreateBuffers(1, &vbo_hdl);

	// Check flags
	size_t vbo_size = (Enable_Vertex_Color) ? (sizeof(glm::vec2) * pos_vtx.size() + sizeof(glm::vec4) * clr_vtx.size()) : (sizeof(glm::vec2) * pos_vtx.size());

	if (Enable_Vertex_Texture)
		vbo_size += sizeof(glm::vec2) * tex_coords.size();

	if (shape_type == PrimitiveShape::PRIMITIVE_LINE || shape_type == PRIMITIVE_POINTS)
	{
		glNamedBufferData(vbo_hdl, static_cast<GLsizeiptr>(vbo_size), nullptr, GL_DYNAMIC_DRAW);
	}
	else
	{
		glNamedBufferStorage(vbo_hdl, static_cast<GLsizeiptr>(vbo_size), nullptr, GL_DYNAMIC_STORAGE_BIT);
	}

	glNamedBufferSubData(vbo_hdl, 0, sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());

	if (Enable_Vertex_Texture)
		glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec2) * tex_coords.size(), tex_coords.data());

	if (Enable_Vertex_Color)
		glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size() + ((Enable_Vertex_Texture) ? (sizeof glm::vec2 * tex_coords.size()) : 0) , sizeof(glm::vec4) * clr_vtx.size(), clr_vtx.data());

	glCreateVertexArrays(1, &vao_hdl);
	// Position
	glEnableVertexArrayAttrib(vao_hdl, 0); // vtx_position at location 0
	glVertexArrayVertexBuffer(vao_hdl, 0, vbo_hdl, 0, sizeof(glm::vec2));
	glVertexArrayAttribFormat(vao_hdl, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao_hdl, 0, 0);

	if (Enable_Vertex_Texture)
	{
		glEnableVertexArrayAttrib(vao_hdl, 1); // vtx_texture at location 2
		glVertexArrayVertexBuffer(vao_hdl, 1, vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec2)); // data location in VBO
		glVertexArrayAttribFormat(vao_hdl, 1, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao_hdl, 1, 1);

	}

	if (Enable_Vertex_Color)
	{
		glEnableVertexArrayAttrib(vao_hdl, 2); // vtx_color at location 1
		glVertexArrayVertexBuffer(vao_hdl, 2, vbo_hdl, sizeof(glm::vec2) * pos_vtx.size() + ((Enable_Vertex_Texture) ? (sizeof glm::vec2 * tex_coords.size()) : 0), sizeof(glm::vec4)); // data location in VBO
		glVertexArrayAttribFormat(vao_hdl, 2, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao_hdl, 2, 2);
	}

	if (Enable_Vertex_Indices)
	{
		glCreateBuffers(1, &ebo_hdl);
		glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_vtx.size(), idx_vtx.data(), GL_DYNAMIC_STORAGE_BIT);
		glVertexArrayElementBuffer(vao_hdl, ebo_hdl);
	}
	else ebo_hdl = 0;

	glBindVertexArray(0);
	Is_Enabled = true;
}


SageModel::~SageModel()
{
	model_count--;
	if (Is_Enabled)
	{
		glDeleteBuffers(1, &vbo_hdl);
		if (Enable_Vertex_Indices)
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
GLuint& SageModel::get_ebo_handle()
{
	return ebo_hdl;
}

GLuint SageModel::get_ebo_handle() const
{
	return ebo_hdl;
}

GLuint& SageModel::get_texture_handle()
{
	return tex_hdl;
}

GLuint SageModel::get_texture_handle() const
{
	return tex_hdl;
}
GLuint& SageModel::get_vao_handle()
{
	return vao_hdl;

}

GLuint SageModel::get_vao_handle() const
{
	return vao_hdl;
}

GLuint& SageModel::get_vbo_handle()
{
	return vbo_hdl;
}

GLuint SageModel::get_vbo_handle() const
{
	return vbo_hdl;
}




void SageModel::set_render_type(RENDER_TYPE type)
{
	mdl_render_type = type;
}

void SageModel::set_shape_type(PrimitiveShape shape)
{
	shape_type = shape;
}


std::vector<glm::vec4>& SageModel::get_vertex_colors()
{
	return clr_vtx;
}

std::vector<glm::vec2>& SageModel::get_vertex_positions()
{
	return pos_vtx;
}

std::vector<glm::vec2>& SageModel::get_vertex_texture_coords()
{
	return tex_coords;
}


std::vector<GLushort>& SageModel::get_vertex_indices()
{
	return idx_vtx;
}


SageShader* SageModel::get_shader_program() const
{
	return base_shader_ptr;
}


bool SageModel::is_idx_enabled() const
{
	return Enable_Vertex_Indices;
}

void SageModel::update_vtx_buffer_GPU()
{
	glNamedBufferSubData(vbo_hdl, 0, sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());
}










