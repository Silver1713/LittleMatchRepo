/* Start Header ************************************************************************/
/*!
\file		SageModelManager.cpp
\title		Memory's Flame
\author		Neo Hui Zong, neo.h, 2301357 (100%)
\par		neo.h@digipen.edu
\date		27 September 2024
\brief		The definition of function to create sage models for rendering

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "SageModelManager.hpp"

#include <iostream>

std::map<std::string, SageModel> SageModelManager::models{};
float pi = static_cast<float>(std::atan(1) * 4);

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
SageModel& SageModelManager::CreatePrimitiveModel(std::string _name, int _shape, int _type)
{
	// For squares
	if (_shape == static_cast<int>(PrimitiveShape::PRIMITIVE_SQUARE))
	{
		//Use ndc [-1,1] for square
		std::vector<glm::vec2> pos_vtx{
			glm::vec2(.5f,-.5f),
			glm::vec2(.5f,.5f),
			glm::vec2(-.5f,.5f),
			glm::vec2(-.5f,-.5f)
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

		SageModel mdl_square{ _name.c_str(), &pos_vtx, &tex_vtx, &clr_vtx, &idx_vtx };
		mdl_square.Set_Render_Type(_type);
		mdl_square.Set_Shape_Type(_shape);

		

		// Add to the map
		models[_name] = mdl_square;

		return models[_name];

	}

	// For circles
	else if (_shape ==static_cast<int>(PrimitiveShape::PRIMITIVE_CIRCLE))
	{
		
		// default radius
		/*float radius = 8.f;*/
		int slices = 255;
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
			tex_vtx.push_back(glm::vec2(  0.5f * cos(angle),  0.5f * sin(angle)));
			clr_vtx.push_back(glm::vec4(0.5f * cos(angle),  0.5f * sin(angle), 1.0f, 1.0f));
		}

		for (int j = 1; j <= slices; ++j)
		{
			idx_vtx.push_back(0); // Center vertex index
			idx_vtx.push_back(static_cast<short>(j)); // Current vertex on perimeter
			idx_vtx.push_back(static_cast<short>(j+1)); // Next vertex on perimeter
		}

		// Last triangle 
		idx_vtx.push_back(0); // Center vertex
		idx_vtx.push_back(static_cast<GLushort>(slices)); // Last vertex
		idx_vtx.push_back(1); // First perimeter vertex to close the loop

		SageModel mdl_circle(_name.c_str(), &pos_vtx, &tex_vtx, &clr_vtx, &idx_vtx);
		mdl_circle.Set_Render_Type(_type);
		mdl_circle.Set_Shape_Type(_shape);

		models[_name] = mdl_circle;
		return models[_name];

	}

	// If lines
	else if (_shape == static_cast<int>(PrimitiveShape::PRIMITIVE_LINE))
	{
		std::vector<glm::vec2> pos_vtx{
			glm::vec2(-1.f,0.f),
			glm::vec2(1.f,0.f)
		};

		std::vector<glm::vec2> tex_vtx{
			glm::vec2(0.f,0.f),
			glm::vec2(1.f,0.f)
		};

		std::vector<glm::vec4> clr_vtx{
			glm::vec4(1.f,0.f,0.f,1.f),
			glm::vec4(0.f,1.f,0.f,1.f)
		};

		std::vector<GLushort> idx_vtx{
			0,1
		};

		SageModel mdl_line{ _name.c_str(), &pos_vtx, &tex_vtx, &clr_vtx, &idx_vtx };
		mdl_line.Set_Render_Type(_type);
		mdl_line.Set_Shape_Type(_shape);

		models[_name] = mdl_line;
		return models[_name];
	}

	// If points
	else if (_shape == static_cast<int>(PrimitiveShape::PRIMITIVE_POINTS))
	{
		std::vector<glm::vec2> pos_vtx{
			glm::vec2{0.f,0.f}
		};

		SageModel mdl_points{ _name.c_str(), &pos_vtx};
		mdl_points.Set_Render_Type(_type);
		mdl_points.Set_Shape_Type(_shape);

		models[_name] = mdl_points;
		return models[_name];
	}
	else
	{
		std::cerr << "Error: Shape not supported." << '\n';
		std::exit(EXIT_FAILURE);
	}
}

SageModel& SageModelManager::GetModel(std::string _name)
{
	if (models.contains(_name))
	{
		return models[_name];
	}
	std::cerr << "Error: Model not found." << '\n';
	std::exit(EXIT_FAILURE);
}



