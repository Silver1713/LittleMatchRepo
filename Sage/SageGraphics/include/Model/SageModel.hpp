#ifndef SAGEMODEL_HPP
#define SAGEMODEL_HPP


#include "Main.h"
#include "SageShader.hpp"
#include "SageRenderer.hpp"


enum PrimitiveShape;
enum RENDER_TYPE;


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
	bool Is_Enabled;
	bool Enable_Vertex_Color;
	bool Enable_Vertex_Texture;
	bool Enable_Vertex_Indices;

	


	// Shape Type
	PrimitiveShape shape_type;
	RENDER_TYPE mdl_render_type;
	

	




public:

	// Constructor

	SageModel() : model_id(0), model_name("Default"), vao_hdl(0), vbo_hdl(0), ebo_hdl(0), tex_hdl(0), base_shader_ptr(nullptr), Is_Enabled(false), Enable_Vertex_Color(false), Enable_Vertex_Texture(false), Enable_Vertex_Indices(false), shape_type(), mdl_render_type() {}
	SageModel(const char* name, std::vector<glm::vec2>* pos, std::vector<glm::vec2>* texture=nullptr, std::vector<glm::vec4>* clr=nullptr, std::vector<GLushort>* idx=nullptr);
	~SageModel();


	void setup_gpu_buffer(); // setup vao, vbo, ebo
	

	void AssignShaderProgram(SageShader* shader);



	/// Getters
	GLuint get_vao_handle() const;
	GLuint get_vbo_handle() const;
	GLuint get_ebo_handle() const;
	GLuint get_texture_handle() const;

	GLuint& get_vao_handle();
	GLuint& get_vbo_handle();
	GLuint& get_ebo_handle();
	GLuint& get_texture_handle();

	std::vector<glm::vec2>& get_vertex_positions();
	std::vector<glm::vec4>& get_vertex_colors();
	std::vector<glm::vec2>& get_vertex_texture_coords();
	std::vector<GLushort>& get_vertex_indices();

	SageShader* get_shader_program() const;

	void set_shape_type(PrimitiveShape shape);
	void set_render_type(RENDER_TYPE type);

	bool is_idx_enabled() const;


	void update_vtx_buffer_GPU();

	static int model_count;



};

#endif

