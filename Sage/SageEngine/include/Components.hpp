/* Start Header ************************************************************************/
/*!
\file		Component.h
\title		
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		12 September 2024
\brief		

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.						
*/
/* End Header **************************************************************************/
#pragma once
typedef enum {
	TRANSFORM,
	SPRITE2D,
	COLLISION2D,
	AUDIO,
	NUM_OF_TYPES_OF_COMPONENTS
} ComponentType;

namespace Components
{
	void Init();
}

class Component
{
protected:
	

public:
	virtual void Init();
	virtual void Update();
	virtual void Exit();
};

class Transform : public Component
{
	void Init() override;
	void Update() override;
	void Exit() override;
};

class Sprite2D : public Component
{
	void Init() override;
	void Update() override;
	void Exit() override;
};

class Collision2D : public Component
{
	void Init() override;
	void Update() override;
	void Exit() override;
};

class Audio : public Component
{
	void Init() override;
	void Update() override;
	void Exit() override;
};

