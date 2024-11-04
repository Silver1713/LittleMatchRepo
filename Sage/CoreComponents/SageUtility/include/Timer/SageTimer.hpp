/* Start Header ************************************************************************/
/*!
\file		SageTimer.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		This file contain the declaration for the SageTimer class. This class
			is used to manage the lifetime of the engine. Delta time is calculated
			and obtained from this class.
*/
/* End Header **************************************************************************/
#ifndef SAGE_TIMER_HPP
#define SAGE_TIMER_HPP

#include <chrono>
/*!*****************************************************************************
\brief Encapsulates the engine's timer.

This class is used to manage the lifetime of the engine. Delta time is calculated
here.
*******************************************************************************/
struct SageTimer
{
	static bool initialized;
	static double maxRefresh_Rate;
	static std::chrono::time_point<std::chrono::steady_clock> start_time; //!< start time of the engine
	static std::chrono::time_point<std::chrono::steady_clock> prev_time; //!< previous time of the engine

	static double delta_time; //!< delta time of the engine
	/*!*****************************************************************************
	\brief Intialize the timer.

	This function initializes the timer by setting the start time and previous time
	to the current time and starting the count.
	*******************************************************************************/
	static void Init();
	/*!*****************************************************************************
	\brief Update the timer.
	This function updates the timer by calculating the delta time , setting the
	prev_time and updating the current time.
	*******************************************************************************/
	static void Update();
	/*!*****************************************************************************
	\brief Get the current time.
	This function returns the current time of the engine.
	*******************************************************************************/
	static double Get_Current_Time();
	/*!*****************************************************************************
	\brief Set the time.
	This function  sets the time of the engine.
	*******************************************************************************/
	static void Set_Time(double time);
};

#endif // !SAGE_TIMER_HPP