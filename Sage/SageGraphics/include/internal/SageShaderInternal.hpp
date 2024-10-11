/* Start Header ************************************************************************/
/*!
\file		SageShader.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The private interface containing the SageShader class containing methods and attributes
			to manage shader programs, compiling and linking of the shader programs.This class
			calls and implement the API provided by the GLFW libraries and the OpenGL API.

			This allow shader rpogram to be created, compiled and linked in the GPU.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#ifndef SAGE_SHADER_INTERNAL_HPP
#define SAGE_SHADER_INTERNAL_HPP
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>


/*!*****************************************************************************
	\brief
		Encapsulate a intenal shader object in the rendering engine.

		This shader class encapsulate the private class used in the
		rendering engine. It provides methods to compile, link and validate
		the shader program. It also provides methods to send the uniform
		data to the shader program.
*******************************************************************************/
class SageShaderInternal
{
private:
	unsigned int pgm_handle; //!< Program handle
	bool is_linked; //!< Is the program linked
	std::string log_string; //!< Shader program logs.

	bool loaded; //!< Is the shader program loaded

public:
	/*!*****************************************************************************
		\brief
			This enums class represent the list of possible shader type that can
			be compiled and linked in the rendering engine.
	*******************************************************************************/
	enum class SAGE_INTERNAL_SHADER_TYPE
	{
		S_INTERNAL_VERTEX_SHADER, //!< Vertex Shader
		S_INTERNAL_FRAGMENT_SHADER, //!< Fragment Shader
		S_INTERNAL_GEOMETRY_SHADER, //!< Geometry Shader
		S_INTERNAL_TESS_CONTROL_SHADER, //!< Tessellation Control Shader
		S_INTERNAL_TESS_EVALUATION_SHADER, //!< Tessellation Evaluation Shader
		S_INTERNAL_COMPUTE_SHADER,	//!< Compute Shader
		S_INTERNAL_count //!< number of shader types
	};
	/*!*****************************************************************************
	\brief
		The default constructor for the internal shader object.

		This constructor initialize the shader object to a safe state.
	*******************************************************************************/
	SageShaderInternal();
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
	GLboolean Compile_From_String(SAGE_INTERNAL_SHADER_TYPE shader_type, std::string const& source, std::string const& path = "");
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
	GLboolean Compile_From_File(SAGE_INTERNAL_SHADER_TYPE shader_type, std::string const& file_name);


	/*!*****************************************************************************
	\brief
		Link the shader program.

		This function will link the shader program. The function will return true
		if there are no errors during the linking process.

	\return
		True if the shader program is linked successfully, false otherwise.
	*******************************************************************************/
	GLboolean Link();

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
	GLboolean Validate();

	//Compile Link and Validate
	GLboolean Compile_Link_Validate(SAGE_INTERNAL_SHADER_TYPE shader_type, std::string const& source);

	/*!*****************************************************************************
	\brief
		Get program handle

		This function will get the program handle from OpenGL for the
		shader program.
	\return
		The program handle for the shader program.
	*******************************************************************************/
	GLuint Get_Program_Handle() const;
	/*!*****************************************************************************
	\brief
		Check if the shader program is linked.

		This function will return true if the shader program is linked and false
		otherwise.
	\return
		True if the shader program is linked, false otherwise.
	*******************************************************************************/
	GLboolean IsLinked() const;
	/*!*****************************************************************************
	\brief
		Check if the shader object holds a shader program.

		This function make sure that the shader program handle is not less than or
		equal to zero. This ensure that the shader program is loaded into the GPU,
		allowing for linking, validation and activation.
	\return
		True if the program handle is not less than 0 else false.
	*******************************************************************************/
	GLboolean is_loaded() const;
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
		Manually bind a vertex attribute location to a given index used in the
		shader program.

