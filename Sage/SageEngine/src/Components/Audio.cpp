/* Start Header ************************************************************************/
/*!
\file		Audio.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class Audio that overrides the virtual functions of the
			base class Component to do Audio specific tasks

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/Audio.hpp"

void Audio::Init(GameObject* _parent)
{
	Component::Init(_parent);
}
void Audio::Update()
{

}
void Audio::Exit()
{

}
ComponentType Audio::Get_Component_Type() { return AUDIO; }