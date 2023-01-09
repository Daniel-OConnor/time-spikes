#include <iostream>
#include <chrono>

constexpr size_t junkSize = 16'000'000;
constexpr size_t bufferSize = 100'000;

using namespace std::chrono_literals;

int main()
{
	long* timestamps = new long[bufferSize];
	long* timeTaken = new long[bufferSize];
	int* junk = new int[junkSize];
	for (size_t i = 0; i < junkSize; ++i)
	{
		junk[i] = 10;
	}
	long index = 0;
	auto startTime = std::chrono::system_clock::now();
	auto currentTime = startTime;
	while (currentTime - startTime < 120s && index < bufferSize)
	{
		auto newTime = std::chrono::system_clock::now();
		auto diff = newTime - currentTime;
		if (diff > 100us)
		{
			timestamps[index] = (newTime - startTime)/1ns;
			timeTaken[index] = diff/1ns;
			++index;
		}
		currentTime = newTime;
	}
	for (size_t i = 0; i < index; ++i)
	{
		std::cout << timeTaken[i] << ", " << timestamps[i] << std::endl;
	}
	return 0;
}
