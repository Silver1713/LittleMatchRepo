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

/*!*****************************************************************************
	\brief
		Encapsulate a shader object in the rendering engine.

		This shader class encapsulate a shader program to be used in the
		rendering engine. It provides methods to compile, link and validate
		the shader program. It also provides methods to send the uniform
		data to the shader program.
*******************************************************************************/
class SageShader
{
	class SageShaderInternalImpl; //!< Forward declaration of the implementation class
	std::unique_ptr<SageShaderInternalImpl> sage_impl; //!< Pointer to the implementation class

	unsigned int pgm_handle; //!< Program handle
	bool is_linked; //!< Is the program linked
	std::string log_string; //!< Shader program logs.

public:
	/*!*****************************************************************************
		\brief
			This enums class represent the list of possible shader type that cna
			be compiled and linked in the rendering engine.
	*******************************************************************************/
	enum class SAGE_SHADER_TYPE
	{
		SAGE_VERTEX_SHADER, //!< Vertex shader
		SAGE_FRAGMENT_SHADER, //!< Fragment shader
		SAGE_GEOMETRY_SHADER, //!< Geometry shader
		SAGE_TESS_CONTROL_SHADER, //!< Tessellation control shader
		SAGE_TESS_EVALUATION_SHADER, //!< Tessellation evaluation shader
		SAGE_COMPUTE_SHADER,//!< Compute shader
		SAGE_SHADER_count // number of shader types
	};
	/*!*****************************************************************************
	\brief
		The default constructor for the shader object.

		This constructor initialize the shader object to a safe state.
	*******************************************************************************/
	SageShader();
	/*!*****************************************************************************
	\brief
		The destructor for the shader object.

		This destructor cleans up the shader object by deleting the shader program
		when the object is destroyed or goes out of scope.
	*******************************************************************************/
	~SageShader();
	/*!*****************************************************************************
	\brief
	The copy constructor for the shader object.

	The copy constructor is a deleted function to prevent copying of the shader
	using the copy constructor. Instead, the shader object can be moved using the
	move constructor which allows the transfer of ownership of the implementation
	class to another shader object. This is to prevent the duplication of the
	shader program in the rendering engine.

	\param other
		The shader object to be copied from.
	*******************************************************************************/
	SageShader(const SageShader&) = delete;
	/*!*****************************************************************************
	\brief
	The copy assignment  for the shader object.

	The copy assignment  is a deleted function to prevent copying of the shader
	using the copy assignment . Instead, the shader object can be moved using the
	move assignment  which allows the transfer of ownership of the implementation
	class to another shader object. This is to prevent the duplication of the
	shader program in the rendering engine.

	\param other
		The shader object to be copied from.
	*******************************************************************************/
	SageShader& operator=(const SageShader&) = delete;

	/*!*****************************************************************************
	\brief
		The move constructor for the shader object.

		The move constructor will move the ownership of the pointer to the implementation class
		from the input shader object to the current shader object. This allows the transfer
		of the shader program to another shader object without duplicating the
		shader program.
	\note This function do not expect any exceptions to be thrown.
	\param other
		The shader object to be moved from.
	*******************************************************************************/
	SageShader(SageShader&& other) noexcept;
	/*!*****************************************************************************
	\brief
		The move assignment for the shader object.

		The move assignment function will move the ownership of the pointer to the implementation class
		from the input shader object to the current shader object. This allows the transfer
		of the shader program to another shader object without duplicating the
		shader program.
	\note This function do not expect any exceptions to be thrown.
	\param other
		The shader object to be moved from.
	*******************************************************************************/
	SageShader& operator=(SageShader&& other) noexcept;


	/*!*****************************************************************************
	\brief
		Compile a shader object from a string.

		This function will compile a shader object from a string. The shader type
		determines the type of shader to be compiled. The source string contains
		the GLSL code for the shader program. The path is optional and is only
		for logging purposes when compiled with a file.

	\param shader_type
		The type of shader to be compiled.
	\param source
			The GLSL code for the shader program.
	\param path
		The path to the file containing the shader code. Default is an empty string.
	\return
			True if the shader is compiled successfully, false otherwise.

	*******************************************************************************/
	bool Compile_From_String(SAGE_SHADER_TYPE shader_type, std::string const& source, std::string const& path = "");
	/*!*****************************************************************************
	\brief
		Compile a shader object from a file.

		This function will compile a shader object from a file. The shader type
		determines the type of shader to be compiled. The file name contains
		the path to the file containing the GLSL code for the shader program.

	\param shader_type
		The type of shader to be compiled.
	\param file_name
		The path to the file containing the shader code. Default is an empty string.
	\return
		True if the shader is compiled successfully, false otherwise.

	*******************************************************************************/
	bool Compile_From_File(SAGE_SHADER_TYPE shader_type, std::string const& file_name);



