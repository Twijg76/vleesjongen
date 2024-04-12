#include "touchside.h"

#include <utility>
vlees::event::TouchSide::TouchSide(std::string kant) { this->side = std::move(kant); }
[[maybe_unused]] std::string vlees::event::TouchSide::getSide() const { return side; }
