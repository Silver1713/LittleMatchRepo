#version 450 core


//// define structure for the data
struct CharacterData {
	vec4 color;
	vec4 position;
	vec2 scale;
	int character;
};

// SSBO for 32 characters
layout(std430, binding = 5) buffer CharacterBuffer {
	CharacterData characters[];
};

// Uniform for the main quad
layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec4 vColorCoord;
layout(location = 2) in vec2 vTexture;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fTexture;
// Uniforms
uniform mat4 uTransform;


void main() {
	// for each character

//	vec4 characterPosition = vec4(vPosition.xy,0,0) + vec4(characters[gl_InstanceID].position.xy, 0.0, 0.0);
	
	CharacterData data = characters[gl_InstanceID];
	vec4 characterPosition = data.position;
	gl_Position = uTransform * vec4(vPosition,0,1);

	fragColor = data.color;
	fTexture = vTexture;
	
}