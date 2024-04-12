#ifndef VLEESJONGEN_JONGENMOVEDEVENT_H
#define VLEESJONGEN_JONGENMOVEDEVENT_H

#include "../position.h"
#include "baseevent.h"

namespace vlees::event {
class JongenMovedEvent : public BaseEvent
{
private:
        Position position;

public:
        explicit JongenMovedEvent(const Position& position);
        [[nodiscard]] const Position& getPosition() const;
};

} // namespace vlees::event

#endif // VLEESJONGEN_JONGENMOVEDEVENT_H
