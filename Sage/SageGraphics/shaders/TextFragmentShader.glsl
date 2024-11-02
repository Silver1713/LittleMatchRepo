#version 450 core



layout(location = 0) in vec4 fColor;
layout(location = 1) in vec2 fTexCoord;

const float edgeThreshold = 0.5;
const float smoothwidth = 0.1;

uniform sampler2D uTexture;
out vec4 color;

void main() {
	float r = texture(uTexture, fTexCoord).r;
	float alpha = smoothstep(edgeThreshold - smoothwidth, edgeThreshold + smoothwidth, r);

	
	color = vec4(0, 0, 0, alpha);
}