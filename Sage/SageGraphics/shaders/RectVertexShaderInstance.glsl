/* Start Header ************************************************************************/
/*!
\file		RectVertexShaderInstance.glsl
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The base(default) vertex shader containing algorithm to draw the mesh.Pass the
			vertex color and position to the fragment shader. This shader transform the vertices
			to their world space/screen space counterpart by applying the given matrix.
			It then pass along the texture and color tot he fragment shader.

			All content  2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#version 450 core

struct InstanceData
{
	mat4 uModel_Matrix;
	mat4 uNDC_Xform;

	vec2 position;
	vec2 scale;
	vec2 orientation;
	vec4 color;
	float alpha;
};


layout(std430, binding = 0) buffer InstanceDataBuffer
{
	InstanceData uInstance_data[];
};

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTextCoords;
layout(location = 2) in vec3 aColor;

layout(location = 2) out vec2 fOutTexture;
layout(location = 3) out vec3 fOutColor;


uniform mat4 uMatrix;


void main() {
	
	gl_Position = uInstance_data[gl_InstanceID].uNDC_Xform * vec4(aPosition,0.f, 1.f);
	fOutTexture = aTextCoords;
	fOutColor = vec3(uInstance_data[gl_InstanceID].color.x, uInstance_data[gl_InstanceID].color.y, uInstance_data[gl_InstanceID].color.z);
}