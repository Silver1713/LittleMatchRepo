#include <map>
#include <iostream>

#include "SageModelManager.hpp"
#include "SageObjectManager.hpp"
#include "SageShaderManager.hpp"

std::map<std::string, SageObject> SageObjectManager::objects{};

SageObject& SageObjectManager::CreatePrimitiveObject(char const* name, PrimitiveObject OBJ_SHAPE)
{
	
	SageObject obj;
	if (OBJ_SHAPE == PRIMITIVE_OBJECT_RECT)
	{
		if (SageModelManager::models.find("PRIMITIVE_RECT") == SageModelManager::models.end())
		{
			SageModelManager::CreatePrimitiveModel("PRIMITIVE_RECT", static_cast<int>(PrimitiveShape::PRIMITIVE_SQUARE), static_cast<int>(RENDER_TYPE::TYPE_TRIANGLE));
		}

		SageModel& mdl = SageModelManager::models["PRIMITIVE_RECT"];


		mdl.setup_gpu_buffer();

		//Create base shader
		if (SageShaderManager::shaders.find("BASE_SHADER") == SageShaderManager::shaders.end()) {
			SageShader& shdr = SageShaderManager::search_and_create_shader_program("BASE_SHADER", "BaseVertexShader", "BaseFragmentShader");
			mdl.AssignShaderProgram(&shdr);
		}
		else
			mdl.AssignShaderProgram(&SageShaderManager::shaders["BASE_SHADER"]);

		obj.init(name, &SageModelManager::models["PRIMITIVE_RECT"]);

		obj.transform = {};

		objects[name] = obj;

		return objects[name];
	}

	if (OBJ_SHAPE == PRIMITIVE_OBJECT_CIRCLE)
	{
		if (SageModelManager::models.find("PRIMITIVE_CIRCLE") == SageModelManager::models.end())
		{
			SageModelManager::CreatePrimitiveModel("PRIMITIVE_CIRCLE", static_cast<int>(PrimitiveShape::PRIMITIVE_CIRCLE), static_cast<int>(RENDER_TYPE::TYPE_TRIANGLE_FAN));
		}

		SageModel& mdl = SageModelManager::models["PRIMITIVE_CIRCLE"];

		mdl.setup_gpu_buffer();

		if (SageShaderManager::shaders.find("BASE_SHADER") == SageShaderManager::shaders.end())
		{
			SageShader& shdr = SageShaderManager::search_and_create_shader_program("BASE_SHADER", "BaseVertexShader", "BaseFragmentShader");
			mdl.AssignShaderProgram(&shdr);
		}
		else
		{
			mdl.AssignShaderProgram(&SageShaderManager::shaders["BASE_SHADER"]);
		}

		obj.init(name, &SageModelManager::models["PRIMITIVE_CIRCLE"]);
		obj.transform = {};

		objects[name] = obj;

		return objects[name];
	}
	else
	{
		std::cerr << "Error: Shape not supported." << '\n';
		std::exit(EXIT_FAILURE);
	}
}

SageObject& SageObjectManager::CreatePrimitiveObject(char const* name, PrimitiveObject OBJ_SHAPE, glm::vec2 position, glm::vec2 scale, glm::vec2 orientation, glm::vec4 color, glm::vec4 borderColor, float borderWidth, float borderRadius)
{
	SageObject obj;
	if (OBJ_SHAPE == PRIMITIVE_OBJECT_RECT)
	{
		if (SageModelManager::models.find("PRIMITIVE_RECT") == SageModelManager::models.end())
		{
			SageModelManager::CreatePrimitiveModel("PRIMITIVE_RECT", static_cast<int>(PrimitiveShape::PRIMITIVE_SQUARE),static_cast<int>(RENDER_TYPE::TYPE_TRIANGLE));
		}

		SageModel& mdl = SageModelManager::models["PRIMITIVE_RECT"];


		mdl.setup_gpu_buffer();

		//Create base shader
		if (SageShaderManager::shaders.find("BASE_SHADER") == SageShaderManager::shaders.end()) {
			SageShader& shdr = SageShaderManager::CreateShaderProgram("BASE_SHADER", "../SageGraphics/shaders/BaseVertexShader.glsl", "../SageGraphics/shaders/BaseFragmentShader.glsl");
			mdl.AssignShaderProgram(&shdr);
		}
		else
			mdl.AssignShaderProgram(&SageShaderManager::shaders["BASE_SHADER"]);

		obj.init(name, &SageModelManager::models["PRIMITIVE_RECT"]);

		obj.transform.position = position;
		obj.transform.scale = scale;
		obj.transform.orientation = orientation;

		obj.GetMaterial().color = color;
		obj.GetMaterial().border_color = borderColor;
		obj.GetMaterial().border_width = borderWidth;
		obj.GetMaterial().border_radius = borderRadius;

		objects[name] = obj;

		return objects[name];
	}

	else if (OBJ_SHAPE == PRIMITIVE_OBJECT_CIRCLE)
	{
		if (SageModelManager::models.find("PRIMITIVE_CIRCLE") == SageModelManager::models.end())
		{
			SageModelManager::CreatePrimitiveModel("PRIMITIVE_CIRCLE", static_cast<int>(PrimitiveShape::PRIMITIVE_CIRCLE), static_cast<int>(RENDER_TYPE::TYPE_TRIANGLE_FAN));
		}

		SageModel& mdl = SageModelManager::models["PRIMITIVE_CIRCLE"];

		mdl.setup_gpu_buffer();

		if (SageShaderManager::shaders.find("BASE_SHADER") == SageShaderManager::shaders.end())
		{
			SageShader& shdr = SageShaderManager::search_and_create_shader_program("BASE_SHADER", "BaseVertexShader", "BaseFragmentShader");
			mdl.AssignShaderProgram(&shdr);
		}
		else
		{
			mdl.AssignShaderProgram(&SageShaderManager::shaders["BASE_SHADER"]);
		}

		obj.init(name, &SageModelManager::models["PRIMITIVE_CIRCLE"]);

		obj.transform.position = position;
		obj.transform.scale = scale;
		obj.transform.orientation = orientation;

		obj.GetMaterial().color = color;
		obj.GetMaterial().border_color = borderColor;
		obj.GetMaterial().border_width = borderWidth;
		obj.GetMaterial().border_radius = borderRadius;
		

		objects[name] = obj;

		return objects[name];
	}
	else
	{
		std::cerr << "Error: Shape not supported." << '\n';
		std::exit(EXIT_FAILURE);
	}
}


void SageObjectManager::DestroyAllObjects()
{
	objects.clear();
}

SageLine SageObjectManager::CreateLineObject(char const* name, glm::vec2 start, glm::vec2 end, glm::vec4 color, float width)
{
	(name);
	if (SageModelManager::models.find("PRIMITIVE_LINE") == SageModelManager::models.end())
	{
		SageModelManager::CreatePrimitiveModel("PRIMITIVE_LINE", static_cast<int>(PrimitiveShape::PRIMITIVE_LINE), static_cast<int>(RENDER_TYPE::TYPE_LINES));
		SageModelManager::models["PRIMITIVE_LINE"].setup_gpu_buffer();
	}

	SageLine line(start, end, color, width);
	line.line = &SageModelManager::models["PRIMITIVE_LINE"];
	
	line.calculate_matrix();


	return line;
}










