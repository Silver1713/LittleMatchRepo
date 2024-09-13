#version 450 core
layout(location = 2) in vec2 aTextCoords;
layout(location = 3) in vec3 aFragColor;

uniform bool uUseColor;
uniform bool uUseBorderColor;
uniform float uBorderSize;
uniform float uCornerRadius;  // New uniform to control corner radius
uniform bool uUseTexture;
uniform vec4 uColor;
uniform vec4 uBorderColor;
uniform vec2 uObjectSize;

uniform sampler2D uTex2D;

out vec4 color;

void main() {
    vec4 c_clr = vec4(aFragColor, 1.0);

    if (uUseBorderColor) {
        float borderSizeX = uBorderSize / uObjectSize.x; // Normalize border size relative to object width
        float borderSizeY = uBorderSize / uObjectSize.y; // Normalize border size relative to object height

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

        // Apply the appropriate color
        if (isInBorder && !isInCorner) {
            c_clr = uBorderColor;  // Border color
        }
        else {
			if (uUseTexture) {
				c_clr = texture(uTex2D, aTextCoords);  // Texture color
			}
            else {
                c_clr = (!uUseColor) ? vec4(aFragColor, 1.0) : uColor;  // Fill color
            }
        }
    }
    else if (uUseColor) {
        
        c_clr = uColor;
	}
	else if (uUseTexture) {
        c_clr = texture(uTex2D, aTextCoords);
	}

    color = c_clr;
}
