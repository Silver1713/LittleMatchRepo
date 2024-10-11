/* Start Header ************************************************************************/
/*!
\file		SageFont.hpp
\title		Memory's Flame
\author		Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (100%)
\par		halisilyasa.b@digipen.edu
\date		08 September 2024
\brief		Contains the functions for creating font.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#ifndef SAGEFONT_HPP
#define SAGEFONT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H

namespace SageFont
{
	void Init();
	void Load();
	void Update();
	void Unload();
}

#endif //SAGEFONT_HPP