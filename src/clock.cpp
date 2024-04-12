#include "clock.h"

vlees::Clock& vlees::Clock::getInstance()
{
        static Clock instance;
        return instance;
}

vlees::Clock::Clock() { restartTime(); }

void vlees::Clock::restartTime() { start = std::chrono::system_clock::now(); }

double vlees::Clock::secondsSinceReset()
{
        return (alltime() - start).count(); // narrowing conversion long -> double
}
std::chrono::system_clock::time_point vlees::Clock::alltime() { return std::chrono::system_clock::now(); }
