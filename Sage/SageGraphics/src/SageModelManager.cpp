#include "SageModelManager.hpp"

#include <iostream>


std::map<std::string, SageModel> SageModelManager::models{};
float pi = static_cast<float>(std::atan(1) * 4);

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
			glm::vec2(0.f,0.f),
		};

		std::vector<glm::vec4> clr_vtx{
			glm::vec4(1.f,0.f,0.f,1.f),
			glm::vec4(0.f,1.f,0.f,1.f),
			glm::vec4(0.f,0.f,1.f,1.f),
			glm::vec4(1.f,1.f,1.f,1.f)
		};

		std::vector<GLushort> idx_vtx{
			2,3,0,
			0,1,2,
		};

		SageModel mdl_square{ name.c_str(), &pos_vtx, &tex_vtx, &clr_vtx, &idx_vtx };
		mdl_square.set_render_type(type);
		mdl_square.set_shape_type(shape);

		

		// Add to the map
		models[name] = mdl_square;

		return models[name];

	}

	// Use triangle fan for circle shape
	else if (shape == PrimitiveShape::PRIMITIVE_CIRCLE)
	{
		// default radius
		float radius = 50.0f;
		int slices = static_cast<int>(10.0f * sqrt(radius));
		float angle_step = 2.0f * pi / static_cast<float>(slices);

		// Vertex arrays
		std::vector<glm::vec2> pos_vtx;
		std::vector<glm::vec2> tex_vtx;
		std::vector<glm::vec4> clr_vtx;
		std::vector<GLushort> idx_vtx;

		pos_vtx.push_back(glm::vec2(0.0f, 0.f)); // Center pos
		tex_vtx.push_back(glm::vec2(0.5f, 0.5f)); // Tex coord
		clr_vtx.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		for (int i = 0; i <= slices; ++i)
		{
			float angle = i * angle_step;
			float x = std::cos(angle);
			float y = std::sin(angle);
			pos_vtx.push_back(glm::vec2(x, y));
			tex_vtx.push_back(glm::vec2(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle)));
			clr_vtx.push_back(glm::vec4(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle), 1.0f, 1.0f));
		}

		for (int j = 1; j <= slices; ++j)
		{
			idx_vtx.push_back(0); // Center vertex index
			idx_vtx.push_back(j); // Current vertex on perimeter
			idx_vtx.push_back(j + 1); // Next vertex on perimeter
		}

		// Last triangle 
		idx_vtx.push_back(0); // Center vertex
		idx_vtx.push_back(static_cast<GLushort>(slices)); // Last vertex
		idx_vtx.push_back(1); // First perimeter vertex to close the loop

		SageModel mdl_circle(name.c_str(), &pos_vtx, &tex_vtx, &clr_vtx, &idx_vtx);
		mdl_circle.set_render_type(type);
		mdl_circle.set_shape_type(shape);

		models[name] = mdl_circle;
		return models[name];

	}
	else
	{
		std::cerr << "Error: Shape not supported." << '\n';
		std::exit(EXIT_FAILURE);

	}

}
