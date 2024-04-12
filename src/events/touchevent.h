#ifndef VLEESJONGEN_TOUCHEVENT_H
#define VLEESJONGEN_TOUCHEVENT_H

#include "../events/baseevent.h"

namespace vlees::event {
class TouchEvent : public BaseEvent
{
public:
        TouchEvent() = default;
};
} // namespace vlees::event

#endif // VLEESJONGEN_TOUCHEVENT_H
