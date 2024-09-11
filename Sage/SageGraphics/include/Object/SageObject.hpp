#ifndef SageObject_HPP
#define SageObject_HPP
#include <string>
#include <GL/glew.h>

#include "SageModel.hpp"
#include "SageViewport.hpp"
#include "SageShader.hpp"

class SageModel;
class SageObject
{
public:
	struct SageTransform2D
	{
		SageTransform2D() : position(0.f), orientation(0.f), scale(1.f), model_matrix() {}

		glm::vec2 position;
		glm::vec2 orientation;
		glm::vec2 scale;

		glm::mat3x3 model_matrix;


		glm::mat3x3 calculate_model_matrix();



	};
	struct SageMesh
	{
		size_t vtx_cnt, idx_cnt;
		SageModel* model_ref;
	};

	struct SageMaterial
	{
		glm::vec4 color;
		glm::vec4 border_color;


		bool enable_texture;
		bool enable_vertex_color;
		bool enable_border_color;

		float border_width;
		float border_radius;

		SageShader* shader_ref;
	};
private:
	GLuint object_id;
	std::string object_name;

	SageMesh obj_mesh;

	SageMaterial material;



public:
	SageObject();
	void init(char const* name, SageModel* model);
	void update();
	void draw(SageViewport* vp);
	//Camera;


	SageTransform2D transform;
	static long int object_count;
	static long int current_object_count;


	SageMaterial& GetMaterial();

};


#endif // SageObject_HPP