#ifndef SAGE_SHADER_INTERNAL_HPP
#define SAGE_SHADER_INTERNAL_HPP
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>


// A library for loading and compiling shaders
class SageShaderInternal
{
private:
	unsigned int pgm_handle;
	bool is_linked;
	std::string log_string;

	bool loaded;

public:
	enum class SAGE_INTERNAL_SHADER_TYPE
	{
		S_INTERNAL_VERTEX_SHADER,
		S_INTERNAL_FRAGMENT_SHADER,
		S_INTERNAL_GEOMETRY_SHADER,
		S_INTERNAL_TESS_CONTROL_SHADER,
		S_INTERNAL_TESS_EVALUATION_SHADER,
		S_INTERNAL_COMPUTE_SHADER,	
		S_INTERNAL_count // number of shader types
	};
	SageShaderInternal();
	GLboolean CompileFromString(SAGE_INTERNAL_SHADER_TYPE shader_type, std::string const& source, std::string const& path = "");
	GLboolean CompileFromFile(SAGE_INTERNAL_SHADER_TYPE shader_type, std::string const& file_name);




	GLboolean Link();

	//Program Activation
	void Activate();
	void Deactivate();

	//Program Validation
	GLboolean Validate();

	//Compile Link and Validate
	GLboolean CompileLinkValidate(SAGE_INTERNAL_SHADER_TYPE shader_type, std::string const& source);

	// Program Info  - Getters

	// Get the program handle

	GLuint GetProgramHandle() const;
	GLboolean IsLinked() const;
	GLboolean is_loaded() const;

	std::string GetLog() const;



	// Vertex and Fragment bindings
	void BindVertexAttribLocation(GLuint index, const char* name);
	void BindFragAttribLocation(GLuint index, const char* name);

	// Shaders Uniforms

	// Get the location of a uniform variable
	GLint GetUniformLocation(const char* name, bool exit_on_error = false) const;

	// Setters for uniform variables
	// Numericals
	void Set_Uniform(const char* name, GLint val);
	void Set_Uniform(const char* name, GLfloat val);
	void Set_Uniform(const char* name, GLdouble val);
	void Set_Uniform(const char* name, GLboolean val);
	void Set_Uniform(const char* name, bool val);

	//Vectors - Singular
	void Set_Uniform(const char* name, GLfloat x, GLfloat y);
	void Set_Uniform(const char* name, GLfloat x, GLfloat y, GLfloat z);
	void Set_Uniform(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	//Vector - glm
	void Set_Uniform(const char* name, const glm::vec2& val);
	void Set_Uniform(const char* name, const glm::vec3& val);
	void Set_Uniform(const char* name, const glm::vec4& val);

	// Uniform Matrices
	void Set_Uniform(const char* name, const glm::mat2& val);
	void Set_Uniform(const char* name, const glm::mat3& val);
	void Set_Uniform(const char* name, const glm::mat4& val);


	void Set_Uniform_3f_m(const char* name, float* data);
	void Set_Uniform_3f_m(const char* name, const float* data) const;
	void Set_Uniform_4f_m(const char* name, float* data);
	void Set_Uniform_4f_m(const char* name, const float* data) const;



	void Print_Active_Attribs() const;

	void Print_Active_Uniforms() const;

	// Helper Functions
	bool FileExists(const std::string& file_name);
	bool DeleteShaderProgram();



	~SageShaderInternal();







};



#endif
