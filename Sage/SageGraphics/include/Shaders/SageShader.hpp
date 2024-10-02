/* Start Header ************************************************************************/
/*!
\file		SageShader.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The public interface containing the SageShader class containing methods and attributes
			to manage shader programs, compiling and linking of the shader programs. Furthmore, this
			class expose methods from the internal class allowing calls to be  delegated to the
			private interface.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#ifndef SAGE_SHADER_HPP
#define SAGE_SHADER_HPP

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

#include <memory>
#include <glm/glm.hpp>
#include <string>

#include "Vector4.h"

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

	bool CompileFromString(SAGE_SHADER_TYPE shader_type, std::string const& source, std::string const& path = "");
	bool CompileFromFile(SAGE_SHADER_TYPE shader_type, std::string const& file_name);




	bool Link();

	//Program Activation
	void Activate();
	void Deactivate();

	//Program Validation
	bool Validate();

	//Compile Link and Validate
	bool CompileLinkValidate(SAGE_SHADER_TYPE shader_type, std::string const& source);

	// Program Info  - Getters

	// Get the program handle

	unsigned int GetProgramHandle();
	bool IsLinked() const;

	std::string GetLog() const;



	// Vertex and Fragment bindings
	void BindVertexAttribLocation(int index, const char* name);
	void BindFragAttribLocation(int index, const char* name);

	// Shaders Uniforms

	// Get the location of a uniform variable
	int GetUniformLocation(const char* name, bool exit_on_error = false);

	// Setters for uniform variables
	// Numericals
	void SetUniform(const char* name, int val);
	void SetUniform(const char* name, float val);
	void SetUniform(const char* name, double val);
	void SetUniform(const char* name, bool val);

	//Vectors - Singular
	void SetUniform(const char* name, float x, float y);
	void SetUniform(const char* name, float x, float y, float z);
	void SetUniform(const char* name, float x, float y, float z, float w);

	//Vector - glm
	void SetUniform(const char* name,  ToastBox::Vec2 const& val);
	void SetUniform(const char* name,  ToastBox::Vec3 const& val);
	void SetUniform(const char* name,  ToastBox::Vec4 const& val);

	// Uniform Matrices
	void SetUniform(const char* name, const glm::mat2& val);
	void SetUniform(const char* name, const glm::mat3& val);
	void SetUniform(const char* name, const glm::mat4& val);

	void SetUniform(const char* name, const ToastBox::Matrix3x3& val);
	void SetUniform(const char* name, const ToastBox::Matrix4& val);



	void PrintActiveAttribs() const;

	void PrintActiveUniforms() const;

	// Helper Functions
	bool FileExists(const std::string& file_name);
	bool DeleteShaderProgram();









};



#endif
