/* Start Header ************************************************************************/
/*!
\file		SageModelManager.hpp
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		The declaration of function to create sage models for rendering

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#pragma once

#ifndef SAGE_MODEL_MANAGER_HPP
#define SAGE_MODEL_MANAGER_HPP

#include "SageModel.hpp"
#include "SageRenderer.hpp"

enum class PrimitiveShape {
	PRIMITIVE_SQUARE,
	PRIMITIVE_CIRCLE,
	PRIMITIVE_TRIANGLE,
	PRIMITIVE_LINE,
	PRIMITIVE_POINTS,
	POLYGON,
	count
};

struct SageModelManager
{
	static std::map<std::string, SageModel> models;

	/*!*****************************************************************************
		\brief
			Gets the texture with the provided ID

		\param _name
			The name of the model

		\param _shape
			The shape of the model

		\param _type
			The render type of the model

		\return
			A reference to SageModel
	*******************************************************************************/
	static SageModel& CreatePrimitiveModel(std::string _name, int _shape, int _type);
	
};

#endif