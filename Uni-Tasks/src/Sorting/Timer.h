#pragma once

#include <iostream>
#include <chrono>

class Timer {
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Startpoint;
	long long m_Duration = 0;
public:
	Timer() {
		m_Startpoint = std::chrono::high_resolution_clock::now();
	}

	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_Startpoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Duration = end - start;
	}

	long long getDuration() { return m_Duration; }
};