#include <map>
#include <iostream>

#include "SageModelManager.hpp"
#include "SageObjectManager.hpp"
#include "SageShaderManager.hpp"

std::map<std::string, SageObject> SageObjectManager::objects{};

SageObject& SageObjectManager::Create_Primitive_Object(char const* _name, PrimitiveObject OBJ_SHAPE)
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

		obj.Init(_name, &SageModelManager::models["PRIMITIVE_RECT"]);

		obj.transform = {};

		objects[_name] = obj;

		return objects[_name];
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

		obj.Init(_name, &SageModelManager::models["PRIMITIVE_CIRCLE"]);
		obj.transform = {};

		objects[_name] = obj;

		return objects[_name];
	}
	else
	{
		std::cerr << "Error: Shape not supported." << '\n';
		std::exit(EXIT_FAILURE);
	}
}

SageObject& SageObjectManager::Create_Primitive_Object(char const* _name, PrimitiveObject _OBJ_SHAPE, glm::vec2 position, glm::vec2 _scale, glm::vec2 _orientation, glm::vec4 _color, glm::vec4 _border_color, float _border_width, float _border_radius)
{
	SageObject obj;
	if (_OBJ_SHAPE == PRIMITIVE_OBJECT_RECT)
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

		obj.Init(_name, &SageModelManager::models["PRIMITIVE_RECT"]);

		obj.transform.position = position;
		obj.transform.scale = _scale;
		obj.transform.orientation = _orientation;

		obj.GetMaterial().color = _color;
		obj.GetMaterial().border_color = _border_color;
		obj.GetMaterial().border_width = _border_width;
		obj.GetMaterial().border_radius = _border_radius;

		objects[_name] = obj;

		return objects[_name];
	}

	else if (_OBJ_SHAPE == PRIMITIVE_OBJECT_CIRCLE)
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

		obj.Init(_name, &SageModelManager::models["PRIMITIVE_CIRCLE"]);

		obj.transform.position = position;
		obj.transform.scale = _scale;
		obj.transform.orientation = _orientation;

		obj.GetMaterial().color = _color;
		obj.GetMaterial().border_color = _border_color;
		obj.GetMaterial().border_width = _border_width;
		obj.GetMaterial().border_radius = _border_radius;
		

		objects[_name] = obj;

		return objects[_name];
	}
	else
	{
		std::cerr << "Error: Shape not supported." << '\n';
		std::exit(EXIT_FAILURE);
	}
}


void SageObjectManager::Destroy_All_Objects()
{
	objects.clear();
}

SageLine SageObjectManager::Create_Line_Object(char const* name, glm::vec2 start, glm::vec2 end, glm::vec4 color, float width)
{
	(name);
	if (SageModelManager::models.find("PRIMITIVE_LINE") == SageModelManager::models.end())
	{
		SageModelManager::CreatePrimitiveModel("PRIMITIVE_LINE", static_cast<int>(PrimitiveShape::PRIMITIVE_LINE), static_cast<int>(RENDER_TYPE::TYPE_LINES));
		SageModelManager::models["PRIMITIVE_LINE"].setup_gpu_buffer();
	}

	SageLine line(start, end, color, width);
	line.line = &SageModelManager::models["PRIMITIVE_LINE"];
	
	line.Calculate_Matrix();


	return line;
}










