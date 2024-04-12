//
// Created by twijg on 23/07/23.
//

#ifndef VLEESJONGEN_MOVABLEMOVEDEVENT_H
#define VLEESJONGEN_MOVABLEMOVEDEVENT_H
#include "../position.h"
#include "baseevent.h"
#include <string>
namespace vlees::event {
class MovableMovedEvent : public BaseEvent
{
private:
        const Position newposition;
        const Position oldposition;
        const std::string type;

public:
        explicit MovableMovedEvent(std::string type, const Position& oldposition, const Position& newposition);
        [[nodiscard]] const Position& getNewPosition() const;
        [[nodiscard]] const Position& getOldPosition() const;
        [[nodiscard]] const std::string& getType() const;
};
} // namespace vlees::event

#endif // VLEESJONGEN_MOVABLEMOVEDEVENT_H
