/* Start Header ************************************************************************/
/*!
\file		SageModel.cpp
\title		Little Match
\author		Jay Lim Jun Xiang, jayjunxiang.lim, 2301335 (100%)
\par		jayjunxiang.lim@digipen.edu
\date		03 October 2024
\brief		This file defines the SageModel class, responsible for managing 
			the graphical model data, including vertex positions, texture 
			coordinates, colors, and indices. It handles the creation and 
			management of GPU buffers (VBO, VAO, EBO), and provides functionality 
			for assigning shaders and updating vertex data on the GPU. The class 
			also supports primitive shape types and rendering configurations 
			using OpenGL.


			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "SageModel.hpp"

#include <iostream>

#include "SageModelManager.hpp"
//increments everytime a new SageModel object is created and decrements each time an object is destroyed. Useful for resource management
int SageModel::model_count{};

/*!*****************************************************************************
  \brief
	Constructor for the SageModel class. Initializes the model with vertex data,
	texture coordinates, colors, and indices.

  \param _name
	The name of the model.

  \param _pos
	The vertex positions for the model. This must be provided for model creation.

  \param _texture
	The texture coordinates for the model (optional).

  \param _clr
	The vertex colors for the model (optional).

  \param _idx
	The vertex indices for the model (optional).
*******************************************************************************/
SageModel::SageModel(const char* _name, std::vector<glm::vec2>* _pos, std::vector<glm::vec2>* _texture, std::vector<glm::vec4>* _clr, std::vector<GLushort>* _idx)
	: model_id(model_count++), model_name(_name), vao_hdl(0), vbo_hdl(0),
	ebo_hdl(0), tex_hdl(0), base_shader_ptr(nullptr), is_enabled(false), enable_vertex_color(false), enable_vertex_texture(false), enable_vertex_indices(false),
	shape_type(), mdl_render_type()
{
	
	if (!_pos)
	{
		std::cerr << "Error: Vertex position data is required for model creation." << '\n';
		std::exit(EXIT_FAILURE);
	}
	pos_vtx = std::vector{ *_pos };
	if (_texture != nullptr)
	{
		tex_coords = std::vector{ *_texture };
		enable_vertex_texture = true;
	}
	if (_clr != nullptr)
	{
		clr_vtx = std::vector{ *_clr };
		enable_vertex_color = true;
	}
	if (_idx != nullptr)
	{
		idx_vtx = std::vector{ *_idx };
		enable_vertex_indices = true;
	}

}

/*!*****************************************************************************
  \brief
	Sets up the GPU buffer by creating a VAO, VBO, and (if necessary) an EBO,
	and loading the vertex data into the GPU.
*******************************************************************************/
void SageModel::Setup_Gpu_Buffer()
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

/*!*****************************************************************************
  \brief
	Destructor for the SageModel class. Deletes the GPU buffers and VAO,
	and decrements the model count.
*******************************************************************************/
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


/*!*****************************************************************************
  \brief
	Assigns a shader program to the model for rendering.

  \param _shader
	The shader program to be assigned.
*******************************************************************************/
void SageModel::Assign_Shader_Program(SageShader* _shader)
{
	base_shader_ptr = _shader;
}

// Getters
/*!*****************************************************************************
  \brief
	Gets the EBO handle by reference.

  \return
	A reference to the EBO handle.
*******************************************************************************/
GLuint& SageModel::Get_EBO_Handle()
{
	return ebo_hdl;
}

/*!*****************************************************************************
  \brief
	Retrieves the EBO handle.

  \return
	The EBO handle.
*******************************************************************************/
GLuint SageModel::Get_EBO_Handle() const
{
	return ebo_hdl;
}

/*!*****************************************************************************
  \brief
	Retrieves the texture handle by reference.

  \return
	A reference to the texture handle.
*******************************************************************************/
GLuint& SageModel::Get_Texture_Handle()
{
	return tex_hdl;
}

/*!*****************************************************************************
  \brief
	Retrieves the texture handle.

  \return
	The texture handle.
*******************************************************************************/
GLuint SageModel::Get_Texture_Handle() const
{
	return tex_hdl;
}

