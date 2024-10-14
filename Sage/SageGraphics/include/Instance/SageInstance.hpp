/* Start Header ************************************************************************/
/*!
\file		SageCamera.cpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		12 October 2024
\brief		This header file contain the definition of a Instance class use for
			rendering an instanced object in the scene. It utilizes instancing and
			SSBO to render multiple instances of the same object in the scene.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/


#ifndef SAGEINSTANCE_HPP
#define SAGEINSTANCE_HPP


#include <glm/glm.hpp>
class SageModel;

struct InstanceData
{
	alignas(16) glm::mat4 model_matrix;      // mat4 aligned to 16 bytes
	alignas(16) glm::mat4 ndc_xform_mat;     // mat4 aligned to 16 bytes
	alignas(8) glm::vec2 position;           // vec2 aligned to 8 bytes
	alignas(8) glm::vec2 scale;              // vec2 aligned to 8 bytes
	alignas(8) glm::vec2 orientation;        // vec2 aligned to 8 bytes
	alignas(16) glm::vec4 color;             // vec4 aligned to 16 bytes
	alignas(16) float alpha;                 // float aligned to 16 bytes
};

class SageInstance
{
	SageModel* model_ref;
	unsigned int instance_count;

	std::vector<InstanceData> Instanced_SSBO;

	static  long long SSBO_SIZE;

	unsigned int SSBO_ID;
public:
	using iterator = std::vector<InstanceData>::iterator;
	using const_iterator = std::vector<InstanceData>::const_iterator;


	SageInstance(SageModel* mdl=nullptr);
	SageInstance(InstanceData* data, unsigned int size, SageModel* mdl = nullptr);
	SageInstance(std::initializer_list<InstanceData> const& data , SageModel* mdl = nullptr);
	~SageInstance();
	


	void Init(SageModel* mdl);
	void Init(InstanceData* data, unsigned int size);
	void Init(std::initializer_list<InstanceData> const& data);
	void Update();

	void Setup_SSBO();
	void Set_Model(SageModel* model);

	InstanceData& operator[](int index);
	 InstanceData const& operator[](int index) const;



	static void Set_SSBO_Size(unsigned int size);

	void Calculate_Model_Matrix();
	void Clear_SSBO();


	void Append_Instance(glm::vec2 position, glm::vec2 scale, glm::vec2 orientation, glm::vec4 color, float alpha);

	void New_Instance( std::initializer_list<InstanceData> const&  data);


	void Load_Instance_To_GPU();

	iterator begin();
	iterator end();


	const_iterator begin() const;
	const_iterator end() const;

	const_iterator cbegin() const;
	const_iterator cend() const;


	SageModel* Get_Model() const;

	int Get_Instance_Count() const;


};


#endif