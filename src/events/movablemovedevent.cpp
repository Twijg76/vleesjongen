//
// Created by twijg on 23/07/23.
//

#include "movablemovedevent.h"

#include <utility>

vlees::event::MovableMovedEvent::MovableMovedEvent(std::string typ, const vlees::Position& oposition,
                                                   const vlees::Position& nposition)
    : type(std::move(typ)), oldposition(oposition), newposition(nposition)
{
}
const vlees::Position& vlees::event::MovableMovedEvent::getNewPosition() const { return newposition; }
const vlees::Position& vlees::event::MovableMovedEvent::getOldPosition() const { return oldposition; }
const std::string& vlees::event::MovableMovedEvent::getType() const { return type; }
