#ifndef VLEESJONGEN_MOVEEVENT_H
#define VLEESJONGEN_MOVEEVENT_H

#include "baseevent.h"
#include <string>

namespace vlees::event {
class MoveEvent : public BaseEvent
{
        std::string where;

public:
        explicit MoveEvent(std::string where);
        [[nodiscard]] const std::string& getWhere() const;
};
} // namespace vlees::event

#endif // VLEESJONGEN_MOVEEVENT_H
