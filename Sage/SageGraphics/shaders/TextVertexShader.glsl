#version 450 core


//// define structure for the data
struct CharacterData {
	vec4 offset;
	vec4 uv;
};

// SSBO for 32 characters
layout(std430, binding = 5) buffer CharacterBuffer {
	CharacterData characters[];
};

// Uniform for the main quad
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTextCoords;
layout(location = 2) in vec3 aColor;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fTexture;
// Uniforms
uniform mat4 uTransform;


void main() {
	// for each character
	
	CharacterData data = characters[gl_InstanceID];
	vec4 offset = data.offset;

	
	vec2 uv0 = data.uv.xy;
	vec2 uv1 = data.uv.zw;
	
	gl_Position = uTransform * (vec4(aPosition, 0, 1) + vec4(1, 0, 0, 0) * gl_InstanceID);
	// Calculate offset
	fragColor = vec4(aColor,1);
	fTexture = uv0 + aTextCoords * (uv1 - uv0);

	
}