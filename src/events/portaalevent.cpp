#include "portaalevent.h"

#include <utility>
vlees::event::PortaalEvent::PortaalEvent(vlees::Position des, std::string fromri, std::string tori)
    : dest(des), fromrichting(std::move(fromri)), torichting(std::move(tori))
{
}
const std::string& vlees::event::PortaalEvent::getFromrichting() const { return fromrichting; }
const std::string& vlees::event::PortaalEvent::getTorichting() const { return torichting; }
const vlees::Position& vlees::event::PortaalEvent::getDest() const { return dest; }
