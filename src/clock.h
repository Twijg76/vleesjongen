#ifndef VLEESJONGEN_CLOCK_H
#define VLEESJONGEN_CLOCK_H

#include <chrono>

namespace vlees {
// Meyers Singleton for a clock
class Clock
{
public:
        static Clock& getInstance();
        double secondsSinceReset();
        void restartTime();
        ~Clock() = default;
        Clock(const Clock&) = delete;
        void operator=(Clock const&) = delete;

private:
        Clock();
        std::chrono::system_clock::time_point start;
        static std::chrono::system_clock::time_point alltime();
};
} // namespace vlees

#endif // VLEESJONGEN_CLOCK_H