		This function will bind a vertex attribute location to a given index. This
		function is used oto manually bind the vertex attribute location to a given
		attrib index.
	\param inde
		The index to bind the vertex attribute location to.
	\param name
		The name of the vertex attribute location.
	*******************************************************************************/
	void Bind_Vertex_Attrib_Location(GLuint index, const char* name);
	/*!*****************************************************************************
	\brief
		Manually bind a fragment attribute location to a given index used in the
		shader program.

		This function will bind a fragment attribute location to a given index. This
		function is used to manually bind the fragment attribute location to a given
		attrib index.
	\param inde
		The index to bind the fragment attribute location to.
	\param name
		The name of the fragment attribute location.
	*******************************************************************************/
	void Bind_Frag_Attrib_Location(GLuint index, const char* name);
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
	GLint GetUniformLocation(const char* name, bool exit_on_error = false) const;
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
	s*******************************************************************************/
	void Set_Uniform(const char* name, GLint val);
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
	void Set_Uniform(const char* name, GLfloat val);
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
	void Set_Uniform(const char* name, GLdouble val);
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
	void Set_Uniform(const char* name, GLboolean val);
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
	void Set_Uniform(const char* name, GLfloat x, GLfloat y);
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
	void Set_Uniform(const char* name, GLfloat x, GLfloat y, GLfloat z);
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
	void Set_Uniform(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	//Vector - glm
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
	void Set_Uniform(const char* name, const glm::vec2& val);
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
	void Set_Uniform(const char* name, const glm::vec3& val);
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
	void Set_Uniform(const char* name, const glm::vec4& val);

	// Uniform Matrices
	/*!*****************************************************************************
	\brief
		Set uniform of 2x2 matrix  with the given name and value.

		This function retrieve the location of the uniform and send a 3x3 matrix
		to the GPU

	\param name
		The name of the uniform
	\param val
		The 2x2 matrix.
	*******************************************************************************/
	void Set_Uniform(const char* name, const glm::mat2& val);
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
	void Set_Uniform(const char* name, const glm::mat3& val);
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
	void Set_Uniform(const char* name, const glm::mat4& val);

	/*!*****************************************************************************
	\brief
	Set uniform of 3x3 matrix  with the given name and value. The 3x3 matrix
	is given as a pointer to an array.

	This function retrieve the location of the uniform and send a pointer to the
	the array representing the 3x3 matrix.


	\param name
		The name of the uniform
	\param data
		Pointer to the array representing the 3x3 matrix.
	*******************************************************************************/
	void Set_Uniform_3f_m(const char* name, float* data);
	/*!*****************************************************************************
	\brief
	Set uniform of 3x3 matrix  with the given name and value. The 3x3 matrix
	is given as a pointer to an array.

	This function retrieve the location of the uniform and send a pointer to the
	the array representing the 3x3 matrix.

	This is the const-overloaded function that allow a const value to be passed
	to the uniform in the GPU


	\param name
		The name of the uniform
	\param data
		Pointer to the array representing the 3x3 matrix.
	*******************************************************************************/
	void Set_Uniform_3f_m(const char* name, const float* data) const;
	/*!*****************************************************************************
	\brief
	Set uniform of 4x4 matrix  with the given name and value. The 3x3 matrix
	is given as a pointer to an array.

	This function retrieve the location of the uniform and send a pointer to the
	the array representing the 3x3 matrix.


	\param name
		The name of the uniform
	\param data
		Pointer to the array representing the 4x4 matrix.
	*******************************************************************************/
	void Set_Uniform_4f_m(const char* name, float* data);

	/*!*****************************************************************************
	\brief
	Set uniform of 4x4 matrix  with the given name and value. The 3x3 matrix
	is given as a pointer to an array.

	This function retrieve the location of the uniform and send a pointer to the
	the array representing the 3x3 matrix.

	This is the const-overloaded function that allow a const value to be passed
	to the uniform in the GPU

	\param name
		The name of the uniform
	\param data
		Pointer to the array representing the 4x4 matrix.
	*******************************************************************************/
	void Set_Uniform_4f_m(const char* name, const float* data) const;


	/*!*****************************************************************************
	\brief
	Print all the active attributes currently bind to the shader program,
	to the output stream.
	*******************************************************************************/
	void Print_Active_Attribs() const;
	/*!*****************************************************************************
	\brief
	Print all the active uniform that the shader program used, to the output
	stream.
	*******************************************************************************/
	void PrintActiveUniforms() const;

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


	/*!*****************************************************************************
	\brief
		The destructor for the shader object.

		This destructor cleans up the shader object by deleting the shader program
		when the object is destroyed or goes out of scope.
	*******************************************************************************/
	~SageShaderInternal();



};



#endif
