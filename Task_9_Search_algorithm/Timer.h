#pragma once

#include <thread>
#include <iostream>

class Timer
{
public:
	Timer();
	~Timer();

private:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
};