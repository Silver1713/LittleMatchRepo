#include "Systems/SageGraphicsSystem.hpp"

#include <iostream>
#include <ostream>
#include <GL/glew.h>

void SageGraphicsSystem::Init()
{
	
}

void SageGraphicsSystem::Update()
{
	
}

void SageGraphicsSystem::Exit()
{
	
}

System::SystemType SageGraphicsSystem::GetInstance()
{
	return System::SystemType::GRAPHICS;
}

SageGraphicsSystem::~SageGraphicsSystem()
{
	
}

void SageGraphicsSystem::Allocate_SSBO(unsigned id , unsigned size, unsigned& ssbo_handle)
{

	glCreateBuffers(size, &ssbo_handle);
	glNamedBufferData(ssbo_handle, size, nullptr, GL_DYNAMIC_DRAW);
	ssbo_data[id] = ssbo_handle;


}

void SageGraphicsSystem::Reallocate_SSBO(unsigned id, size_t new_capacity)
{
    int size;
    glGetNamedBufferParameteriv(ssbo_data[id], GL_BUFFER_SIZE, &size);
    if (size == 0) {
        
        return;
    }

	if (size > new_capacity)
	{
		std::cerr << "New capacity is less than the current capacity" << std::endl;
		return;
	}
	unsigned& ssbo_handle = ssbo_data[id];
    void* data = reinterpret_cast<void*>(new char[size]);  // Allocate memory to hold the data
    glGetNamedBufferSubData(ssbo_handle, 0, size, data);

	// Delete the old buffer
	glDeleteBuffers(1, &ssbo_handle);


    glCreateBuffers(1, &ssbo_handle);
    glNamedBufferData(ssbo_handle, new_capacity, data, GL_DYNAMIC_DRAW);

    // Clean up allocated memory
	char* data_char = reinterpret_cast<char*>(data);
	delete[] data_char;
}

void SageGraphicsSystem::SSBO_SubData(unsigned id, unsigned offset, unsigned size, void* data)
{
	glNamedBufferSubData(id, offset, size, data);
}


void SageGraphicsSystem::Append_SSBO(unsigned id, unsigned offset, unsigned data_size, void* data)
{
	unsigned& ssbo_handle = ssbo_data[id];
	int size;
	glGetNamedBufferParameteriv(ssbo_handle, GL_BUFFER_SIZE, &size);
	if (size == 0)
	{
		std::cerr << "Buffer is empty" << std::endl;
		return;
	}
	if (size < offset + data_size)
	{
		std::cerr << "Buffer is too small" << std::endl;
		return;
	}
	glNamedBufferSubData(ssbo_handle, offset, data_size, data);
}




void SageGraphicsSystem::SSBO_Delete(unsigned& id)
{
	glDeleteBuffers(1, &ssbo_data[id]);
	ssbo_data.erase(id);
}





