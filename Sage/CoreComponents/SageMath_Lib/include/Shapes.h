/* Start Header ************************************************************************/
/*!
\file		Shapes.h
\title		Memory's Flame
\author		Edwin Lee Zirui, edwinzirui.lee, 2301299 (100%)
\par		edwinzirui.lee@digipen.edu
\date		11 September 2024
\brief		Contain structures decribing shape attributes

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#pragma once
#include "Vector2.h"

namespace ToastBox {
	struct Circle
	{
		Vec2 center;
		float radius;
	};

	struct Line 
	{
		Vec2 pt1;
		Vec2 pt2;
		Vec2 normal;
	};

	struct Rectangle 
	{
		Vec2 center;
		float width;
		float height;
		Vec2 min;
		Vec2 max;
	};
}