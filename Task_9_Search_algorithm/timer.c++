#include "Timer.h"

Timer::Timer()
{
	begin = std::chrono::high_resolution_clock::now();
}


Timer::~Timer()
{
	end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	std::cout << "Время выполнения: " << duration.count() << " наноосек.\n";
}