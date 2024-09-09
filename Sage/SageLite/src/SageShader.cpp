#include "SageShader.hpp"

#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>


SageShader::SageShader() : pgm_handle(0), is_linked(false) {};

//SageShader::~SageShader()
//{
//	if (pgm_handle != 0)
//	{
//		bool delete_status = DeleteShaderProgram();
//		if (!delete_status)
//		{
//			std::cout << "Error: Failed to delete shader program.";
//			std::exit(EXIT_FAILURE);
//		}
//		pgm_handle = 0;
//		is_linked = false;
//
//	}
//}
GLboolean SageShader::CompileFromString(SHADER_TYPE shader_type, std::string const& source, std::string const& path)
{
	GLuint shader_handle = 0;
	GLint status = 0;
	const char* src = source.c_str();
	if (pgm_handle <= 0)
	{
		pgm_handle = glCreateProgram();
		if (pgm_handle == 0)
		{
			std::cerr << "Error: Failed to create shader program." << '\n';
			return false;
		}

	}
	switch (shader_type)
	{
	case SHADER_TYPE::VERTEX_SHADER:
		shader_handle = glCreateShader(GL_VERTEX_SHADER);
		break;
	case SHADER_TYPE::FRAGMENT_SHADER:
		shader_handle = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case SHADER_TYPE::GEOMETRY_SHADER:
		shader_handle = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case SHADER_TYPE::TESS_CONTROL_SHADER:
		shader_handle = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;
	case SHADER_TYPE::TESS_EVALUATION_SHADER:
		shader_handle = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;
	case SHADER_TYPE::COMPUTE_SHADER:
		shader_handle = glCreateShader(GL_COMPUTE_SHADER);
		break;
	default:
		std::cerr << "Error: Invalid shader type." << '\n';
		return false;
	}


	char const* src_code[] = { src };
	glShaderSource(shader_handle, 1, src_code, NULL);
	glCompileShader(shader_handle);

	glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint log_length = 0;
		glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &log_length);

		std::string log(log_length, ' ');
		glGetShaderInfoLog(shader_handle, log_length, &log_length, &log[0]);

		log_string = log;

		std::cerr << "Error: Failed to compile (" << ((shader_type == SHADER_TYPE::VERTEX_SHADER) ? "VERTEX" : "FRAGMENT") << ')'  << '\n';
		if (path != "")
			std::cerr << "At: " << path << '\n';
		std::cerr << log << '\n';

		return false;
	}

	glAttachShader(pgm_handle, shader_handle);

	

	return true;
}

GLboolean SageShader::CompileFromFile(SHADER_TYPE shader_type, std::string const& file_name)
{
	std::ifstream file(file_name);

	if (!file)
	{
		std::cerr << "Error: Failed to open file." << '\n';
		return false;
	}
	if (pgm_handle <= 0)
	{
		pgm_handle = glCreateProgram();
		if (pgm_handle == 0)
		{
			std::cerr << "Error: Failed to create shader program." << '\n';
			return false;
		}

	}

	std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return CompileFromString(shader_type, source, file_name);
}


// Helper function to link the shader program

GLboolean SageShader::Link()
{
	GLint status = 0;
	glLinkProgram(pgm_handle);

	glGetProgramiv(pgm_handle, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint log_length = 0;
		glGetProgramiv(pgm_handle, GL_INFO_LOG_LENGTH, &log_length);

		std::string log(log_length, ' ');
		glGetProgramInfoLog(pgm_handle, log_length, &log_length, &log[0]);

		log_string = log;

		std::cerr << "Error: Failed to link shader program." << '\n';
		std::cerr << log << '\n';

		return false;
	}

	is_linked = true;
	//glDeleteShader();
	return true;
}


GLboolean SageShader::Validate()
{
	GLint status = 0;
	glValidateProgram(pgm_handle);

	glGetProgramiv(pgm_handle, GL_VALIDATE_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint log_length = 0;
		glGetProgramiv(pgm_handle, GL_INFO_LOG_LENGTH, &log_length);

		std::string log(log_length, ' ');
		glGetProgramInfoLog(pgm_handle, log_length, &log_length, &log[0]);

		log_string = log;

		std::cerr << "Error: Failed to validate shader program." << '\n';
		std::cerr << log << '\n';

		return false;
	}

	return true;
}


void SageShader::Activate()
{
	if (pgm_handle > 0 && is_linked)
		glUseProgram(pgm_handle);
	
	
}

void SageShader::Deactivate()
{
	glUseProgram(0);
}




GLuint SageShader::GetProgramHandle() const
{
	return pgm_handle;
}

std::string SageShader::GetLog() const
{
	return log_string;
}

GLboolean SageShader::IsLinked() const
{
	return is_linked;
}

void SageShader::BindVertexAttribLocation(GLuint index, const char* name)
{
	glBindAttribLocation(pgm_handle, index, name);
}

void SageShader::BindFragAttribLocation(GLuint index, const char* name)
{
	glBindFragDataLocation(pgm_handle, index, name);

}

