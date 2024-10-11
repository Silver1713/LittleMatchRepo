/* Start Header ************************************************************************/
/*!
\file		BaseVertexShader.glsl
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
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTextCoords;
layout(location = 2) in vec3 aColor;

layout(location = 2) out vec2 fOutTexture;
layout(location = 3) out vec3 fOutColor;

uniform mat3 uModel_xform;
void main() {
	vec3 pos = uModel_xform * vec3(aPosition, 1.f);
	gl_Position = vec4(pos, 1.f);	
	fOutTexture = aTextCoords;
	fOutColor = aColor;
}