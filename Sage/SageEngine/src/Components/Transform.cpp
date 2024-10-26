/* Start Header ************************************************************************/
/*!
\file		Transform.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class Transform that overrides the virtual functions of the
			base class Component to do transform specific tasks.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/Component.hpp"
#include "Components/Transform.hpp"

#include "Components/RigidBody.hpp"
#include "GameObjects.hpp"
#include "SageHelper.hpp"

/*!*****************************************************************************
  \brief
	Default constructor for Transform
*******************************************************************************/
Transform::Transform() {}

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
Transform::Transform(ToastBox::Vec3 const& _pos, ToastBox::Vec3 const& _rot, ToastBox::Vec3 const& _scale) : position{ _pos }, rotation{ _rot }, scale{ _scale }, previous_position{ _pos } {}

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
Transform::Transform(std::initializer_list<float> const& _pos, std::initializer_list<float> const& _rot, std::initializer_list<float> const& _scale) : Transform(
	ToastBox::Vec3(*(_pos.begin()), *(_pos.begin() + 1), *(_pos.begin() + 2)),
	ToastBox::Vec3(*(_rot.begin()), *(_rot.begin() + 1), *(_rot.begin() + 2)),
	ToastBox::Vec3(*(_scale.begin()), *(_scale.begin() + 1), *(_scale.begin() + 2))) {}

/*!*****************************************************************************
  \brief
	This function initializes the component along with any Transform specific
	members that need initializing

  \param _parent
	The gameobject that created this component
*******************************************************************************/
void Transform::Init(GameObject* _parent)
{
	Component::Init(_parent);
}

/*!*****************************************************************************
  \brief
	Updates members of Transform separately from the set functions
*******************************************************************************/
void Transform::Update()
{
	if (!is_enabled) { return; }
	// update model matrix

	ToastBox::Matrix3x3 translation_matrix{};
	translation_matrix.Matrix3Translate(position.x, position.y);
	ToastBox::Matrix3x3 rotation_matrix{};
	ToastBox::Matrix3x3 scale_matrix{};

	rotation_matrix.Matrix3RotDeg(rotation.x);
	scale_matrix.Matrix3Scale(scale.x, scale.y);

	model_matrix = ~translation_matrix * ~rotation_matrix * ~scale_matrix;


	if (!(position == previous_position)) {
		previous_position = position;
	}
	
}
void Transform::Exit()
{

}

/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType Transform::Get_Component_Type() { return TRANSFORM; }

/*!*****************************************************************************
  \brief
	Sets the position member to the _new_pos

  \param _new_pos
	new positions for the transform
*******************************************************************************/
void Transform::Set_Position(ToastBox::Vec3 const& _new_pos)
{
	position = _new_pos;
}

/*!*****************************************************************************
  \brief
	Sets the position member to the _new_pos

  \param _new_pos
	new positions for the transform
*******************************************************************************/
void Transform::Set_Position(std::initializer_list<float> const& _new_pos)
{
	for (unsigned int i{}; i < 3; i++)
	{
		position[i] = *(_new_pos.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Gets the position member

  \return
	the position member
*******************************************************************************/
ToastBox::Vec3 const& Transform::Get_Position()
{
	return position;
}

/*!*****************************************************************************
  \brief
	Sets the prev position member to the _new_prev_pos

  \param _new_pos
	new positions for the transform
*******************************************************************************/
void Transform::Set_Prev_Position(ToastBox::Vec3 const& _new_prev_pos)
{
	previous_position = _new_prev_pos;
}

/*!*****************************************************************************
  \brief
	Sets the prev position member to the _new_prev_pos

  \param _new_pos
	new positions for the transform
*******************************************************************************/
void Transform::Set_Prev_Position(std::initializer_list<float> const& _new_prev_pos)
{
	for (unsigned int i{}; i < 3; i++)
	{
		previous_position[i] = *(_new_prev_pos.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Gets the prev position member

  \return
	the position member
*******************************************************************************/
ToastBox::Vec3 const& Transform::Get_Prev_Position()
{
	return previous_position;
}

/*!*****************************************************************************
  \brief
	Sets the rotation member to the _new_rot

  \param _new_rot
	new rotation for the transform
*******************************************************************************/
void Transform::Set_Rotation(ToastBox::Vec3 const& _new_rot)
{
	rotation = _new_rot;
}

/*!*****************************************************************************
  \brief
	Sets the rotation member to the _new_rot

  \param _new_rot
	new rotation for the transform
*******************************************************************************/
void Transform::Set_Rotation(std::initializer_list<float> const& _new_rot)
{
	for (unsigned int i{}; i < 3; i++)
	{
		rotation[i] = *(_new_rot.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Gets the rotation member

  \return
	the rotation member
*******************************************************************************/
ToastBox::Vec3 const& Transform::Get_Rotation()
{
	return rotation;
}

/*!*****************************************************************************
  \brief
	Sets the scale member to the _new_scale

  \param _new_scale
	new scale for the transform
*******************************************************************************/
void Transform::Set_Scale(ToastBox::Vec3 const& _new_scale)
{
	scale = _new_scale;
}

/*!*****************************************************************************
  \brief
	Sets the scale member to the _new_scale

  \param _new_scale
	new scale for the transform
*******************************************************************************/
void Transform::Set_Scale(std::initializer_list<float> const& _new_scale)
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
ToastBox::Vec3 const& Transform::Get_Scale()
{
	return scale;
}

/*!*****************************************************************************
  \brief
	Adds _delta_pos to the current position

  \param _delta_pos
	the position to add to the current position
*******************************************************************************/
void Transform::Translate(ToastBox::Vec3 const& _delta_pos)
{
	position += _delta_pos;
}

/*!*****************************************************************************
  \brief
	Adds _delta_pos to the current position

  \param _delta_pos
	the position to add to the current position
*******************************************************************************/
void Transform::Translate(std::initializer_list<float> const& _delta_pos)
{
	for (unsigned int i{}; i < 3; i++)
	{
		position[i] += *(_delta_pos.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Adds _delta_rot to the current rotation

  \param _delta_pos
	the change in rotation
*******************************************************************************/
void Transform::Rotate(ToastBox::Vec3 const& _delta_rot)
{
	rotation += _delta_rot;
}

/*!*****************************************************************************
  \brief
	Adds _delta_rot to the current rotation

  \param _delta_pos
	the change in rotation
*******************************************************************************/
void Transform::Rotate(std::initializer_list<float> const& _delta_rot)
{
	for (unsigned int i{}; i < 3; i++)
	{
		rotation[i] += *(_delta_rot.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Adds _delta_scale to the current scale

  \param _delta_pos
	the change in scale
*******************************************************************************/
void Transform::Scale(ToastBox::Vec3 const& _delta_scale)
{
	scale += _delta_scale;
}

/*!*****************************************************************************
  \brief
	Adds _delta_scale to the current scale

  \param _delta_pos
	the change in scale
*******************************************************************************/
void Transform::Scale(std::initializer_list<float> const& _delta_scale)
{
	for (unsigned int i{}; i < 3; i++)
	{
		scale[i] += *(_delta_scale.begin() + i);
	}
}

/*!*****************************************************************************
  \brief
	Gets the 3x3 Model Matrix

  \return
	the 3x3 Model Matrix
*******************************************************************************/
ToastBox::Matrix3x3& Transform::Get_Model_Matrix()
{
	return model_matrix;
}
