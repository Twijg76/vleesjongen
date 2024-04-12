#ifndef VLEESJONGEN_JONGENCONTROLLER_H
#define VLEESJONGEN_JONGENCONTROLLER_H

#include "../events/moveevent.h"
#include "../events/sfmlevent.h"
#include "../models/jongenmodel.h"
#include "controller.h"
#include <SFML/Window/Event.hpp>

namespace vlees::controller {
class JongenController : public Controller
{
public:
        JongenController() = default;
        void update(std::shared_ptr<event::BaseEvent>& event) override;
};
} // namespace vlees::controller

#endif // VLEESJONGEN_JONGENCONTROLLER_H
