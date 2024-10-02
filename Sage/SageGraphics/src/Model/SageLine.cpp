#include "SageLine.hpp"
#include "glm/ext/matrix_transform.hpp"


SageLine::SageLine() : start(), end(), color(), width(0), line(nullptr), transformation_matrix()
{
}


SageLine::SageLine(glm::vec2 start, glm::vec2 end, glm::vec4 color, float width)
{
	this->start = start;
	this->end = end;
	this->color = color;
	this->width = width;
	this->line = nullptr;
	this->transformation_matrix = glm::mat3(1.f);


}

void SageLine::calculate_matrix()
{
	

	transformation_matrix = { 1.f };
}


void SageLine::update()
{
	calculate_matrix();
	
}


void SageLine::update_dist(glm::vec2 _start, glm::vec2 _end)
{
	this->start = _start;
	this->end = _end;

	SageModel& model = *line;
	model.get_vertex_positions()[0] = _start;
	model.get_vertex_positions()[1] = _end;

	model.update_vtx_buffer_GPU();

}









