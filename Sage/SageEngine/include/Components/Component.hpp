/* Start Header ************************************************************************/
/*!
\file		Component.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the class Component that declares the base class that is to be polymorphed
			into the various types of components as defined by ComponentType depending on the
			need of a gameobject.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include <string>
#include <initializer_list>

class GameObject;
class SageObject;

//label for the different types of component that currently exist
typedef enum {
	COMPONENT,
	TRANSFORM,
	SPRITE2D,
	BOXCOLLIDER2D,
	//RIGIDBODY2D,
	PHYSICS,
	AUDIO,
	NUM_OF_TYPES_OF_COMPONENTS
} ComponentType;

//base class that gives the basic definition of a component to be polymorphed into more specialized components
class Component
{
protected:
	GameObject* parent{ nullptr };
public:
	/*!*****************************************************************************
	  \brief
		default destructor for component
	*******************************************************************************/
	virtual ~Component() = default;

	/*!*****************************************************************************
	  \brief
		Initializes the component and assigns the parent to the gameobject that
		created this component

	  \param _parent
		the gameobject creating this component
	*******************************************************************************/
	virtual void Init(GameObject* _parent);

	/*!*****************************************************************************
	  \brief
		to be overriden by the Update function of specialized components
		that this component will polymorph into
	*******************************************************************************/
	virtual void Update();

	/*!*****************************************************************************
	  \brief
		to be overriden by the Draw function of specialized components
		that this component will polymorph into
	*******************************************************************************/
	virtual void Draw();

	/*!*****************************************************************************
	  \brief
		to be overriden by the Exit function of specialized components
		that this component will polymorph into
	*******************************************************************************/
	virtual void Exit();

	/*!*****************************************************************************
	  \brief
		Gets overriden based on what component this is

	  \return
		the enum representating what component this is
	*******************************************************************************/
	virtual ComponentType Get_Component_Type();

	/*!*****************************************************************************
	  \brief
		Returns the parent of this component

	  \return
		the parent of this component
	*******************************************************************************/
	GameObject* Get_Parent();

	/*!*****************************************************************************
	  \brief
		Changes the parent of this component

	  \param _parent
		the new parent gameobject
	*******************************************************************************/
	void Set_Parent(GameObject* const _parent);
};

