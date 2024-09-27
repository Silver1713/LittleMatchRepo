/******************************************************************************
File name	 : shapes.hpp
Project		 : Memory's Flame
Author       : Edwin Lee Zirui
E-mail		 : edwinzirui.lee@digipen.edu
Data		 : 11/09/2024
Brief		 : Contain structures decribing shape attributes
*
* \copyright	All content 2024 DigiPen Institute of Technology Singapore. All
				rights reserved.
******************************************************************************/

#pragma once
#include "Vector2.h"

namespace ToastBox {
	struct  Circle
	{
		Vec2 center;
		float radius;
	};

	struct Line {
		Vec2 pt1;
		Vec2 pt2;
		Vec2 normal;
	};

	struct Rectangle {
		Vec2 center;
		float width;
		float height;
		Vec2 min;
		Vec2 max;
	};
}