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