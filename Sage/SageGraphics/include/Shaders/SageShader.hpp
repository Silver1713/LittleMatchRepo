#ifndef SAGE_SHADER_HPP
#define SAGE_SHADER_HPP
#include <memory>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

// A library for loading and compiling shaders
class SageShader
{

	class SageShaderInternalImpl;
	std::unique_ptr<SageShaderInternalImpl> sage_impl;

	unsigned int pgm_handle;
	bool is_linked;
	std::string log_string;

public:
	enum class SAGE_SHADER_TYPE
	{
		SAGE_VERTEX_SHADER,
		SAGE_FRAGMENT_SHADER,
		SAGE_GEOMETRY_SHADER,
		SAGE_TESS_CONTROL_SHADER,
		SAGE_TESS_EVALUATION_SHADER,
		SAGE_COMPUTE_SHADER,
		SAGE_SHADER_count // number of shader types
	};

	SageShader();
	~SageShader();
	//Delete copy constructor
	SageShader(const SageShader&) = delete;
	//Delete assignment operator
	SageShader& operator=(const SageShader&) = delete;

	//Move constructor
	SageShader(SageShader&& other) noexcept;
	//Move assignment operator
	SageShader& operator=(SageShader&& other) noexcept;

	GLboolean CompileFromString(SAGE_SHADER_TYPE shader_type, std::string const& source, std::string const& path = "");
	GLboolean CompileFromFile(SAGE_SHADER_TYPE shader_type, std::string const& file_name);




	GLboolean Link();

	//Program Activation
	void Activate();
	void Deactivate();

	//Program Validation
	GLboolean Validate();

	//Compile Link and Validate
	GLboolean CompileLinkValidate(SAGE_SHADER_TYPE shader_type, std::string const& source);

	// Program Info  - Getters

	// Get the program handle

	GLuint GetProgramHandle();
	GLboolean IsLinked() const;

	std::string GetLog() const;



	// Vertex and Fragment bindings
	void BindVertexAttribLocation(GLuint index, const char* name);
	void BindFragAttribLocation(GLuint index, const char* name);

	// Shaders Uniforms

	// Get the location of a uniform variable
	GLint GetUniformLocation(const char* name, bool exit_on_error = false);

	// Setters for uniform variables
	// Numericals
	void SetUniform(const char* name, GLint val);
	void SetUniform(const char* name, GLfloat val);
	void SetUniform(const char* name, GLdouble val);
	void SetUniform(const char* name, GLboolean val);
	void SetUniform(const char* name, bool val);

	//Vectors - Singular
	void SetUniform(const char* name, GLfloat x, GLfloat y);
	void SetUniform(const char* name, GLfloat x, GLfloat y, GLfloat z);
	void SetUniform(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	//Vector - glm
	void SetUniform(const char* name, const glm::vec2& val);
	void SetUniform(const char* name, const glm::vec3& val);
	void SetUniform(const char* name, const glm::vec4& val);

	// Uniform Matrices
	void SetUniform(const char* name, const glm::mat2& val);
	void SetUniform(const char* name, const glm::mat3& val);
	void SetUniform(const char* name, const glm::mat4& val);



	void PrintActiveAttribs() const;

	void PrintActiveUniforms() const;

	// Helper Functions
	bool FileExists(const std::string& file_name);
	bool DeleteShaderProgram();









};



#endif