GLint SageShader::GetUniformLocation(const char* name, bool exit_on_error)
{
#if _DEBUG
	std::cout << "Getting uniform location for: " << name << '\n';
#endif

	GLint loc = glGetUniformLocation(pgm_handle, name);

	if (loc == -1)
	{
		std::cerr << "Error: Failed to get uniform location for: " << name << '\n';
		if (exit_on_error)
			std::exit(EXIT_FAILURE);

	}

	return loc;
}

// Uniform setter - Numerical

void SageShader::SetUniform(const char* name, GLint val)
{
	GLint loc = GetUniformLocation(name);
	glUniform1i(loc, val);
}


void SageShader::SetUniform(const char* name, GLfloat val)
{
	GLint loc = GetUniformLocation(name);
	glUniform1f(loc, val);
}

void SageShader::SetUniform(const char* name, GLdouble val)
{
	GLint loc = GetUniformLocation(name);
	glUniform1d(loc, val);
}

void SageShader::SetUniform(const char* name, GLboolean val)
{
	GLint loc = GetUniformLocation(name);
	glUniform1i(loc, val);
}

void SageShader::SetUniform(const char* name, bool val)
{
	GLint loc = GetUniformLocation(name);
	glUniform1i(loc, val ? GL_TRUE : GL_FALSE);
}

// Uniform setter - Vector - Singular

void SageShader::SetUniform(const char* name, GLfloat x, GLfloat y)
{
	GLint loc = GetUniformLocation(name);
	glUniform2f(loc, x, y);
}
void SageShader::SetUniform(const char* name, GLfloat x, GLfloat y, GLfloat z)
{
	GLint loc = GetUniformLocation(name);
	glUniform3f(loc, x, y, z);

}

void SageShader::SetUniform(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	GLint loc = GetUniformLocation(name);
	glUniform4f(loc, x, y, z, w);
}

// Uniform setter - Vector - glm

void SageShader::SetUniform(const char* name, const glm::vec2& val)
{
	GLint loc = GetUniformLocation(name);
	glUniform2fv(loc, 1, glm::value_ptr(val));
}

void SageShader::SetUniform(const char* name, const glm::vec3& val)
{
	GLint loc = GetUniformLocation(name);
	glUniform3fv(loc, 1, glm::value_ptr(val));
}

void SageShader::SetUniform(const char* name, const glm::vec4& val)
{
	GLint loc = GetUniformLocation(name);
	glUniform4fv(loc, 1, glm::value_ptr(val));
}

// Uniform setter - Matrices - glm

void SageShader::SetUniform(const char* name, const glm::mat2& val)
{
	GLint loc = GetUniformLocation(name);
	glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(val));

}

void SageShader::SetUniform(const char* name, const glm::mat3& val)
{
	GLint loc = GetUniformLocation(name);
	glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}
void SageShader::SetUniform(const char* name, const glm::mat4& val)
{
	GLint loc = GetUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}

// Helper Functions
bool SageShader::FileExists(const std::string& file_name)
{
	std::ifstream file(file_name);
	return file.good();
}

bool SageShader::DeleteShaderProgram()
{
	glDeleteProgram(pgm_handle);
	return true;
}

// Print Active Attributes in a neatly table format
void SageShader::PrintActiveAttribs() const
{
	GLint num_attribs = 0;
	glGetProgramInterfaceiv(pgm_handle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &num_attribs);

	std::vector<GLchar> name_data(256);
	std::vector<GLenum> properties = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };

	std::cout << "Active Attributes" << '\n';
	std::cout << "Index | Name" << '\n';
	std::cout << "----------------" << '\n';

	for (int i = 0; i < num_attribs; i++)
	{
		GLint attrib[3];
		glGetProgramResourceiv(pgm_handle, GL_PROGRAM_INPUT, i, 3, &properties[0], 3, NULL, attrib);

		name_data.resize(attrib[0]);
		glGetProgramResourceName(pgm_handle, GL_PROGRAM_INPUT, i, name_data.size(), NULL, &name_data[0]);

		std::string name((char*)&name_data[0], name_data.size() - 1);
		std::cout << attrib[2] << " | " << name << '\n';
	}
}

void SageShader::PrintActiveUniforms() const
{
	GLint num_uniforms = 0;
	glGetProgramInterfaceiv(pgm_handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &num_uniforms);

	std::vector<GLchar> name_data(256);
	std::vector<GLenum> properties = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };

	std::cout << "Active Uniforms" << '\n';
	std::cout << "Index | Name" << '\n';
	std::cout << "----------------" << '\n';

	for (int i = 0; i < num_uniforms; i++)
	{
		GLint uniform[3];
		glGetProgramResourceiv(pgm_handle, GL_UNIFORM, i, 3, &properties[0], 3, NULL, uniform);

		name_data.resize(uniform[0]);
		glGetProgramResourceName(pgm_handle, GL_UNIFORM, i, name_data.size(), NULL, &name_data[0]);

		std::string name((char*)&name_data[0], name_data.size() - 1);
		std::cout << uniform[2] << " | " << name << '\n';
	}
}




















