#include <iostream>
#include <ostream>

#include "SageProfiler.hpp"
#include "SageTimer.hpp"

int main(){
	SageTimer::Init();
	int i = 0;

	while (i < 10000)
	{
		Profiler::SageProfiler::Mark("Test");
		Profiler::SageProfiler::Mark("Test2");
		SageTimer::Update();

		std::cout << SageTimer::Get_Current_Time() << std::endl;
		i++;
		if (i > 1)
		{
			Profiler::SageProfiler::Stop_Marker("Test");
			if (i > 5000)
				Profiler::SageProfiler::Mark("Test3");
		}
	}
	Profiler::SageProfiler::Stop_Marker("Test2");
	Profiler::SageProfiler::End();


	Profiler::SageProfiler::Print_Profile_Info();
}
