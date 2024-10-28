/* Start Header ************************************************************************/
/*!
\file		UITransform.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class UITransform that overrides the virtual functions of the
			base class Component to do transform specific tasks.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Components/Component.hpp"
#include "Vector3.h"
#include "Matrix3x3.h"

//derived component class UITransform that handles object transforms including positions, rotations and scales
class UITransform : public Component
{
private:
	ToastBox::Vec3 previous_position{};

	ToastBox::Vec3 position{};
	ToastBox::Vec3 rotation{};
	ToastBox::Vec3 scale{};

	ToastBox::Matrix3x3 model_matrix{};

public:
	/*!*****************************************************************************
	  \brief
		Default constructor for UITransform
	*******************************************************************************/
	UITransform();

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
	UITransform(ToastBox::Vec3 const& _pos, ToastBox::Vec3 const& _rot, ToastBox::Vec3 const& _scale);

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
	UITransform(std::initializer_list<float> const& _pos, std::initializer_list<float> const& _rot, std::initializer_list<float> const& _scale);

	/*!*****************************************************************************
	  \brief
		This function initializes the component along with any UITransform specific
		members that need initializing

	  \param _parent
		The gameobject that created this component
	*******************************************************************************/
	void Init(GameObject* _parent) override;

	/*!*****************************************************************************
	  \brief
		Updates members of UITransform separately from the set functions
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
	void Set_Position(ToastBox::Vec3 const& _new_pos);

	/*!*****************************************************************************
	  \brief
		Sets the position member to the _new_pos

	  \param _new_pos
		new positions for the transform
	*******************************************************************************/
	void Set_Position(std::initializer_list<float> const& _new_pos);
	/*!*****************************************************************************
	  \brief
		Gets the position member

	  \return
		the position member
	*******************************************************************************/
	ToastBox::Vec3 const& Get_Position() const;
	/*!*****************************************************************************
	  \brief
		Gets the position member

	  \return
		the position member
	*******************************************************************************/
	ToastBox::Vec3& Get_Position();
	/*!*****************************************************************************
	  \brief
		Sets the prev position member to the _new_prev_pos

	  \param _new_pos
		new positions for the transform
	*******************************************************************************/
	void Set_Prev_Position(ToastBox::Vec3 const& _new_prev_pos);
	/*!*****************************************************************************
	  \brief
		Sets the prev position member to the _new_prev_pos

	  \param _new_pos
		new positions for the transform
	*******************************************************************************/
	void Set_Prev_Position(std::initializer_list<float> const& _new_prev_pos);
	/*!*****************************************************************************
	  \brief
		Gets the previous position member

	  \return
		the previous position member
	*******************************************************************************/
	ToastBox::Vec3 const& Get_Prev_Position();


	/*!*****************************************************************************
	  \brief
		Sets the rotation member to the _new_rot

	  \param _new_rot
		new rotation for the transform
	*******************************************************************************/
	void Set_Rotation(ToastBox::Vec3 const& _new_rot);
	/*!*****************************************************************************
	  \brief
		Sets the rotation member to the _new_rot

	  \param _new_rot
		new rotation for the transform
	*******************************************************************************/
	void Set_Rotation(std::initializer_list<float> const& _new_rot);
	/*!*****************************************************************************
	  \brief
		Gets the rotation member

	  \return
		the rotation member
	*******************************************************************************/
	ToastBox::Vec3 const& Get_Rotation() const;
	/*!*****************************************************************************
	  \brief
		Gets the rotation member

	  \return
		the rotation member
	*******************************************************************************/
	ToastBox::Vec3& Get_Rotation();
	/*!*****************************************************************************
	  \brief
		Sets the scale member to the _new_scale

	  \param _new_scale
		new scale for the transform
	*******************************************************************************/
	void Set_Scale(ToastBox::Vec3 const& _new_scale);
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
	ToastBox::Vec3 const& Get_Scale() const;
	/*!*****************************************************************************
	  \brief
		Gets the scale member

	  \return
		the scale member
	*******************************************************************************/
	ToastBox::Vec3& Get_Scale();
	/*!*****************************************************************************
	  \brief
		Adds _delta_pos to the current position

	  \param _delta_pos
		the position to add to the current position
	*******************************************************************************/
	void Translate(ToastBox::Vec3 const& _delta_pos);
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
	void Rotate(ToastBox::Vec3 const& _delta_rot);
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
	void Scale(ToastBox::Vec3 const& _delta_scale);
	/*!*****************************************************************************
	  \brief
		Adds _delta_scale to the current scale

	  \param _delta_pos
		the change in scale
	*******************************************************************************/
	void Scale(std::initializer_list<float> const& _delta_scale);

	/*!*****************************************************************************
	  \brief
		Gets the 3x3 Model Matrix

	  \return
		the 3x3 Model Matrix
	*******************************************************************************/
	ToastBox::Matrix3x3& Get_Model_Matrix();
};
