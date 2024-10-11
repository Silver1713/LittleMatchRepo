/* Start Header ************************************************************************/
/*!
\file		BaseFragmentShader.glsl
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The base(default) fragment shader containing algorithm to draw the mesh. Contain addition setting
            and algorithm to render out a border by checking for the mesh edges. Border is 
            always assumed to be rect currently.

            All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/


#version 450 core
layout(location = 2) in vec2 aTextCoords;
layout(location = 3) in vec3 aFragColor;

uniform bool uUseColor;
uniform bool uUseBorderColor;
uniform float uBorderSize;
uniform float uCornerRadius;  
uniform bool uUseTexture;
uniform float uAlpha;
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

        
        float normalizedCornerRadiusX = uCornerRadius / uObjectSize.x;
        float normalizedCornerRadiusY = uCornerRadius / uObjectSize.y;

        
        bool isInBorder = (aTextCoords.x < borderSizeX || aTextCoords.x > 1.0 - borderSizeX ||
            aTextCoords.y < borderSizeY || aTextCoords.y > 1.0 - borderSizeY);

       
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
    else if (uUseTexture && uUseColor){
         c_clr = texture(uTex2D, aTextCoords);
         c_clr *= uColor;
    }
	else if (uUseTexture) {
        c_clr = texture(uTex2D, aTextCoords);
	}
    else if (uUseColor) {
        
        c_clr = uColor;
	}

    color = vec4(c_clr.x, c_clr.y, c_clr.z, uAlpha);
}
