/* Start Header ************************************************************************/
/*!
\file		Matrix3x3.h
\title		Memory's Flame
\author		Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (100%)
\par		halisilyasa.b@digipen.edu
\date		08 September 2024
\brief		Contains the functions to calculate matrices.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once

namespace ToastBox {
	class Vec3;
	class Matrix3x3 {
	private:
		union {
			struct Matrix{
				float m00, m01, m02;
				float m10, m11, m12;
				float m20, m21, m22;
			}matrix;
			float m[9];
		};

	public:
		/*!*****************************************************************************
		  \brief
			Constructor for class matrix.
		*******************************************************************************/
		Matrix3x3();

		/*!*****************************************************************************
		  \brief
			Constructor for class matrix.

		  \param _arr

		*******************************************************************************/
		Matrix3x3(const float* arr);

		/*!*****************************************************************************
		  \brief
			Constructor for class matrix.
		*******************************************************************************/
		Matrix3x3(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22);

		/*!*****************************************************************************
		  \brief
			Copy Assignment for class matrix.

		  \param _rhs
			The other matrix.

		  \return
			The current matrix.
		*******************************************************************************/
		Matrix3x3 operator=(const Matrix3x3& rhs);

		/*!*****************************************************************************
		  \brief
			Operator overload for ~ to transpose a matrix.

		  \return
			The result of transposing the matrix.
		*******************************************************************************/
		Matrix3x3 operator~();

		/*!*****************************************************************************
		  \brief
			Creates an identity matrix to the current matrix.
		*******************************************************************************/
		void Matrix3Identity();

		/*!*****************************************************************************
		  \brief
			Performs translation transformation to the matrix.

		  \param _x
			The x translation.

		  \param _y
			The y translation.
		*******************************************************************************/
		void Matrix3Translate(float _x, float _y);

		/*!*****************************************************************************
		  \brief
			Performs scaling transformation to the matrix.

		  \param _x
			The x scale.

		  \param _y
			The y scale.
		*******************************************************************************/
		void Matrix3Scale(float _x, float _y);

		/*!*****************************************************************************
		  \brief
			Performs radian rotation transformation to the matrix.

		  \param _angle
			The angle (in radian) of the rotation.
		*******************************************************************************/
		void Matrix3RotRad(float _angle);

		/*!*****************************************************************************
		  \brief
			Performs degree rotation transformation to the matrix.

		  \param _angle
			The angle (in degree) of the rotation.
		*******************************************************************************/
		void Matrix3RotDeg(float _angle);

		/*!*****************************************************************************
		  \brief
			Transposes a matrix.

		  \param _p_mtx
			The matrix itself.
		*******************************************************************************/
		void Matrix3Transpose(const Matrix3x3& _p_mtx);

		/*!*****************************************************************************
		  \brief
			Invereses a matrix.

		  \param _mtx
			The matrix itself.
		*******************************************************************************/
		void Matrix3SetInverse(const Matrix3x3& _mtx);

		/*!*****************************************************************************
		  \brief
			Invereses a matrix.

		  \return
			The copy of the matrix but inversed.
		*******************************************************************************/
		Matrix3x3 inverse() const;

		/*!*****************************************************************************
		  \brief
			Invereses a matrix.

		  \return
			The matrix itself.
		*******************************************************************************/
		void invert();

		/*!*****************************************************************************
		  \brief
			Performs addition calculation to a matrix

		  \param _rhs
			The other matrix.
		*******************************************************************************/
		void Matrix3Add(const Matrix3x3& _rhs);

		/*!*****************************************************************************
		  \brief
			Performs addition calculation to 2 matrices

		  \param _lhs
			The first matrix.

		  \param _rhs
			The second matrix.

		  \return
			The result of both matrices added.
		*******************************************************************************/
		Matrix3x3 Matrix3Add2(const Matrix3x3& _lhs, const Matrix3x3& _rhs);

		/*!*****************************************************************************
		  \brief
			Performs subtraction calculation to a matrix

		  \param _rhs
			The other matrix.
		*******************************************************************************/
		void Matrix3Sub(const Matrix3x3& _rhs);

		/*!*****************************************************************************
		  \brief
			Performs subtraction calculation to 2 matrices

		  \param _lhs
			The first matrix.

		  \param _rhs
			The second matrix.

		  \return
			The result of both matrices subtracted.
		*******************************************************************************/
		Matrix3x3 Matrix3Sub2(const Matrix3x3& _lhs, const Matrix3x3& _rhs);

		/*!*****************************************************************************
		  \brief
			Performs multiplication calculation to a matrix

		  \param _scale
			The scalar.
		*******************************************************************************/
		void Matrix3Mul(const float _scale);

		/*!*****************************************************************************
		  \brief
			Performs multiplication calculation to 2 matrices

		  \param _lhs
			The matrix itself.

		  \param _scale
			The scalar.

		  \return
			The result of multiplying the matrix.
		*******************************************************************************/
		Matrix3x3 Matrix3Mul2(const Matrix3x3& _lhs, const float _scale);

		/*!*****************************************************************************
		  \brief
			Performs division calculation to a matrix

		  \param _scale
			The scalar.
		*******************************************************************************/
		void Matrix3Div(const float _scale);

		/*!*****************************************************************************
		  \brief
			Performs division calculation to 2 matrices

		  \param _lhs
			The matrix itself.

		  \param _scale
			The scalar.

		  \return
			The result of dividing the matrix.
		*******************************************************************************/
		Matrix3x3 Matrix3Div2(const Matrix3x3& _lhs, const float _scale);

		/*!*****************************************************************************
		  \brief
			Returns the elements of a matrix

		  \return
			The elements of a matrix.
		*******************************************************************************/
		Matrix3x3 getMatrixElements();

		/*!*****************************************************************************
		  \brief
			Retrieves a matrix

		  \return
			A matrix.
		*******************************************************************************/
		Matrix3x3 getMatrix();

		/*!*****************************************************************************
		  \brief
			Sets a matrix to desired values.

		  \return
			The set matrix.
		*******************************************************************************/
		Matrix3x3 setMatrix(float, float, float, float, float, float, float, float, float);

		/*!*****************************************************************************
		  \brief
			Returns the elements in the matrix.

		  \return
			The elements in the matrix.
		*******************************************************************************/
		const float* data() const;

		/*!*****************************************************************************
		  \brief
			Returns the elements in the matrix.

		  \return
			The elements in the matrix.
		*******************************************************************************/
		float* data();

		/*!*****************************************************************************
		  \brief
			Operator overload for * to multiply 2 matrices.

		  \param _lhs
			The first matrix.

		  \param _rhs
			The second matrix.

		  \return
			The result of multiplying the matrices.
		*******************************************************************************/
		friend Matrix3x3 operator*(const Matrix3x3& _lhs, const Matrix3x3& _rhs);
	};

	/*!*****************************************************************************
	  \brief
		Performs scaling calculation to 2 matrices

	  \param _data
		The matrix itself.

	  \param _x
		The x scalar.

	  \param _y
		The y scalar.

	  \return
		The result of scaling the matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3Scaling(Matrix3x3&, float _x, float _y);

	/*!*****************************************************************************
	  \brief
		Performs radian rotation calculation to 2 matrices.

	  \param
		The matrix itself.

	  \param _angle
		The angle of rotation.

	  \return
		The result of rotating the matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3Rotation(Matrix3x3&, float _angle);

	/*!*****************************************************************************
	  \brief
		Translates a matrix.

	  \param
		The matrix itself.

	  \param _x
		The x translation.

	  \param _y
		The y translation.

	  \return
		The result of translating the matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3Translation(Matrix3x3&, float _x, float _y);

	/*!*****************************************************************************
	  \brief
		Concatenates 2 matrices.

	  \param
		The matrix itself.

	  \param _angle
		The angle of rotation.

	  \return
		The result of rotating the matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3Concat(Matrix3x3 const& _lhs, Matrix3x3 const& _rhs);
}