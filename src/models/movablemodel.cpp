#include "movablemodel.h"

vlees::model::MovableModel::MovableModel(const float x, const float y, const float xgoal, const float ygoal,
                                         std::string typ)
{
        type = std::move(typ);
        position = Position(x, y);
        goal = Position(xgoal, ygoal);
        from = Position(x, y);
        double distance = std::sqrt(std::pow(xgoal - x, 2) + std::pow(ygoal - y, 2));
        const double speed = 60;
        double time = distance / speed;
        xspeed = (xgoal - x) / time;
        yspeed = (ygoal - y) / time;

        /**
        if (xgoal > x) {
                xspeed = 60;
        } else if (xgoal < x) {
                xspeed = -60;
        } else {
                xspeed = 0;
        }
        if (ygoal > y) {
                yspeed = 60;
        } else if (ygoal < y) {
                yspeed = -60;
        } else {
                yspeed = 0;
        }**/
}

void vlees::model::MovableModel::move(double timepassed)
{
        float newx = position.getX() + xspeed * timepassed;
        float newy = position.getY() + yspeed * timepassed;
        float maxx = std::max(from.getX(), goal.getX());
        float minx = std::min(from.getX(), goal.getX());
        float maxy = std::max(from.getY(), goal.getY());
        float miny = std::min(from.getY(), goal.getY());
        if (xspeed > 0) {
                if (newx >= maxx) {
                        newx = maxx;
                        xspeed = -xspeed;
                }
        } else if (xspeed < 0) {
                if (newx <= minx) {
                        newx = minx;
                        xspeed = -xspeed;
                }
        }

        if (yspeed > 0) {
                if (newy >= maxy) {
                        newy = maxy;
                        yspeed = -yspeed;
                }
        } else if (yspeed < 0) {
                if (newy <= miny) {
                        newy = miny;
                        yspeed = -yspeed;
                }
        }
        Position oldposition = position;
        position.setX(newx);
        position.setY(newy);
        std::shared_ptr<vlees::event::BaseEvent> event =
            std::make_shared<event::MovableMovedEvent>(type, oldposition, position);
        notify(event);
}

vlees::Position vlees::model::MovableModel::getPosition() const { return position; }

vlees::model::MovableModel::MovableModel() { position = Position(0, 0); }
void vlees::model::MovableModel::adjustPosition(double seconds) {}
[[maybe_unused]] void vlees::model::MovableModel::setSpeed(float xspee, float yspee)
{
        this->xspeed = xspee;
        this->yspeed = yspee;
}
