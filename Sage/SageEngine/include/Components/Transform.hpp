/* Start Header ************************************************************************/
/*!
\file		Transform.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class Transform that overrides the virtual functions of the
			base class Component to do transform specific tasks.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Components/Component.hpp"

//derived component class Transform that handles object transforms including positions, rotations and scales
class Transform : public Component
{
private:
	float positions[3]{};
	float rotations[3]{};
	float scale[3]{};
	bool is_UI_Element{ false };

public:
	/*!*****************************************************************************
	  \brief
		Default constructor for Transform
	*******************************************************************************/
	Transform();

	/*!*****************************************************************************
	  \brief
		Constructor for Transform that has values for initial positions, rotations and scales

	  \param _pos
		initial positions for the transform

	  \param _rot
		initial rotations for the transform

	  \param _scale
		initial scales for the transform

	  \param _is_UI_element
		whether this gameobject is a UI element.
	*******************************************************************************/
	Transform(float const* _pos, float const* _rot, float const* _scale, bool _is_UI_element = false);

	/*!*****************************************************************************
	  \brief
		Override constructor for Transform that has values for initial positions, rotations and scales

	  \param _pos
		initial positions for the transform

	  \param _rot
		initial rotations for the transform

	  \param _scale
		initial scales for the transform
	*******************************************************************************/
	Transform(std::initializer_list<float> const& _pos, std::initializer_list<float> const& _rot, std::initializer_list<float> const& _scale);

	/*!*****************************************************************************
	  \brief
		This function initializes the component along with any Transform specific
		members that need initializing

	  \param _parent
		The gameobject that created this component
	*******************************************************************************/
	void Init(GameObject* _parent) override;

	/*!*****************************************************************************
	  \brief
		Updates members of Transform separately from the set functions
	*******************************************************************************/
	void Update() override;

	/*!*****************************************************************************
	  \brief
		Provides a space for any free or unloading functions that may be required
		by subsequent interation of this component
	*******************************************************************************/
	void Exit() override;

	/*!*****************************************************************************
	  \brief
		Gets overriden based on what component this is

	  \return
		the enum representating what component this is
	*******************************************************************************/
	ComponentType Get_Component_Type() override;

	/*!*****************************************************************************
	  \brief
		Sets the position member to the _new_pos

	  \param _new_pos
		new positions for the transform
	*******************************************************************************/
	void Set_Positions(float const* _new_pos);

	/*!*****************************************************************************
	  \brief
		Sets the position member to the _new_pos

	  \param _new_pos
		new positions for the transform
	*******************************************************************************/
	void Set_Positions(std::initializer_list<float> const& _new_pos);
	/*!*****************************************************************************
	  \brief
		Gets the position member

	  \return
		the position member
	*******************************************************************************/
	float const* Get_Positions();

	/*!*****************************************************************************
	  \brief
		Sets the rotation member to the _new_rot

	  \param _new_rot
		new rotation for the transform
	*******************************************************************************/
	void Set_Rotations(float const* _new_rot);
	/*!*****************************************************************************
	  \brief
		Sets the rotation member to the _new_rot

	  \param _new_rot
		new rotation for the transform
	*******************************************************************************/
	void Set_Rotations(std::initializer_list<float> const& _new_rot);
	/*!*****************************************************************************
	  \brief
		Gets the rotation member

	  \return
		the rotation member
	*******************************************************************************/
	float const* Get_Rotations();

	/*!*****************************************************************************
	  \brief
		Sets the scale member to the _new_scale

	  \param _new_scale
		new scale for the transform
	*******************************************************************************/
	void Set_Scale(float const* _new_scale);
	/*!*****************************************************************************
	  \brief
		Sets the scale member to the _new_scale

	  \param _new_scale
		new scale for the transform
	*******************************************************************************/
	void Set_Scale(std::initializer_list<float> const& _new_scale);
	/*!*****************************************************************************
	  \brief
		Gets the scale member

	  \return
		the scale member
	*******************************************************************************/
	float const* Get_Scale();
	
	/*!*****************************************************************************
	  \brief
		Adds _delta_pos to the current position

	  \param _delta_pos
		the position to add to the current position
	*******************************************************************************/
	void Translate(float const* _delta_pos);
	/*!*****************************************************************************
	  \brief
		Adds _delta_pos to the current position

	  \param _delta_pos
		the position to add to the current position
	*******************************************************************************/
	void Translate(std::initializer_list<float> const& _delta_pos);
	/*!*****************************************************************************
	  \brief
		Adds _delta_rot to the current rotation

	  \param _delta_pos
		the change in rotation
	*******************************************************************************/
	void Rotate(float const* _delta_rot);
	/*!*****************************************************************************
	  \brief
		Adds _delta_rot to the current rotation

	  \param _delta_pos
		the change in rotation
	*******************************************************************************/
	void Rotate(std::initializer_list<float> const& _delta_rot);
	/*!*****************************************************************************
	  \brief
		Adds _delta_scale to the current scale

	  \param _delta_pos
		the change in scale
	*******************************************************************************/
	void Scale(float const* _delta_scale);
	/*!*****************************************************************************
	  \brief
		Adds _delta_scale to the current scale

	  \param _delta_pos
		the change in scale
	*******************************************************************************/
	void Scale(std::initializer_list<float> const& _delta_scale);

	/*!*****************************************************************************
	  \brief
		Adds _delta_scale to the current scale

	  \return 
		whether this component is for a UI element
	*******************************************************************************/
	bool& Is_UI_Element();
};
