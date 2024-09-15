#version 450 core
layout(location = 2) in vec2 aTextCoords;
layout(location = 3) in vec3 aFragColor;

uniform bool uUseColor;
uniform bool uUseBorderColor;
uniform float uBorderSize;
uniform float uCornerRadius;  
uniform bool uUseTexture;
uniform float uTransparency;
uniform vec4 uColor;
uniform vec4 uBorderColor;
uniform vec2 uObjectSize;

uniform sampler2D uTex2D;

out vec4 color;

void main() {
    vec4 c_clr = vec4(aFragColor, 1.0);

    if (uUseBorderColor) {
        float borderSizeX = uBorderSize / uObjectSize.x; 
        float borderSizeY = uBorderSize / uObjectSize.y; 

        // Calculate normalized corner radius
        float normalizedCornerRadiusX = uCornerRadius / uObjectSize.x;
        float normalizedCornerRadiusY = uCornerRadius / uObjectSize.y;

        // Check if the fragment is within the border area
        bool isInBorder = (aTextCoords.x < borderSizeX || aTextCoords.x > 1.0 - borderSizeX ||
            aTextCoords.y < borderSizeY || aTextCoords.y > 1.0 - borderSizeY);

        // Check for rounded corners using distance to each corner
        bool isInCorner = false;
        if (aTextCoords.x < normalizedCornerRadiusX && aTextCoords.y < normalizedCornerRadiusY) {
            isInCorner = (length(aTextCoords - vec2(normalizedCornerRadiusX, normalizedCornerRadiusY)) > normalizedCornerRadiusX);
        }
        if (aTextCoords.x > 1.0 - normalizedCornerRadiusX && aTextCoords.y < normalizedCornerRadiusY) {
            isInCorner = (length(aTextCoords - vec2(1.0 - normalizedCornerRadiusX, normalizedCornerRadiusY)) > normalizedCornerRadiusX);
        }
        if (aTextCoords.x < normalizedCornerRadiusX && aTextCoords.y > 1.0 - normalizedCornerRadiusY) {
            isInCorner = (length(aTextCoords - vec2(normalizedCornerRadiusX, 1.0 - normalizedCornerRadiusY)) > normalizedCornerRadiusX);
        }
        if (aTextCoords.x > 1.0 - normalizedCornerRadiusX && aTextCoords.y > 1.0 - normalizedCornerRadiusY) {
            isInCorner = (length(aTextCoords - vec2(1.0 - normalizedCornerRadiusX, 1.0 - normalizedCornerRadiusY)) > normalizedCornerRadiusX);
        }


        if (isInBorder && !isInCorner) {
            c_clr = uBorderColor;  
        }
        else {
			if (uUseTexture) {
				c_clr = texture(uTex2D, aTextCoords); 
			}
            else {
                c_clr = (!uUseColor) ? vec4(aFragColor, 1.0) : uColor;  
            }
        }
    }
    else if (uUseColor) {
        
        c_clr = uColor;
	}
	else if (uUseTexture) {
        c_clr = texture(uTex2D, aTextCoords);
	}

    color = vec4(c_clr.x, c_clr.y, c_clr.z, uTransparency);
}
