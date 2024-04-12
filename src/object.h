#ifndef VLEESJONGEN_OBJECT_H
#define VLEESJONGEN_OBJECT_H

#include "observer.h"
#include <list>

namespace vlees::observer {
class Object
{
public:
        void attach(const std::shared_ptr<Observer>& observer);
        [[maybe_unused]] void detach(const std::shared_ptr<Observer>& observer);
        void notify(std::shared_ptr<event::BaseEvent>& event);

private:
        std::list<std::weak_ptr<Observer>> observers;
};
} // namespace vlees::observer

#endif // VLEESJONGEN_OBJECT_H
