#ifndef SAGE_TIMER_HPP
#define SAGE_TIMER_HPP

#include <chrono>

struct SageTimer
{
	// This function mimic glfwGetTime() function
	// starting time is the time when the program startss
	static std::chrono::time_point<std::chrono::steady_clock> start_time;
	static std::chrono::time_point<std::chrono::steady_clock> prev_time;

	static double delta_time;

	static void init();

	static double GetCurrentTime();
	static void SetTime(double time);


};

#endif // !SAGE_TIMER_HPP