#include "SageProfiler.hpp"

#include <iostream>
#include <iomanip>

namespace Profiler
{

	std::map<std::string, Marker> SageProfiler::m_Markers{};
	double SageProfiler::m_StartTime{};
	double SageProfiler::m_PrevExecTime{};
	double SageProfiler::m_EndTime{};

	Marker::Marker() : name(""), m_StartTime(0), m_EndTime(0), Has_Started(false) {}


	void Marker::Update_Start()
	{
		if (SageTimer::initialized == false)
		{
			std::cerr << "Timer not initialized" << std::endl;
			return;
		}

		m_StartTime = SageTimer::Get_Current_Time();
		Has_Started = true;
		Has_Ended = false;

	}



	Marker::Marker(const std::string& name)
	{
		this->name = name;
		m_StartTime = 0;
		m_EndTime = 0;
		Has_Started = false;
		Has_Ended = false;

	}

	void Marker::Start()
	{
		if (SageTimer::initialized == false)
		{
			std::cerr << "Timer not initialized" << std::endl;
			return;
		}

		m_StartTime = SageTimer::Get_Current_Time();
		Has_Started = true;
	}


	void Marker::Clear()
	{
		m_StartTime = 0;
		m_EndTime = 0;
		Has_Started = false;
		Has_Ended = false;
	}

	void Marker::Reset()
	{
		m_StartTime = SageTimer::Get_Current_Time();
		m_EndTime = 0;
	}

	void SageProfiler::Mark(std::string name)
	{
		if (m_Markers.contains(name))
		{
			if (m_Markers[name].Has_Started == true && !m_Markers[name].Has_Ended == true)
			{
				Incremental_Update(name);
				return;
			}
			if (m_Markers[name].Has_Ended == true)
				m_Markers[name].Update_Start();
			return;
		}
		m_Markers[name] = Marker(name);
		m_Markers[name].Start();
	}


	void SageProfiler::Incremental_Update(std::string name)
	{
		if (m_Markers.contains(name))
		{
			if (m_Markers[name].Has_Started == false)
				return;
			m_Markers[name].m_EndTime = SageTimer::Get_Current_Time();
		}

	}


	void SageProfiler::Begin()
	{
		if (SageTimer::initialized == false)
		{
			std::cerr << "Timer not initialized" << std::endl;
			return;
		}

		m_StartTime = SageTimer::Get_Current_Time();
	}

	std::string SageProfiler::Get_Current_Profile()
	{
		std::string profile_info = "";
		double total_time = 0;

		for (auto& mark : m_Markers)
		{
			total_time += mark.second.m_EndTime - mark.second.m_StartTime;
		}
		for (auto& marker : m_Markers)
		{
			profile_info += "Marker: " + marker.first + '\n';
			profile_info += "Start Time (ms): " + std::to_string(marker.second.m_StartTime * 1000.0) + '\n';
			profile_info += "End Time (ms): " + std::to_string(marker.second.m_EndTime * 1000.0) + '\n';
			profile_info += "Duration (ms) : " + std::to_string((marker.second.m_EndTime - marker.second.m_StartTime) * 1000.0) + '\n';
			profile_info += "Percentage: " + std::to_string(static_cast<unsigned long long>(
				std::ceil((marker.second.m_EndTime - marker.second.m_StartTime) / total_time * 100))) + '%' + '\n';
			profile_info += '\n';
		}

		profile_info += "Execution Time (ms) : " + std::to_string(m_PrevExecTime * 1000.0) + '\n';
		return profile_info;
	}






	void SageProfiler::End() // Mark the end time of the frame
	{
		m_EndTime = SageTimer::Get_Current_Time();
		m_PrevExecTime = m_EndTime - m_StartTime;
		m_StartTime = SageTimer::Get_Current_Time();
		// Stop running markers
		for (auto& marker : m_Markers)
		{
			if (marker.second.Has_Started && !marker.second.Has_Ended)
			{
				marker.second.m_EndTime = m_EndTime;
				marker.second.Has_Ended = true;
			}
		}
	}


	void SageProfiler::Reset() // Clear all markers
	{

		for (auto& marker : m_Markers)
		{
			marker.second.Clear();
		}
	

		m_StartTime = 0;
		m_PrevExecTime = 0;
		m_EndTime = 0;
	}

	void SageProfiler::Clear_All()
	{
		m_Markers.clear();
	}

	void SageProfiler::Stop_Marker(std::string name)
	{
		
		if (m_Markers.contains(name))
		{
			if (m_Markers[name].Has_Started == false || m_Markers[name].Has_Ended)
				return;
			m_Markers[name].m_EndTime = SageTimer::Get_Current_Time();
			m_Markers[name].Has_Ended = true;
		}
	}


	void SageProfiler::Print_Profile_Info()
	{
		int i = 0;
		double total_time = 0;

		std::cout << "===========================================\n";

		for (auto& mark : m_Markers)
		{
			total_time += mark.second.m_EndTime - mark.second.m_StartTime;
		}

		for (auto& marker : m_Markers)
		{
			std::cout << std::fixed << std::setprecision(5);
			std::cout << "Marker: " << marker.first << '\n';
			std::cout << "Start Time (ms): " << marker.second.m_StartTime * 1000.0 << '\n';
			std::cout << "End Time (ms): " << marker.second.m_EndTime * 1000.0 << '\n';
			std::cout << "Duration (ms) : " << (marker.second.m_EndTime - marker.second.m_StartTime) * 1000.0 << '\n';
			std::cout << "Percentage: " <<std::setprecision(5)  << (marker.second.m_EndTime - marker.second.m_StartTime) / total_time * 100 << '%' <<'\n';
			std::cout << '\n';
		}

		
		
		std::cout << "===========================================\n";
		std::cout << std::defaultfloat;
		std::cout << "Execution Time (ms) : " << m_PrevExecTime * 1000 << '\n';

		

	}

	void SageProfiler::Format_Print_Marker(Marker& marker)
	{
		std::cout << '\n';
	}









}
