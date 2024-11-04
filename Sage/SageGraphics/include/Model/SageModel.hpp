/* Start Header ************************************************************************/
/*!
\file		SageModel.hpp
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

#pragma once
#include <GL/glew.h>
#include "Main.h"

#include "SageShader.hpp"
#include "SageRenderer.hpp"


enum class PrimitiveShape;
enum class RENDER_TYPE;


/// A class for handling 2D model data
class SageModel
{
	// ID for the model
	GLuint model_id;
	std::string model_name;


	// OpenGL handles
	GLuint vao_hdl;
	GLuint vbo_hdl;
	GLuint ebo_hdl;
	GLuint tex_hdl;


	// Data for the model
	std::vector<glm::vec2> pos_vtx;
	std::vector<glm::vec4> clr_vtx;
	std::vector<glm::vec2> tex_coords;

	std::vector<GLushort> idx_vtx;

	// Material data
	SageShader* base_shader_ptr;

	// Flags
	bool is_enabled;
	bool enable_vertex_color;
	bool enable_vertex_texture;
	bool enable_vertex_indices;

	


	// Shape Type
	PrimitiveShape shape_type;
	RENDER_TYPE mdl_render_type;
	

	




public:

	// Constructor

	SageModel() : model_id(0), model_name("Default"), vao_hdl(0), vbo_hdl(0), ebo_hdl(0), tex_hdl(0), base_shader_ptr(nullptr), is_enabled(false), enable_vertex_color(false), enable_vertex_texture(false), enable_vertex_indices(false), shape_type(), mdl_render_type() {}
	/*!*****************************************************************************
	  \brief
		Constructor for the SageModel class. Initializes the model with vertex data,
		texture coordinates, colors, and indices.

	  \param _name
		The name of the model.

	  \param _pos
		The vertex positions for the model. This must be provided for model creation.

	  \param _texture
		The texture coordinates for the model 

	  \param _clr
		The vertex colors for the model

	  \param _idx
		The vertex indices for the model
	*******************************************************************************/
	SageModel(const char* _name, std::vector<glm::vec2>* _pos, std::vector<glm::vec2>* _texture = nullptr, std::vector<glm::vec4>* _clr = nullptr, std::vector<GLushort>* _idx = nullptr);
	
	/*!*****************************************************************************
	  \brief
		Destructor for the SageModel class. Deletes the GPU buffers and VAO,
		and decrements the model count.
	*******************************************************************************/
	~SageModel();

	/*!*****************************************************************************
	  \brief
		Sets up the GPU buffer by creating a VAO, VBO, and (if necessary) an EBO,
		and loading the vertex data into the GPU.
	*******************************************************************************/
	void Setup_Gpu_Buffer(); // setup vao, vbo, ebo
	
	/*!*****************************************************************************
	  \brief
		Assigns a shader program to the model for rendering.

	  \param _shader
		The shader program to be assigned.
	*******************************************************************************/
	void Assign_Shader_Program(SageShader* _shader);



	/// Getters

	/*!*****************************************************************************
	  \brief
		Retrieves the VAO handle.

	  \return
		The VAO handle.
	*******************************************************************************/
	GLuint Get_VAO_Handle() const;

	/*!*****************************************************************************
	  \brief
		Retrieves the VBO handle.

	  \return
		The VBO handle.
	*******************************************************************************/
	GLuint Get_VBO_Handle() const;

	/*!*****************************************************************************
	  \brief
		Retrieves the EBO handle.

	  \return
		The EBO handle.
	*******************************************************************************/
	GLuint Get_EBO_Handle() const;

	/*!*****************************************************************************
	  \brief
		Retrieves the texture handle.

	  \return
		The texture handle.
	*******************************************************************************/
	GLuint Get_Texture_Handle() const;

	/*!*****************************************************************************
	  \brief
		Retrieves the VAO handle by reference.

	  \return
		A reference to the VAO handle.
	*******************************************************************************/
	GLuint& Get_VAO_Handle();

	/*!*****************************************************************************
	  \brief
		Retrieves the VBO handle by reference.

	  \return
		A reference to the VBO handle.
	*******************************************************************************/
	GLuint& Get_VBO_Handle();
	/*!*****************************************************************************
	  \brief
		Gets the EBO handle by reference.

	  \return
		A reference to the EBO handle.
	*******************************************************************************/
	GLuint& Get_EBO_Handle();

	/*!*****************************************************************************
	  \brief
		Retrieves the texture handle by reference.

	  \return
		A reference to the texture handle.
	*******************************************************************************/
	GLuint& Get_Texture_Handle();

	/*!*****************************************************************************
	  \brief
		Retrieves the vertex positions.

	  \return
		A reference to the vector of vertex positions.
	*******************************************************************************/
	std::vector<glm::vec2>& Get_Vertex_Positions();

	/*!*****************************************************************************
	  \brief
		Retrieves the vertex colors.

	  \return
		A reference to the vector of vertex colors.
	*******************************************************************************/
	std::vector<glm::vec4>& Get_Vertex_Colors();

	/*!*****************************************************************************
	  \brief
		Retrieves the texture coordinates.

	  \return
		A reference to the vector of texture coordinates.
	*******************************************************************************/
	std::vector<glm::vec2>& Get_Vertex_Texture_Coords();

	/*!*****************************************************************************
	  \brief
		Retrieves the vertex indices.

	  \return
		A reference to the vector of vertex indices.
	*******************************************************************************/
	std::vector<GLushort>& Get_Vertex_Indices();

	/*!*****************************************************************************
	  \brief
		Retrieves the shader program assigned to the model.

	  \return
		A pointer to the shader program.
	*******************************************************************************/
	SageShader* Get_Shader_Program() const;

	/*!*****************************************************************************
	  \brief
		Sets the shape type for the model.

	  \param _shape
		The shape type as an enum.
	*******************************************************************************/
	void Set_Shape_Type(PrimitiveShape _shape);

	/*!*****************************************************************************
	  \brief
		Sets the render type for the model.

	  \param _type
		The render type as an enum.
	*******************************************************************************/
	void Set_Render_Type(RENDER_TYPE _type);

	/*!*****************************************************************************
	  \brief
		Sets the render type for the model.

	  \param _type
		The render type as an integer.
	*******************************************************************************/
	void Set_Render_Type(int _type);

	/*!*****************************************************************************
	  \brief
		Sets the shape type for the model.

	  \param _shape
		The shape type as an integer.
	*******************************************************************************/
	void Set_Shape_Type(int _shape);

	/*!*****************************************************************************
	  \brief
		Checks if vertex indices are enabled.

	  \return
		True if vertex indices are enabled, otherwise false.
	*******************************************************************************/
	bool Is_Idx_Enabled() const;

	/*!*****************************************************************************
	  \brief
		Updates the vertex buffer on the GPU with the current vertex positions.
	*******************************************************************************/
	void Update_Vtx_Buffer_GPU();

	//increments everytime a new SageModel object is created and decrements each time an object is destroyed. Useful for resource management.
	static int model_count;

	/*!*****************************************************************************
	  \brief
		Retrieves the shape type of the model.

	  \return
		The shape type as an integer.
	*******************************************************************************/
	int Get_Shape_Type();


};


