#pragma once

#include <iostream>
#include <chrono>

#define PRINT_TIME 0

class Timer {
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Startpoint;
	double m_Duration = 0;
	bool m_IsRunning = true;
public:
	Timer() {
		m_Startpoint = std::chrono::high_resolution_clock::now();
	}
#if PRINT_TIME
	~Timer() {
		if (m_IsRunning) Stop();
		std::cout << m_Duration << " microseconds\n";
	}
#endif
	void Start() {
		if (m_IsRunning) return;
		m_Startpoint = std::chrono::high_resolution_clock::now();
		m_IsRunning = true;
	}

	void Stop() {
		if (!m_IsRunning) return;

		auto endTimepoint = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::micro> duration = endTimepoint - m_Startpoint;
		m_Duration = duration.count();
		m_IsRunning = false;
	}

	double getDuration() const { return m_Duration; }
};