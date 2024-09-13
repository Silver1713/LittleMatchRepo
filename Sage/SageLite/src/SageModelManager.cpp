#include "SageModelManager.hpp"

#include <iostream>


std::map<std::string, SageModel> SageModelManager::models{};


SageModel& SageModelManager::CreatePrimitiveModel(std::string name, PrimitiveShape shape, RENDER_TYPE type)
{

	if (shape == PrimitiveShape::PRIMITIVE_SQUARE)
	{
		//Use ndc [-1,1] for square
		std::vector<glm::vec2> pos_vtx{
			glm::vec2(1.f,-1.f),
			glm::vec2(1.f,1.f),
			glm::vec2(-1.f,1.f),
			glm::vec2(-1.f,-1.f)
		};

		std::vector<glm::vec2> tex_vtx{
			glm::vec2(1.f,0.f),
			glm::vec2(1.f,1.f),
			glm::vec2(0.f,1.f),
			glm::vec2(0.f,0.f)
		};

		std::vector<glm::vec4> clr_vtx{
			glm::vec4(1.f,0.f,0.f,1.f),
			glm::vec4(0.f,1.f,0.f,1.f),
			glm::vec4(0.f,0.f,1.f,1.f),
			glm::vec4(1.f,1.f,1.f,1.f)
		};

		std::vector<GLushort> idx_vtx{
			0,1,2,
			2,3,0
		};

		SageModel mdl_square{ name.c_str(), &pos_vtx, &tex_vtx, &clr_vtx, &idx_vtx };
		mdl_square.set_render_type(type);
		mdl_square.set_shape_type(shape);

		

		// Add to the map
		models[name] = mdl_square;

		return models[name];

	}
	else
	{
		std::cerr << "Error: Shape not supported." << '\n';
		std::exit(EXIT_FAILURE);

	}

}
