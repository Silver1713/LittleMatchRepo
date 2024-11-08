/* Start Header ************************************************************************/
/*!
\file		SageShader.cpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		This source file defines the public interface containing the SageShader class containing
			methods and attributes to manage shader programs, compiling and linking of the shader programs.
			Furthmore, this class expose methods from the internal class allowing calls to be
			delegated to the private interface.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
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
		return internal_impl->Compile_From_File(static_cast<SageShaderInternal::SAGE_INTERNAL_SHADER_TYPE>(type), path);
	}

	bool Compile_Raw_String(std::string const& source, SAGE_SHADER_TYPE type, std::string const& path)
	{
		return internal_impl->Compile_From_String(static_cast<SageShaderInternal::SAGE_INTERNAL_SHADER_TYPE>(type), source, path);
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
		return internal_impl->Get_Log();
	}

	unsigned int GetProgramID()
	{
		return internal_impl->Get_Program_Handle();

	}



	void PrintActiveAttribs()
	{
		internal_impl->Print_Active_Attribs();
	}

	void PrintActiveUniform()
	{
		internal_impl->PrintActiveUniforms();

	}

	bool DeleteShaderProgram()
	{
		return internal_impl->Delete_Shader_Program();

	}


	void SetUniform(const char* name, int const& val) const
	{
		internal_impl->Set_Uniform(name, val);
	}

	void SetUniform(const char* name, float const& val) const
	{
		internal_impl->Set_Uniform(name, val);
	}

	void SetUniform(const char* name, double const& val) const
	{
		internal_impl->Set_Uniform(name, val);
	}


	void SetUniform(const char* name, bool val) const
	{
		internal_impl->Set_Uniform(name, val);
	}

	void SetUniform(const char* name, float x, float y) const
	{
		internal_impl->Set_Uniform(name, x, y);
	}

	void SetUniform(const char* name, float x, float y, float z) const
	{
		internal_impl->Set_Uniform(name, x, y, z);
	}

	void SetUniform(const char* name, float x, float y, float z, float w) const
	{
		internal_impl->Set_Uniform(name, x, y, z, w);
	}

	void SetUniform(const char* name, const ToastBox::Matrix3x3& val) const
	{
		
		internal_impl->Set_Uniform_3f_m(name, val.data());
	}

	void SetUniform(const char* name, const ToastBox::Matrix4& val) const
	{
		internal_impl->Set_Uniform_4f_m(name, val.Data());
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



bool SageShader::Compile_From_String(SAGE_SHADER_TYPE shader_type, std::string const& source, std::string const& path)
{
	return sage_impl->Compile_Raw_String(source, shader_type, path);
}

bool SageShader::Compile_From_File(SAGE_SHADER_TYPE shader_type, std::string const& file_name)
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




unsigned int SageShader::Get_Program_Handle()
{
	pgm_handle = sage_impl->GetProgramID();
	return sage_impl->GetProgramID();
}

std::string SageShader::Get_Log() const
{
	return sage_impl->GetLog();
}

bool SageShader::Is_Linked() const
{
	return is_linked;
}



int SageShader::Get_Uniform_Location(const char* name, bool exit_on_error)
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

void SageShader::Set_Uniform(const char* name, int val)
{
	sage_impl->SetUniform(name, val);
}


void SageShader::Set_Uniform(const char* name, float val)
{
	sage_impl->SetUniform(name, val);
}

void SageShader::Set_Uniform(const char* name, double val)
{
	sage_impl->SetUniform(name, val);
}

void SageShader::Set_Uniform(const char* name, bool val)
{
	sage_impl->SetUniform(name, val);
}
// Uniform setter - Vector - Singular

void SageShader::Set_Uniform(const char* name, float x, float y)
{
	sage_impl->SetUniform(name, x, y);
}
void SageShader::Set_Uniform(const char* name, float x, float y, float z)
{
	sage_impl->SetUniform(name, x, y, z);

}

void SageShader::Set_Uniform(const char* name, float x, float y, float z, float w)
{
	sage_impl->SetUniform(name, x, y, z, w);
}

// Uniform setter - Vector - glm

void SageShader::Set_Uniform(const char* name, const ToastBox::Vec2& val)
{
	sage_impl->SetUniform(name, val.GetX(), val.GetY());
}

void SageShader::Set_Uniform(const char* name, const ToastBox::Vec3& val)
{
	sage_impl->SetUniform(name, val.x, val.y, val.z);
}

void SageShader::Set_Uniform(const char* name,  ToastBox::Vec4 const& val)
{
	sage_impl->SetUniform(name, val.x, val.y, val.z, val.w);
}

// Uniform setter - Matrices - glm

void SageShader::Set_Uniform(const char* name, const glm::mat3& val)
{
	GLint loc = Get_Uniform_Location(name);
	glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}
void SageShader::Set_Uniform(const char* name, const glm::mat4& val)
{
	GLint loc = Get_Uniform_Location(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}

// Helper Functions
bool SageShader::File_Exists(const std::string& file_name)
{
	std::ifstream file(file_name);
	return file.good();
}

bool SageShader::Delete_Shader_Program()
{
	return sage_impl->DeleteShaderProgram();
}

// Print Active Attributes in a neatly table format
void SageShader::Print_Active_Attribs() const
{

	sage_impl->PrintActiveAttribs();
}

void SageShader::Print_Active_Uniforms() const
{
	sage_impl->PrintActiveUniform();
}

void SageShader::Set_Uniform(const char* name, const ToastBox::Matrix3x3& val)
{
	sage_impl->SetUniform(name, val);

}

void SageShader::Set_Uniform(const char* name, const ToastBox::Matrix4& val)
{
	sage_impl->SetUniform(name, val);
}



SageShader::~SageShader() = default;


















