#include "jongenmodel.h"

vlees::model::JongenModel::JongenModel(const float x, const float y) : position(x, y) {}
void vlees::model::JongenModel::move(double timepassed)
{
        if (yspeed > -150) {
                yspeed -= 3;
        }

        float newx = position.getX() + xspeed * timepassed;
        float newy = position.getY() - yspeed * timepassed;
        bool onderbots = botser->onderbots(position, Position(newx, newy));
        bool bovenbots = botser->bovenbots(position, Position(newx, newy));
        bool linksbots = botser->linksbots(position, Position(newx, newy));
        bool rechtsbots = botser->rechtsbots(position, Position(newx, newy));

        if (linksbots or rechtsbots) {
                xspeed = 0;
                newx = position.getX();
        }
        if (bovenbots) {
                yspeed = -yspeed;
                newy = position.getY();
        } else if (onderbots) {
                yspeed = 0;
                newy = position.getY();
        }

        position.setX(newx);
        position.setY(newy);
        botser->wintest(position);
        botser->doodtest(position);
        botser->portaaltest(position);
        xspeed *= 0.95;
        std::shared_ptr<vlees::event::BaseEvent> event = std::make_shared<event::JongenMovedEvent>(position);
        notify(event);
}

void vlees::model::JongenModel::update(std::shared_ptr<event::BaseEvent>& event)
{
        if (auto moveEvent = std::dynamic_pointer_cast<event::MoveEvent>(event)) {
                if (moveEvent->getWhere() == "left") {
                        xspeed = -100;
                } else if (moveEvent->getWhere() == "right") {
                        xspeed = 100;
                } else if (moveEvent->getWhere() == "jump") {
                        std::string soort = botser->springsoort(position);
                        if (soort == "links") {
                                xspeed = 100;
                                yspeed = 100;
                        } else if (soort == "rechts") {
                                xspeed = -100;
                                yspeed = 100;
                        } else if (soort == "onder") {
                                yspeed = 100;
                        }
                }
        } else if (auto win = std::dynamic_pointer_cast<event::GoalTouch>(event)) {
                xspeed = 0;
                yspeed = 0;
                notify(event);
        } else if (auto dood = std::dynamic_pointer_cast<event::JongenDood>(event)) {
                xspeed = 0;
                yspeed = 0;
                notify(event);
        } else if (auto port = std::dynamic_pointer_cast<event::PortaalEvent>(event)) {
                notify(event);
        }
}

vlees::model::JongenModel::JongenModel() { position = Position(0, 0); }
void vlees::model::JongenModel::adjustPosition(double seconds) {}
void vlees::model::JongenModel::setPosition(const vlees::Position& pos) { position = pos; }
[[maybe_unused]] vlees::Position vlees::model::JongenModel::getPosition() const { return position; }
void vlees::model::JongenModel::turn(float degrees)
{
        if (degrees == 90) {
                xspeed = yspeed;
                yspeed = -xspeed;
        } else if (degrees == 180) {
                xspeed = -xspeed;
                yspeed = -yspeed;
        } else if (degrees == 270) {
                xspeed = -yspeed;
                yspeed = xspeed;
        }
}
