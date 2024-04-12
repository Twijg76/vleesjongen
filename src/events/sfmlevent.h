#ifndef VLEESJONGEN_SFMLEVENT_H
#define VLEESJONGEN_SFMLEVENT_H

#include "baseevent.h"
#include <SFML/Window/Event.hpp>

namespace vlees::event {
class SFMLEvent : public BaseEvent
{
private:
        sf::Event realEvent{};

public:
        explicit SFMLEvent(sf::Event realEvent);
        [[nodiscard]] const sf::Event& getRealEvent() const;
};
} // namespace vlees::event

#endif // VLEESJONGEN_SFMLEVENT_H
