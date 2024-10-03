#include <iostream>
#include <fstream>

#include "SageShaderInternal.hpp"
#include "SageShader.hpp"

#include "glm/gtc/type_ptr.inl"

class SageShader::SageShaderInternalImpl
{
private:
	std::unique_ptr<SageShaderInternal> internal_impl;
public:
	SageShaderInternalImpl() : internal_impl(std::make_unique<SageShaderInternal>()) {};

	bool Compile(std::string const& path, SAGE_SHADER_TYPE type)
	{
		return internal_impl->CompileFromFile(static_cast<SageShaderInternal::SAGE_INTERNAL_SHADER_TYPE>(type), path);
	}

	bool Compile_Raw_String(std::string const& source, SAGE_SHADER_TYPE type, std::string const& path)
	{
		return internal_impl->CompileFromString(static_cast<SageShaderInternal::SAGE_INTERNAL_SHADER_TYPE>(type), source, path);
	}

	bool Link()
	{
		return internal_impl->Link();

	}

	bool Validate()
	{
		return internal_impl->Validate();
	}
	

	void Use()
	{
		internal_impl->Activate();

	}

	void Unuse()
	{
		internal_impl->Deactivate();
	}


	std::string GetLog()
	{
		return internal_impl->GetLog();
	}

	unsigned int GetProgramID()
	{
		return internal_impl->GetProgramHandle();

	}



	void PrintActiveAttribs()
	{
		internal_impl->PrintActiveAttribs();
	}

	void PrintActiveUniform()
	{
		internal_impl->PrintActiveUniforms();

	}

	bool DeleteShaderProgram()
	{
		return internal_impl->DeleteShaderProgram();

	}


	void SetUniform(const char* name, int const& val) const
	{
		internal_impl->SetUniform(name, val);
	}

	void SetUniform(const char* name, float const& val) const
	{
		internal_impl->SetUniform(name, val);
	}

	void SetUniform(const char* name, double const& val) const
	{
		internal_impl->SetUniform(name, val);
	}


	void SetUniform(const char* name, bool val) const
	{
		internal_impl->SetUniform(name, val);
	}

	void SetUniform(const char* name, float x, float y) const
	{
		internal_impl->SetUniform(name, x, y);
	}

	void SetUniform(const char* name, float x, float y, float z) const
	{
		internal_impl->SetUniform(name, x, y, z);
	}

	void SetUniform(const char* name, float x, float y, float z, float w) const
	{
		internal_impl->SetUniform(name, x, y, z, w);
	}

	void SetUniform(const char* name, const ToastBox::Matrix3x3& val) const
	{
		
		internal_impl->SetUniform3fm(name, val.data());
	}

	void SetUniform(const char* name, const ToastBox::Matrix4& val) const
	{
		internal_impl->SetUniform4fm(name, val.Data());
	}

};


SageShader::SageShader() : sage_impl{ std::make_unique<SageShaderInternalImpl>() }, pgm_handle(0), is_linked(false)
{

};


SageShader::SageShader(SageShader&& other) noexcept : sage_impl(std::move(other.sage_impl)), pgm_handle(other.pgm_handle), is_linked(other.is_linked)
{
	other.pgm_handle = 0;
	other.is_linked = false;
}

SageShader& SageShader::operator=(SageShader&& other) noexcept
{
	if (this != &other)
	{
		sage_impl = std::move(other.sage_impl);
		pgm_handle = other.pgm_handle;
		is_linked = other.is_linked;

		other.pgm_handle = 0;
		other.is_linked = false;
	}

	return *this;
}



bool SageShader::CompileFromString(SAGE_SHADER_TYPE shader_type, std::string const& source, std::string const& path)
{
	return sage_impl->Compile_Raw_String(source, shader_type, path);
}

bool SageShader::CompileFromFile(SAGE_SHADER_TYPE shader_type, std::string const& file_name)
{
	return sage_impl->Compile(file_name, shader_type);
}


// Helper function to link the shader program

bool SageShader::Link()
{

	is_linked = sage_impl->Link();
	return is_linked;
}


bool SageShader::Validate()
{
	return sage_impl->Validate();
}


void SageShader::Activate()
{
	sage_impl->Use();


}

void SageShader::Deactivate()
{
	sage_impl->Unuse();
}




unsigned int SageShader::GetProgramHandle()
{
	pgm_handle = sage_impl->GetProgramID();
	return sage_impl->GetProgramID();
}

std::string SageShader::GetLog() const
{
	return sage_impl->GetLog();
}

bool SageShader::IsLinked() const
{
	return is_linked;
}

void SageShader::BindVertexAttribLocation(int index, const char* name)
{
	glBindAttribLocation(pgm_handle, index, name);
}

void SageShader::BindFragAttribLocation(int index, const char* name)
{
	glBindFragDataLocation(pgm_handle, index, name);

}

int SageShader::GetUniformLocation(const char* name, bool exit_on_error)
{

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

void SageShader::SetUniform(const char* name, int val)
{
	sage_impl->SetUniform(name, val);
}


void SageShader::SetUniform(const char* name, float val)
{
	sage_impl->SetUniform(name, val);
}

void SageShader::SetUniform(const char* name, double val)
{
	sage_impl->SetUniform(name, val);
}

void SageShader::SetUniform(const char* name, bool val)
{
	sage_impl->SetUniform(name, val);
}
// Uniform setter - Vector - Singular

void SageShader::SetUniform(const char* name, float x, float y)
{
	sage_impl->SetUniform(name, x, y);
}
void SageShader::SetUniform(const char* name, float x, float y, float z)
{
	sage_impl->SetUniform(name, x, y, z);

}

void SageShader::SetUniform(const char* name, float x, float y, float z, float w)
{
	sage_impl->SetUniform(name, x, y, z, w);
}

// Uniform setter - Vector - glm

void SageShader::SetUniform(const char* name, const ToastBox::Vec2& val)
{
	sage_impl->SetUniform(name, val.GetX(), val.GetY());
}

void SageShader::SetUniform(const char* name, const ToastBox::Vec3& val)
{
	sage_impl->SetUniform(name, val.x, val.y, val.z);
}

void SageShader::SetUniform(const char* name,  ToastBox::Vec4 const& val)
{
	sage_impl->SetUniform(name, val.x, val.y, val.z, val.w);
}

// Uniform setter - Matrices - glm

void SageShader::SetUniform(const char* name, const glm::mat2& val)
{
	return;

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
	return sage_impl->DeleteShaderProgram();
}

// Print Active Attributes in a neatly table format
void SageShader::PrintActiveAttribs() const
{

	sage_impl->PrintActiveAttribs();
}

void SageShader::PrintActiveUniforms() const
{
	sage_impl->PrintActiveUniform();
}

void SageShader::SetUniform(const char* name, const ToastBox::Matrix3x3& val)
{
	sage_impl->SetUniform(name, val);

}

void SageShader::SetUniform(const char* name, const ToastBox::Matrix4& val)
{
	sage_impl->SetUniform(name, val);
}



SageShader::~SageShader() = default;


















