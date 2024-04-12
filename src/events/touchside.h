#ifndef VLEESJONGEN_TOUCHSIDE_H
#define VLEESJONGEN_TOUCHSIDE_H

#include "touchevent.h"
#include <string>

namespace vlees::event {
class TouchSide : public TouchEvent
{
private:
        std::string side;

public:
        explicit TouchSide(std::string side);
        [[maybe_unused]] [[nodiscard]] std::string getSide() const;
};
} // namespace vlees::event

#endif // VLEESJONGEN_TOUCHSIDE_H
