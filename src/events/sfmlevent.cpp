#include "sfmlevent.h"
vlees::event::SFMLEvent::SFMLEvent(sf::Event realEvent) : realEvent(realEvent) {}
const sf::Event& vlees::event::SFMLEvent::getRealEvent() const { return realEvent; }
