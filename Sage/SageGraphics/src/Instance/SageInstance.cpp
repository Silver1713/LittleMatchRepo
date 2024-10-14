#include "SageInstance.hpp"

#include <iostream>
#include <ostream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>




long long SageInstance::SSBO_SIZE = 10000; // Holds the around 10000 instances at max
void SageInstance::Set_SSBO_Size(unsigned int size)
{
	SSBO_SIZE = size;
}

void SageInstance::Setup_SSBO()
{
	// GL 4.5 and above
	glCreateBuffers(1, &SSBO_ID);
	glNamedBufferData(SSBO_ID, SSBO_SIZE * sizeof(InstanceData), NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBO_ID);


	
	
	
}

void SageInstance::Calculate_Model_Matrix()
{
	// Calculate the model matrix for each instance

	for (InstanceData& data : Instanced_SSBO)
	{
		glm::mat4 translation = glm::translate(glm::mat4(1.f), glm::vec3(data.position, 0.f));
		glm::mat4 rotation = glm::rotate(glm::mat4(1.f), data.orientation.x, glm::vec3(0, 0, 1));
		glm::mat4 scaling = glm::scale(glm::mat4(1.f), glm::vec3(data.scale, 1.f));

		data.model_matrix = (translation * rotation) * scaling;
	}
}



void SageInstance::Clear_SSBO()
{
	Instanced_SSBO.clear();
}


void SageInstance::Init(SageModel* mdl)
{
	model_ref = mdl;
	Instanced_SSBO = {};

	Setup_SSBO();

}

void SageInstance::Init(InstanceData* data, unsigned int size)
{
	Instanced_SSBO = { data, data + size };

}

void SageInstance::Init(std::initializer_list<InstanceData> const& data)
{
	Instanced_SSBO = { data.begin(), data.end() };
}



void SageInstance::Append_Instance(glm::vec2 position, glm::vec2 scale, glm::vec2 orientation, glm::vec4 color, float alpha)
{
	InstanceData data{};
	data.position = position;
	data.scale = scale;
	data.orientation = orientation;
	data.color = color;
	data.alpha = alpha;
	Instanced_SSBO.push_back(data);
}

//! New instance - Clear the previous instances and add new instances
void SageInstance::New_Instance(std::initializer_list<InstanceData> const& data)
{
	Instanced_SSBO.clear();
	Instanced_SSBO.insert(Instanced_SSBO.end(), data.begin(), data.end());
}


void SageInstance::Set_Model(SageModel* model)
{
	model_ref = model;
}


InstanceData& SageInstance::operator[](int index)
{
	return Instanced_SSBO[index];
}

 InstanceData const& SageInstance::operator[](int index) const
{
	 return Instanced_SSBO[index];
}



 void SageInstance::Load_Instance_To_GPU()
 {
	
	 glNamedBufferSubData(SSBO_ID, 0, Instanced_SSBO.size() * sizeof(InstanceData), Instanced_SSBO.data());
	// glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBO_ID);

 }

SageInstance::SageInstance(SageModel* mdl)
{
	model_ref = mdl;
	instance_count = 0;
	Instanced_SSBO = {};
	SSBO_ID = 0;
}

SageInstance::~SageInstance()
{
	glDeleteBuffers(1, &SSBO_ID);
	Instanced_SSBO.clear();

}

void SageInstance::Update()
{
	Calculate_Model_Matrix();
	
}

SageInstance::SageInstance(InstanceData* data, unsigned int size, SageModel* mdl)
{
	model_ref = mdl;
	instance_count = size;
	Instanced_SSBO = { data, data + size };
	SSBO_ID = 0;

	Calculate_Model_Matrix();
	Load_Instance_To_GPU();
}

SageInstance::SageInstance(std::initializer_list<InstanceData> const& data, SageModel* mdl)
{
	model_ref = mdl;
	instance_count = data.size();
	Instanced_SSBO = {data.begin(), data.end()};
	SSBO_ID = 0;

	Calculate_Model_Matrix();
	Load_Instance_To_GPU();

}



SageInstance::iterator SageInstance::begin()
{
	return Instanced_SSBO.begin();
}


SageInstance::iterator SageInstance::end()
{
	return Instanced_SSBO.end();
}


SageInstance::const_iterator SageInstance::cbegin() const
{
	return Instanced_SSBO.cbegin();
}

SageInstance::const_iterator SageInstance::cend() const
{
	return Instanced_SSBO.cend();
}

SageInstance::const_iterator SageInstance::begin() const
{
	return Instanced_SSBO.begin();
}


SageInstance::const_iterator SageInstance::end() const
{
	return Instanced_SSBO.end();
}



SageModel* SageInstance::Get_Model() const
{
	return model_ref;
}


int SageInstance::Get_Instance_Count() const
{
	
	return Instanced_SSBO.size();
}






