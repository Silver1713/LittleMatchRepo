#pragma once

#ifndef SAGE_MODEL_MANAGER_HPP
#define SAGE_MODEL_MANAGER_HPP

#include "SageModel.hpp"
#include "SageRenderer.hpp"

enum PrimitiveShape {
	PRIMITIVE_SQUARE,
	PRIMITIVE_CIRCLE,
	PRIMITIVE_TRIANGLE,
	POLYGON,
	count
};

struct SageModelManager
{
	static std::map<std::string, SageModel> models;

	static SageModel& CreatePrimitiveModel(std::string name, PrimitiveShape shape, RENDER_TYPE type);
};

#endif