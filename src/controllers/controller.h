#ifndef VLEESJONGEN_CONTROLLER_H
#define VLEESJONGEN_CONTROLLER_H

#include "../events/baseevent.h"
#include "../object.h"
#include "../observer.h"
#include <memory>

namespace vlees::controller {
class Controller : public observer::Observer, public observer::Object
{
public:
        void update(std::shared_ptr<event::BaseEvent>& event) override;
        Controller() = default;
};
} // namespace vlees::controller

#endif // VLEESJONGEN_CONTROLLER_H
