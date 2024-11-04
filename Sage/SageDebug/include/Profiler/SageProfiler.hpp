#ifndef SAGE_PROFILER_HPP
#define SAGE_PROFILER_HPP
#include <map>

#include "SageTimer.hpp"
#include <string>


namespace Profiler
{
	


	struct Marker // Marker to track time per frame
	{
		std::string name;
		double m_StartTime;
		double m_EndTime;

		bool Has_Started;
		bool Has_Ended;


		Marker();
		Marker(const std::string& name);
		void Update_Start();
		void Start();
		void Clear();
		void Reset();
		
		
	};

	struct SageProfiler
	{
		static std::map<std::string, Marker> m_Markers;

		static double m_StartTime; // Start time of the frame
		static double m_PrevExecTime;
		static double m_EndTime; // End time of the frame

		static void Begin(); // Begin profiling;
		static void Mark(std::string name); // Mark the time for a specific marker
		static void Get_Time(std::string name); // Get the time for a specific marker	
		static void Incremental_Update(std::string name); // Update the time for a specific marker
		static void UnMark(std::string name); // Remove the marker

		static void Print_Profile_Info(); // Print the performance info on the different markers
		static std::string Get_Current_Profile(); // Get the performance info on the different markers at a current time
		static void Format_Print_Marker(Marker& marker); // Format the print of the marker

		static void Stop_Marker(std::string name); // Set a end time to marker.
		static void End(); // End profiling



		static void Reset();

		static void Clear_All();





	};



}
#endif // !SAGE_PROFILER_HPP