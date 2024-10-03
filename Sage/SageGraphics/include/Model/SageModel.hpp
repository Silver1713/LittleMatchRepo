	#ifndef SAGEMODEL_HPP
#define SAGEMODEL_HPP


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
	SageModel(const char* name, std::vector<glm::vec2>* pos, std::vector<glm::vec2>* texture=nullptr, std::vector<glm::vec4>* clr=nullptr, std::vector<GLushort>* idx=nullptr);
	~SageModel();


	void setup_gpu_buffer(); // setup vao, vbo, ebo
	

	void AssignShaderProgram(SageShader* shader);



	/// Getters
	GLuint Get_VAO_Handle() const;
	GLuint Get_VBO_Handle() const;
	GLuint Get_EBO_Handle() const;
	GLuint Get_Texture_Handle() const;

	GLuint& Get_VAO_Handle();
	GLuint& Get_VBO_Handle();
	GLuint& Get_EBO_Handle();
	GLuint& Get_Texture_Handle();

	std::vector<glm::vec2>& Get_Vertex_Positions();
	std::vector<glm::vec4>& Get_Vertex_Colors();
	std::vector<glm::vec2>& Get_Vertex_Texture_Coords();
	std::vector<GLushort>& Get_Vertex_Indices();

	SageShader* Get_Shader_Program() const;

	void Set_Shape_Type(PrimitiveShape shape);

	void Set_Render_Type(RENDER_TYPE type);
	void Set_Render_Type(int type);
	void Set_Shape_Type(int shape);

	bool Is_Idx_Enabled() const;


	void Update_Vtx_Buffer_GPU();

	static int model_count;

	int get_shape_type();


};

#endif

