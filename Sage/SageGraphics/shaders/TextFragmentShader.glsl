#version 450 core



layout(location = 0) in vec4 fColor;
layout(location = 1) in vec2 fTexCoord;


uniform sampler2D uTexture;
out vec4 color;

void main() {
	color = vec4(0,0,0, texture(uTexture, fTexCoord).r);
}