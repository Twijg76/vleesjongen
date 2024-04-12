#include "object.h"

void vlees::observer::Object::attach(const std::shared_ptr<observer::Observer>& observer)
{
        observers.push_back(observer);
}

[[maybe_unused]] void vlees::observer::Object::detach(const std::shared_ptr<observer::Observer>& observer)
{
        // iterate over the observers list and remove the observer
        for (auto it = observers.begin(); it != observers.end(); ++it) {
                if (it->lock() == observer) {
                        observers.erase(it);
                        break;
                }
        }
}

void vlees::observer::Object::notify(std::shared_ptr<event::BaseEvent>& event)
{
        // iterate over the observers list and notify all observers
        for (const auto& it : observers) {
                if (auto observer = it.lock()) {
                        observer->update(event);
                }
        }
}
