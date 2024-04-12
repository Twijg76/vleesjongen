#ifndef VLEESJONGEN_JONGENMODEL_H
#define VLEESJONGEN_JONGENMODEL_H

#include "../botser.h"
#include "../events/jongendood.h"
#include "../events/jongenmovedevent.h"
#include "../events/moveevent.h"
#include "../position.h"
#include "model.h"

namespace vlees::model {
class JongenModel : public Model
{
private:
        float xspeed = 0;
        float yspeed = 0;
        Position position = Position(0, 0);

public:
        JongenModel(float x, float y);
        JongenModel();
        std::shared_ptr<Botser> botser;
        // void setXSpeed(float xspeed);
        // void setYSpeed(float yspeed);
        //  bool outOfRange(); nakijken bij beeld, de objecten weten niet waar het beeld zit
        void move(double timepassed);
        void update(std::shared_ptr<event::BaseEvent>& event) override;
        void adjustPosition(double seconds) override;
        [[maybe_unused]] [[maybe_unused]] Position getPosition() const;
        void setPosition(const Position& pos);
        void turn(float degrees);
};
} // namespace vlees::model

#endif // VLEESJONGEN_JONGENMODEL_H
