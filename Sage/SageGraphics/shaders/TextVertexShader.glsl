#version 450 core

// Define structure for the data
struct CharacterData {
    vec4 offset;
    vec4 uv;
    vec2 size;
};

// SSBO for 32 characters
layout(std430, binding = 5) buffer CharacterBuffer {
    CharacterData characters[];
};

// Inputs
layout(location = 0) in vec2 aPosition;   // Local vertex position for each glyph quad
layout(location = 1) in vec2 aTextCoords; // Texture coordinates for each glyph
layout(location = 2) in vec3 aColor;      // Color input

// Outputs
layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fTexture;

// Uniforms
uniform mat4 uTransform;

void main() {
    CharacterData data = characters[gl_InstanceID];
    float aspectRatio = data.size.x / data.size.y;

  
    vec2 correctedPosition = aPosition;

    if (aspectRatio > 1.0) {
        correctedPosition.y /= aspectRatio;  
    }
    else {
        correctedPosition.x *= aspectRatio;  
    }

    
    vec2 uv0 = data.uv.xy;
    vec2 uv1 = data.uv.zw;
    fTexture = uv0 + aTextCoords * (uv1 - uv0);
    //fTexture = aTextCoords; 
    gl_Position = uTransform * (vec4(correctedPosition, 0, 1) + vec4(1,0, 0, 0) * gl_InstanceID);

    
    fragColor = vec4(aColor, 1.0);
}
