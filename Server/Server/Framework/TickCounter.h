#pragma once

#include <Pch.h>
#include <chrono>

class TickCounter
{
public:
	TickCounter() { Reset(); }
	virtual ~TickCounter() {}

	void Reset()
	{
		m_time = std::chrono::system_clock::now();
	}

	DOUBLE Getduration()
	{
		std::chrono::duration<DOUBLE> duration = std::chrono::system_clock::now() - m_time;
		return duration.count();
	}

private:
	std::chrono::system_clock::time_point m_time;

};