#include "SageTimer.hpp"



std::chrono::time_point<std::chrono::high_resolution_clock> SageTimer::start_time{};
std::chrono::time_point<std::chrono::high_resolution_clock> SageTimer::prev_time{};
double SageTimer::delta_time{};
void SageTimer::init()
{
	start_time = std::chrono::steady_clock::now();
	prev_time = std::chrono::steady_clock::now();

}


double SageTimer::GetCurrentTime()
{
	auto current_time = std::chrono::steady_clock::now();

	double time = std::chrono::duration<double, std::milli>(current_time - start_time).count();

	time /= 1000.0;
	return time;
	
}

void SageTimer::SetTime(double time)
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

