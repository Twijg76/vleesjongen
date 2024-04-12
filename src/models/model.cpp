#include "model.h"

// handle an event you observe
void vlees::model::Model::update(std::shared_ptr<vlees::event::BaseEvent>& event)
{
        if (auto e = std::dynamic_pointer_cast<event::Adjust>(event)) {
                adjustPosition(e->getSeconds());
        }
}
