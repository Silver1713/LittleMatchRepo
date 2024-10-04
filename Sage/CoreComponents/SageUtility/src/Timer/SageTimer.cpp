/* Start Header ************************************************************************/
/*!
\file		SageTimer.cpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		This file contain the definition for the SageTimer class. This class
			is used to manage the lifetime of the engine. Delta time is calculated
			and obtained from this class.
*/
/* End Header **************************************************************************/
#include "SageTimer.hpp"

std::chrono::time_point<std::chrono::high_resolution_clock> SageTimer::start_time{};
std::chrono::time_point<std::chrono::high_resolution_clock> SageTimer::prev_time{};
double SageTimer::delta_time{};
void SageTimer::Init()
{
	start_time = std::chrono::steady_clock::now();
	prev_time = std::chrono::steady_clock::now();

}


double SageTimer::Get_Current_Time()
{
	auto current_time = std::chrono::steady_clock::now();

	double time = std::chrono::duration<double, std::milli>(current_time - start_time).count();

	time /= 1000.0;
	return time;
	
}

void SageTimer::Set_Time(double time)
{
	
	start_time = std::chrono::steady_clock::now() - std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>(time));

}


void SageTimer::Update()
{
	auto current_time = std::chrono::steady_clock::now();

	delta_time = std::chrono::duration<double, std::milli>(current_time - prev_time).count();

	delta_time /= 1000.0;

	prev_time = current_time;
}

