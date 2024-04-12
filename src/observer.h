#ifndef VLEESJONGEN_OBSERVER_H
#define VLEESJONGEN_OBSERVER_H

#include <memory>

namespace vlees::event {
class BaseEvent;
} // namespace vlees::event

namespace vlees::observer {
class Observer
{
public:
        virtual void update(std::shared_ptr<vlees::event::BaseEvent>& event) = 0;
        virtual ~Observer() = default;
};
} // namespace vlees::observer

#endif // VLEESJONGEN_OBSERVER_H
