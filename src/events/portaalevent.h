#ifndef VLEESJONGEN_PORTAALEVENT_H
#define VLEESJONGEN_PORTAALEVENT_H

#include "../position.h"
#include "baseevent.h"
#include <string>

namespace vlees::event {
class PortaalEvent : public BaseEvent
{
        Position dest;
        std::string fromrichting;
        std::string torichting;

public:
        PortaalEvent(Position dest, std::string fromrichting, std::string torichting);
        [[nodiscard]] const std::string& getFromrichting() const;
        [[nodiscard]] const std::string& getTorichting() const;
        [[nodiscard]] const Position& getDest() const;
};
} // namespace vlees::event

#endif // VLEESJONGEN_PORTAALEVENT_H
