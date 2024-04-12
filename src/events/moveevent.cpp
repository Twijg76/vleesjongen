#include "moveevent.h"
vlees::event::MoveEvent::MoveEvent(std::string where) : where(std::move(where)) {}
const std::string& vlees::event::MoveEvent::getWhere() const { return where; }
