#include "jongencontroller.h"

void vlees::controller::JongenController::update(std::shared_ptr<event::BaseEvent>& event)
{

        if (auto keyEvent = std::dynamic_pointer_cast<event::SFMLEvent>(event)) {
                auto keyevent = keyEvent->getRealEvent().type;
                if (keyevent == sf::Event::KeyPressed) {
                        sf::Keyboard::Key key = keyEvent->getRealEvent().key.code;
                        if (key == sf::Keyboard::Left or key == sf::Keyboard::A or key == sf::Keyboard::Q) {
                                std::shared_ptr<event::BaseEvent> ev = std::make_shared<event::MoveEvent>("left");
                                notify(ev);
                        } else if (key == sf::Keyboard::Right or key == sf::Keyboard::D) {
                                std::shared_ptr<event::BaseEvent> ev = std::make_shared<event::MoveEvent>("right");
                                notify(ev);
                        } else if (key == sf::Keyboard::Space) {
                                std::shared_ptr<event::BaseEvent> ev = std::make_shared<event::MoveEvent>("jump");
                                notify(ev);
                        }
                }
        }
}
