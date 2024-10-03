


#ifndef SageObject_HPP
#define SageObject_HPP
#include <string>
#include <GL/glew.h>

#include "SageModel.hpp"
#include "SageViewport.hpp"
#include "SageShader.hpp"
#include "SageTexture.h"
class SageCamera;
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


		glm::mat3x3 Calculate_Model_Matrix();

		


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
		SageTexture* texture_ref;

		float mat_transparency{ 1 }; // 1 : opaque, 0 : transparent
	};
private:
	GLuint object_id;
	std::string object_name;


	bool is_enabled;

	



public:
	SageObject();
	void Init(char const* name, SageModel* model);
	void Update();
	void Draw(SageViewport* vp);
	void Draw(SageCamera* cam);
	void Attach_Texture(SageTexture* texture);
	//Camera;


	SageTransform2D transform;
	SageMaterial material;
	SageMesh obj_mesh;
	static long int object_count;
	static long int current_object_count;


	SageMaterial& GetMaterial();

	void Set_Alpha(float transparency); // 0: Transparent, 1: Opaque

	void Disable_Object();

	

};


#endif // SageObject_HPP