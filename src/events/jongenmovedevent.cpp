#include "jongenmovedevent.h"

vlees::event::JongenMovedEvent::JongenMovedEvent(const vlees::Position& position) : position(position) {}
const vlees::Position& vlees::event::JongenMovedEvent::getPosition() const { return position; }
