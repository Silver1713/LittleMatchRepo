/* Start Header ************************************************************************/
/*!
\file		UITransform.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		12 October 2024
\brief		Contains the derived class UITransform that overrides the virtual functions of the
			base class Component to do UITransform specific tasks. Uses screen space instead
			of Transform's world space.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/Component.hpp"
#include "Components/UITransform.hpp"

#include "Components/Physics.hpp"
#include "GameObjects.hpp"

/*!*****************************************************************************
  \brief
	Default constructor for UITransform
*******************************************************************************/
UITransform::UITransform() {}

/*!*****************************************************************************
  \brief
	Constructor for UITransform that has values for initial positions, rotations and scales

  \param _pos
	initial positions for the transform

  \param _rot
	initial rotations for the transform

  \param _scale
	initial scales for the transform

  \param _is_UI_element
	whether this gameobject is a UI element.
*******************************************************************************/
UITransform::UITransform(float const* _pos, float const* _rot, float const* _scale, bool _is_UI_element) : positions{ *_pos,*(_pos + 1),*(_pos + 2) }, rotations{ *_rot, *(_rot + 1), *(_rot + 2) }, scale{ *_scale, *(_scale + 1), *(_scale + 2) }, is_UI_Element{ _is_UI_element } {}

/*!*****************************************************************************
  \brief
	Override constructor for UITransform that has values for initial positions, rotations and scales

  \param _pos
	initial positions for the transform

  \param _rot
	initial rotations for the transform

  \param _scale
	initial scales for the transform
*******************************************************************************/
UITransform::UITransform(std::initializer_list<float> const& _pos, std::initializer_list<float> const& _rot, std::initializer_list<float> const& _scale) : UITransform(_pos.begin(), _rot.begin(), _scale.begin()) {}

/*!*****************************************************************************
  \brief
	This function initializes the component along with any UITransform specific
	members that need initializing

  \param _parent
	The gameobject that created this component
*******************************************************************************/
void UITransform::Init(GameObject* _parent)
{
	Component::Init(_parent);
	previous_position = position = ToastBox::Vec3{ positions[0],positions[1], positions[2] };
}

/*!*****************************************************************************
  \brief
	Updates members of UITransform separately from the set functions
*******************************************************************************/
void UITransform::Update()
{

	// apply transformation
	
	position = ToastBox::Vec3{ positions[0],positions[1], positions[2] };

	Physics* phy = dynamic_cast<Physics*>(Get_Parent()->Get_Component(PHYSICS));
	
	if (phy)
	{
		
		Set_Positions({ Get_Position()[0] +phy->Get_Velocity().x,Get_Position()[1] + phy->Get_Velocity().y, Get_Position()[2]});
	

	}

	// update model matrix

	ToastBox::Matrix3x3 translation_matrix{};
	translation_matrix.Matrix3Translate(positions[0], positions[1]);
	ToastBox::Matrix3x3 rotation_matrix{};
	ToastBox::Matrix3x3 scale_matrix{};

	rotation_matrix.Matrix3RotDeg(rotations[0]);
	scale_matrix.Matrix3Scale(scale[0], scale[1]);

	model_matrix = ~translation_matrix * ~rotation_matrix * ~scale_matrix;


	if (!(position == previous_position)) {
		previous_position = position;
	}
	
}
void UITransform::Exit()
{

}

/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType UITransform::Get_Component_Type() { return TRANSFORM; }

/*!*****************************************************************************
  \brief
	Sets the position member to the _new_pos

  \param _new_pos
	new positions for the transform
*******************************************************************************/
void UITransform::Set_Positions(float const* _new_pos)
{
	*positions = *_new_pos;
}

/*!*****************************************************************************
  \brief
	Sets the position member to the _new_pos

  \param _new_pos
	new positions for the transform
*******************************************************************************/
void UITransform::Set_Positions(std::initializer_list<float> const& _new_pos)
{
	for (unsigned int i{}; i < 3; i++)
	{
		positions[i] = *(_new_pos.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Gets the position member

  \return
	the position member
*******************************************************************************/
float const* UITransform::Get_Position()
{
	return positions;
}

/*!*****************************************************************************
  \brief
	Sets the rotation member to the _new_rot

  \param _new_rot
	new rotation for the transform
*******************************************************************************/
void UITransform::Set_Rotations(float const* _new_rot)
{
	*rotations = *_new_rot;
}

/*!*****************************************************************************
  \brief
	Sets the rotation member to the _new_rot

  \param _new_rot
	new rotation for the transform
*******************************************************************************/
void UITransform::Set_Rotations(std::initializer_list<float> const& _new_rot)
{
	for (unsigned int i{}; i < 3; i++)
	{
		rotations[i] = *(_new_rot.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Gets the rotation member

  \return
	the rotation member
*******************************************************************************/
float const* UITransform::Get_Rotation()
{
	return rotations;
}

/*!*****************************************************************************
  \brief
	Sets the scale member to the _new_scale

  \param _new_scale
	new scale for the transform
*******************************************************************************/
void UITransform::Set_Scale(float const* _new_scale)
{
	*scale = *_new_scale;
}

/*!*****************************************************************************
  \brief
	Sets the scale member to the _new_scale

  \param _new_scale
	new scale for the transform
*******************************************************************************/
void UITransform::Set_Scale(std::initializer_list<float> const& _new_scale)
{
	for (unsigned int i{}; i < 3; i++)
	{
		scale[i] = *(_new_scale.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Gets the scale member

  \return
	the scale member
*******************************************************************************/
float const* UITransform::Get_Scale()
{
	return scale;
}

/*!*****************************************************************************
  \brief
	Adds _delta_pos to the current position

  \param _delta_pos
	the position to add to the current position
*******************************************************************************/
void UITransform::Translate(float const* _delta_pos)
{
	*positions = *_delta_pos;
}

/*!*****************************************************************************
  \brief
	Adds _delta_pos to the current position

  \param _delta_pos
	the position to add to the current position
*******************************************************************************/
void UITransform::Translate(std::initializer_list<float> const& _delta_pos)
{
	for (unsigned int i{}; i < 3; i++)
	{
		positions[i] += *(_delta_pos.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Adds _delta_rot to the current rotation

  \param _delta_pos
	the change in rotation
*******************************************************************************/
void UITransform::Rotate(float const* _delta_rot)
{
	*rotations = *_delta_rot;
}

/*!*****************************************************************************
  \brief
	Adds _delta_rot to the current rotation

  \param _delta_pos
	the change in rotation
*******************************************************************************/
void UITransform::Rotate(std::initializer_list<float> const& _delta_rot)
{
	for (unsigned int i{}; i < 3; i++)
	{
		rotations[i] += *(_delta_rot.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Adds _delta_scale to the current scale

  \param _delta_pos
	the change in scale
*******************************************************************************/
void UITransform::Scale(float const* _delta_scale)
{
	*scale = *_delta_scale;
}

/*!*****************************************************************************
  \brief
	Adds _delta_scale to the current scale

  \param _delta_pos
	the change in scale
*******************************************************************************/
void UITransform::Scale(std::initializer_list<float> const& _delta_scale)
{
	for (unsigned int i{}; i < 3; i++)
	{
		scale[i] += *(_delta_scale.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Adds _delta_scale to the current scale

  \return
	whether this component is for a UI element
*******************************************************************************/
bool& UITransform::Is_UI_Element()
{
	return is_UI_Element;
}

ToastBox::Matrix3x3& UITransform::Get_Model_Matrix()
{
	return model_matrix;
}
