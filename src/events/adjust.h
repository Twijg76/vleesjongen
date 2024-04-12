#ifndef VLEESJONGEN_ADJUST_H
#define VLEESJONGEN_ADJUST_H

#include "baseevent.h"

namespace vlees::event {
class Adjust : public vlees::event::BaseEvent
{
private:
        double seconds;

public:
        [[nodiscard]] double getSeconds() const;
        explicit Adjust(double seconds);
};
} // namespace vlees::event

#endif // VLEESJONGEN_ADJUST_H
