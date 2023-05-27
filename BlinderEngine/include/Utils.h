#pragma once
#include <chrono>
#include <iostream>


class Timer
{
public:
	Timer() 
	{
		start();
		verbose = true;
	}

	void start() 
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	void end() 
	{
		auto endTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		if (verbose)
			std::cout << duration.count() << std::endl;
		startTime = endTime;
	}
public:
	bool verbose;

private:
	std::chrono::steady_clock::time_point startTime;
		
};
