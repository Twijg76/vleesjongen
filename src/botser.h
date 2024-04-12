#ifndef VLEESJONGEN_BOTSER_H
#define VLEESJONGEN_BOTSER_H

#include "events/baseevent.h"
#include "events/goaltouch.h"
#include "events/jongendood.h"
#include "events/portaalevent.h"
#include "models/movingblokmodel.h"
#include "models/movingstekelmodel.h"
#include "models/portaalmodel.h"

#include "object.h"
#include "position.h"
#include <cmath>
#include <memory>
#include <string>
#include <vector>

namespace vlees {
class Botser : public observer::Object, public observer::Observer
{
private:
        std::vector<Position> blokken;
        std::vector<Position> stekels;
        std::vector<model::PortaalModel> portalen;
        std::vector<Position> movingblokken;
        std::vector<Position> movingstekels;
        Position doel = Position(0, 0);
        float size = 50.0 / 2.0;

public:
        Botser(vlees::Position doel, const std::vector<Position>& blokken, const std::vector<Position>& stekels);
        void addBlok(const Position& blok);
        void addStekel(const Position& stekel);
        void addMovingBlokken(const std::shared_ptr<std::vector<model::MovingBlokModel>>& moblokken);
        void addMovingStekels(const std::shared_ptr<std::vector<model::MovingStekelModel>>& mostekels);
        void addPortalen(const std::vector<model::PortaalModel>& portalen);
        void setDoel(const Position& dol);
        Botser();
        bool rechtsbots(const Position& oldpos, const Position& newpos);
        bool bovenbots(const Position& oldpos, const Position& newpos);
        bool onderbots(const Position& oldpos, const Position& newpos);
        bool linksbots(const Position& oldpos, const Position& newpos);
        std::string springsoort(const Position& pos);
        void wintest(const Position& pos);
        void doodtest(const Position& pos);
        void portaaltest(const Position& pos);
        void update(std::shared_ptr<vlees::event::BaseEvent>& event) override;
};
} // namespace vlees

#endif // VLEESJONGEN_BOTSER_H
