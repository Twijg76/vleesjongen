#ifndef VLEESJONGEN_MOVABLEMODEL_H
#define VLEESJONGEN_MOVABLEMODEL_H

#include "../events/movablemovedevent.h"
#include "../position.h"
#include "model.h"
#include <complex>

namespace vlees::model {
class MovableModel : public Model
{
private:
        float xspeed = 0;
        float yspeed = 0;
        Position goal = Position(0, 0);
        Position from = Position(0, 0);
        Position position = Position(0, 0);
        std::string type;

public:
        MovableModel(float x, float y, float xgoal, float ygoal, std::string type);
        MovableModel();
        void move(double timepassed);
        void adjustPosition(double seconds) override;
        [[maybe_unused]] void setSpeed(float xspeed, float yspeed);
        Position getPosition() const;
};
} // namespace vlees::model

#endif // VLEESJONGEN_MOVABLEMODEL_H
