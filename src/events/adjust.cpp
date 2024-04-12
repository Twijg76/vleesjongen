#include "adjust.h"

double vlees::event::Adjust::getSeconds() const { return seconds; }

vlees::event::Adjust::Adjust(double seconds) : seconds(seconds) {}