	/*!*****************************************************************************
	\brief
		Link the shader program.

		This function will link the shader program. The function will return true
		if there are no errors during the linking process.

	\return
		True if the shader program is linked successfully, false otherwise.
	*******************************************************************************/
	bool Link();

	/*!*****************************************************************************
	\brief
		Activate the shader program.

		This function will activate the shader program for rendering. Once activated
		data can be sent to the shader program using the uniform functions. This modifies
		how objects are rendered in the rendering engine.

	\note A shader program must be activated before rendering objects in the
	rendering engine.
	*******************************************************************************/
	void Activate();
	/*!*****************************************************************************
	\brief
		Deactivate the shader program.

		This function will deactivate the shader program for rendering. Once it is
		deactivated, the shader program will be unbound from the rendering engine.
	*******************************************************************************/
	void Deactivate();
	/*!*****************************************************************************
	\brief
		Validate the shader program.

		This function will check if a shader program is valid. It will return true
		if it is valid and false otherwise.
	\return
		True if the shader program is valid, false otherwise.
	*******************************************************************************/
	bool Validate();

	//Compile Link and Validate
	bool Compile_Link_Validate(SAGE_SHADER_TYPE shader_type, std::string const& source);


	/*!*****************************************************************************
	\brief
		Get program handle

		This function will get the program handle from OpenGL for the
		shader program.
	\return
		The program handle for the shader program.
	*******************************************************************************/
	unsigned int Get_Program_Handle();
	/*!*****************************************************************************
	\brief
		Check if the shader program is linked.

		This function will return true if the shader program is linked and false
		otherwise.
	\return
		True if the shader program is linked, false otherwise.
	*******************************************************************************/
	bool Is_Linked() const;
	/*!*****************************************************************************
	\brief
		Get the shader program logs.

		This function retrieve the program logs from the shader program. The logs
		details any errors that occur during the compilation and linking of the
		shader program.
	\return
		The shader program logs.
	*******************************************************************************/
	std::string Get_Log() const;

	/*!*****************************************************************************
	\brief
		Get the uniform location of a variable in the shader program.

		This function will retrieve the uniform location of a
		variable in the shader. The location of the variable is used to
		send data to the shader program.
	\param name
		The name of the uniform.
	\param exit_on_error
		Determines if application should exit, when an invalid location is retrieved.

	\return
		An integer representing the uniform location of the variable.
	*******************************************************************************/
	int Get_Uniform_Location(const char* name, bool exit_on_error = false);

	/*!*****************************************************************************
	\brief
		Get the uniform location of a variable in the shader program.

		This function will retrieve the uniform location of a
		variable in the shader. The location of the variable is used to
		send data to the shader program.

	\param name
		The name of the unifrom
	\param val
		The value to be send to the GPU.
	*******************************************************************************/
	void Set_Uniform(const char* name, int val);
	/*!*****************************************************************************
	\brief
		Set uniform of type float with the given name and value.

		This function retrieve the location of the uniform and send float data of the
		to the uniform of the given name that is of a float type.

	\param name
		The name of the unifrom
	\param val
		The value to be send to the GPU.
	*******************************************************************************/

	void Set_Uniform(const char* name, float val);
	/*!*****************************************************************************
	\brief
		Set uniform of type double with the given name and value.

		This function retrieve the location of the uniform and send double data of the
		to the uniform of the given name that is of a double type.

	\param name
		The name of the unifrom
	\param val
		The value to be send to the GPU.
	*******************************************************************************/
	void Set_Uniform(const char* name, double val);
	/*!*****************************************************************************
	\brief
		Set uniform of type integer with the given name and value.

		This function retrieve the location of the uniform and send a integer
		data of the uniform of the given name that is of a integer.
	\param name
		The name of the uniform.
	\param val
		The value to be send to the GPU.
	*******************************************************************************/
	void Set_Uniform(const char* name, bool val);