/*!*****************************************************************************
  \brief
	Retrieves the VAO handle by reference.

  \return
	A reference to the VAO handle.
*******************************************************************************/
GLuint& SageModel::Get_VAO_Handle()
{
	return vao_hdl;

}

/*!*****************************************************************************
  \brief
	Retrieves the VAO handle.

  \return
	The VAO handle.
*******************************************************************************/
GLuint SageModel::Get_VAO_Handle() const
{
	return vao_hdl;
}

/*!*****************************************************************************
  \brief
	Retrieves the VBO handle by reference.

  \return
	A reference to the VBO handle.
*******************************************************************************/
GLuint& SageModel::Get_VBO_Handle()
{
	return vbo_hdl;
}


/*!*****************************************************************************
  \brief
	Retrieves the VBO handle.

  \return
	The VBO handle.
*******************************************************************************/
GLuint SageModel::Get_VBO_Handle() const
{
	return vbo_hdl;
}

/*!*****************************************************************************
  \brief
	Retrieves the shape type of the model.

  \return
	The shape type as an integer.
*******************************************************************************/
int SageModel::Get_Shape_Type()
{
	return static_cast<int>(shape_type);
}

/*!*****************************************************************************
  \brief
	Sets the render type for the model.

  \param _type
	The render type as an integer.
*******************************************************************************/
void SageModel::Set_Render_Type(int _type)
{
	mdl_render_type = static_cast<RENDER_TYPE>(_type);

}

/*!*****************************************************************************
  \brief
	Sets the shape type for the model.

  \param _shape
	The shape type as an integer.
*******************************************************************************/
void SageModel::Set_Shape_Type(int _shape)
{
	shape_type = static_cast<PrimitiveShape>(_shape);

}

/*!*****************************************************************************
  \brief
	Sets the render type for the model.

  \param _type
	The render type as an enum.
*******************************************************************************/
void SageModel::Set_Render_Type(RENDER_TYPE _type)
{
	mdl_render_type = _type;
}

/*!*****************************************************************************
  \brief
	Sets the shape type for the model.

  \param _shape
	The shape type as an enum.
*******************************************************************************/
void SageModel::Set_Shape_Type(PrimitiveShape _shape)
{
	shape_type = _shape;
}

/*!*****************************************************************************
  \brief
	Retrieves the vertex colors.

  \return
	A reference to the vector of vertex colors.
*******************************************************************************/
std::vector<glm::vec4>& SageModel::Get_Vertex_Colors()
{
	return clr_vtx;
}

/*!*****************************************************************************
  \brief
	Retrieves the vertex positions.

  \return
	A reference to the vector of vertex positions.
*******************************************************************************/
std::vector<glm::vec2>& SageModel::Get_Vertex_Positions()
{
	return pos_vtx;
}

/*!*****************************************************************************
  \brief
	Retrieves the texture coordinates.

  \return
	A reference to the vector of texture coordinates.
*******************************************************************************/
std::vector<glm::vec2>& SageModel::Get_Vertex_Texture_Coords()
{
	return tex_coords;
}

/*!*****************************************************************************
  \brief
	Retrieves the vertex indices.

  \return
	A reference to the vector of vertex indices.
*******************************************************************************/
std::vector<GLushort>& SageModel::Get_Vertex_Indices()
{
	return idx_vtx;
}

/*!*****************************************************************************
  \brief
	Retrieves the shader program assigned to the model.

  \return
	A pointer to the shader program.
*******************************************************************************/
SageShader* SageModel::Get_Shader_Program() const
{
	return base_shader_ptr;
}

/*!*****************************************************************************
  \brief
	Checks if vertex indices are enabled.

  \return
	True if vertex indices are enabled, otherwise false.
*******************************************************************************/
bool SageModel::Is_Idx_Enabled() const
{
	return enable_vertex_indices;
}

/*!*****************************************************************************
  \brief
	Updates the vertex buffer on the GPU with the current vertex positions.
*******************************************************************************/
void SageModel::Update_Vtx_Buffer_GPU()
{
	glNamedBufferSubData(vbo_hdl, 0, static_cast<GLsizeiptr>(sizeof(glm::vec2) * pos_vtx.size()), pos_vtx.data());
}










