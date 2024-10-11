/* Start Header ************************************************************************/
/*!
\file		SageObject.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The header file containing the declaration of the object class
			that define the properties of the objects which is to be used
			when rendering to the game world.



			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#ifndef SageObject_HPP
#define SageObject_HPP
#include <string>
#include <GL/glew.h>

#include "SageModel.hpp"
#include "SageViewport.hpp"
#include "SageShader.hpp"
#include "SageTexture.h"
class SageCamera; // Forward Declaration
class SageModel;
/*!*****************************************************************************
	\brief
		Encapsulate the OpenGL object.

		This class represent the openGL object. It contain functions and
		and algorithm used to create and modify and draw the object.
*******************************************************************************/
class SageObject
{
public:
	/*!*****************************************************************************
	\brief
		Represent the transformation of the object.

		This struct represent the transformation of the object. It contain the
		position, orientation and scale of the object.
	*******************************************************************************/

	struct SageTransform2D 
	{
		SageTransform2D() : position(0.f), orientation(0.f), scale(1.f), model_matrix() {}

		glm::vec2 position; //!< position of the object
		glm::vec2 orientation; //!< orientation of the object
		glm::vec2 scale; //!< scale of the object

		glm::mat3x3 model_matrix; //!< model matrix of the object

		/*!*****************************************************************************
		\brief
			Calculate the model matrix of the object.
		*******************************************************************************/
		glm::mat3x3 Calculate_Model_Matrix();

	};

	/*!*****************************************************************************
	\brief
		Entity mesh data.
	*******************************************************************************/
	struct SageMesh
	{
		//!< Vertex and index count
		size_t vtx_cnt, idx_cnt;
		SageModel* model_ref; //!< pointer to the model
	};
	/*!*****************************************************************************
	\brief Encapsulate the material of the object.
	*******************************************************************************/
	struct SageMaterial
	{
		glm::vec4 color; //!< color of the object
		glm::vec4 border_color; //!< border color of the object


		bool enable_texture; //!< enable texture
		bool enable_vertex_color; //!< enable vertex color
		bool enable_border_color; //!< enable border color

		float border_width; //!< border width
		float border_radius; //!< border radius

		SageShader* shader_ref; //!< Pointer to the shader
		SageTexture* texture_ref; //!< Pointer to the texture

		float mat_transparency{ 1 }; //!< 1 : opaque, 0 : transparent
	};
private:
	GLuint object_id; //!< Object ID
	std::string object_name; //!< Object name


	bool is_enabled; //!< Is object enabled

	



public:
	/*!*****************************************************************************
	\brief Default Constructor, create a object with default value.
	*******************************************************************************/
	SageObject();
	/*!*****************************************************************************
	\brief Initialize the object with the given name and model.
	\param name
		Name of the object.
	\param model
		Model of the object.
	*******************************************************************************/
	void Init(char const* _name, SageModel* _model);
	/*!*****************************************************************************
	\brief Update the object, calculating the model matrix.
	
	*******************************************************************************/
	void Update();
	/*!*****************************************************************************
	\brief Draw the object using viewport space.

	*******************************************************************************/
	void Draw(SageViewport* _vp);
	/*!*****************************************************************************
	\brief Draw the object using world space.

	*******************************************************************************/
	void Draw(SageCamera* _cam);
	/*!*****************************************************************************
	\brief Attach a texture to the object.
	\param _texture
		Texture to be attached.
	*******************************************************************************/
	void Attach_Texture(SageTexture* _texture);
	//Camera;


	SageTransform2D transform; //!< Transformation of the object
	SageMaterial material; //!< Material of the object
	SageMesh obj_mesh; //!< Mesh of the object
	static long int object_count; //!< Object count
	static long int current_object_count; //!< Current object count

	/*!*****************************************************************************
	\brief Get the material of the object.

	*******************************************************************************/
	SageMaterial& GetMaterial(); 
	/*!*****************************************************************************
	\brief Set the visibility of the object.
	\param _transparency
		0: Transparent, 1: Opaque
	*******************************************************************************/
	void Set_Alpha(float _transparency); // 0: Transparent, 1: Opaque
	/*!*****************************************************************************
	\brief Disable the object.
	*******************************************************************************/
	void Disable_Object();

	

};


#endif // SageObject_HPP