	//Vectors - Singular
	/*!*****************************************************************************
	\brief
		Set uniform of type 2d vector  with the given name and value.

		This function retrieve the location of the uniform and send 2 float data
		representing the x and y value of a 2d vector.

	\param name
		The name of the uniform
	\param x
		The x value of the vector.
	\param y
		The y value of the vector.
	*******************************************************************************/
	void Set_Uniform(const char* name, float x, float y);
	/*!*****************************************************************************
	\brief
		Set uniform of type 3d vector  with the given name and value.

		This function retrieve the location of the uniform and send 2 float data
		representing the x, y and z value of a 2d vector.

	\param name
		The name of the uniform
	\param x
		The x value of the vector.
	\param y
		The y value of the vector.
	\param z
		The z value of the vector.
	*******************************************************************************/
	void Set_Uniform(const char* name, float x, float y, float z);
	/*!*****************************************************************************
	\brief
		Set uniform of type 4d vector  with the given name and value.

		This function retrieve the location of the uniform and send 2 float data
		representing the x, y, z and w value of a 2d vector.

	\param name
		The name of the uniform
	\param x
		The x value of the vector.
	\param y
		The y value of the vector.
	\param z
		The z value of the vector.
	\param w
		The w value of the vector.
	*******************************************************************************/
	void Set_Uniform(const char* name, float x, float y, float z, float w);

	/*!*****************************************************************************
	\brief
		Set uniform of type 2d vector  with the given name and value.

		This function retrieve the location of the uniform and send a 2d vector
		to the GPU

	\param name
		The name of the uniform
	\param val
		The 2D Vector.
	*******************************************************************************/
	void Set_Uniform(const char* name, ToastBox::Vec2 const& val);
	/*!*****************************************************************************
	\brief
		Set uniform of type 3d vector  with the given name and value.

		This function retrieve the location of the uniform and send a 3d vector
		to the GPU

	\param name
		The name of the uniform
	\param val
		The 3D Vector.
	*******************************************************************************/
	void Set_Uniform(const char* name, ToastBox::Vec3 const& val);
	/*!*****************************************************************************
	\brief
		Set uniform of type 4d vector  with the given name and value.

		This function retrieve the location of the uniform and send a 4d vector
		to the GPU

	\param name
		The name of the uniform
	\param val
		The 4D Vector.
	*******************************************************************************/
	void Set_Uniform(const char* name, ToastBox::Vec4 const& val);

	// Uniform Matrices


	void Set_Uniform(const char* name, const glm::mat2& val);
	void Set_Uniform(const char* name, const glm::mat3& val);
	void Set_Uniform(const char* name, const glm::mat4& val);
	/*!*****************************************************************************
	\brief
		Set uniform of 3x3 matrix  with the given name and value.

		This function retrieve the location of the uniform and send a 3x3 matrix
		to the GPU

	\param name
		The name of the uniform
	\param val
		The 3x3 matrix.
	*******************************************************************************/
	void Set_Uniform(const char* name, const ToastBox::Matrix3x3& val);
	/*!*****************************************************************************
	\brief
	Set uniform of 4x4 matrix  with the given name and value.

	This function retrieve the location of the uniform and send a 4x4 matrix
	to the GPU

	\param name
		The name of the uniform
	\param val
		The 4x4 matrix.
	*******************************************************************************/
	void Set_Uniform(const char* name, const ToastBox::Matrix4& val);



	void Print_Active_Attribs() const;

	void Print_Active_Uniforms() const;

	// Helper Functions
	/*!*****************************************************************************
	\brief
		Check if a given file exist.

		This helper function take in a file path and check if the given file exist
		in the system.
	\param _file_name
		The path to the file.
	\return
		True, if the file exist else, false.
	*******************************************************************************/
	bool File_Exists(const std::string& file_name);

	/*!*****************************************************************************
	\brief
		Delete the current shader program

		This function delete the shader program compiled and linked in the GPU. This
		deactivate and terminate the shader program and free memory to the GPU.
	\return
		True, if deletion is successful else false.
	*******************************************************************************/
	bool Delete_Shader_Program();
};
#endif
