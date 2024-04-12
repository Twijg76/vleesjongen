#include "botser.h"
#include <iostream>

#define BLOKSIZE 50.0f
#define BIJNABLOKSIZE 49.0f

vlees::Botser::Botser(vlees::Position dol, const std::vector<Position>& blokken, const std::vector<Position>& stekels)
{
        this->doel = dol;
        this->blokken = blokken;
        this->stekels = stekels;
}
void vlees::Botser::setDoel(const vlees::Position& dol) { this->doel = dol; }
void vlees::Botser::addBlok(const vlees::Position& blok) { this->blokken.push_back(blok); }
void vlees::Botser::addStekel(const vlees::Position& stekel) { this->stekels.push_back(stekel); }

bool vlees::Botser::linksbots(const vlees::Position& oldpos, const vlees::Position& newpos)
{
        float xfromold = oldpos.getX() + 1;
        float xfromnew = newpos.getX() + 1;
        float yfromnew = newpos.getY() + 1;
        float ytonew = newpos.getY() + BIJNABLOKSIZE;
        std::vector<Position> alleblokpositions = blokken;
        alleblokpositions.insert(alleblokpositions.end(), movingblokken.begin(), movingblokken.end());
        for (Position blok : alleblokpositions) {
                if ((yfromnew >= blok.getY() and yfromnew <= blok.getY() + BLOKSIZE) or
                    (ytonew >= blok.getY() and ytonew <= blok.getY() + BLOKSIZE)) {
                        if (xfromnew >= blok.getX() + BLOKSIZE / 2 and xfromnew <= blok.getX() + BLOKSIZE) {
                                if (xfromold >= blok.getX() + BLOKSIZE)
                                        return true;
                        }
                }
        }
        return false;
}

bool vlees::Botser::rechtsbots(const vlees::Position& oldpos, const vlees::Position& newpos)
{
        float xtoold = oldpos.getX() + BIJNABLOKSIZE;
        float xtonew = newpos.getX() + BIJNABLOKSIZE;
        float yfromnew = newpos.getY() + 1;
        float ytonew = newpos.getY() + BIJNABLOKSIZE;
        std::vector<Position> alleblokpositions = blokken;
        alleblokpositions.insert(alleblokpositions.end(), movingblokken.begin(), movingblokken.end());

        for (Position blok : alleblokpositions) {
                if ((yfromnew >= blok.getY() and yfromnew <= blok.getY() + BLOKSIZE) or
                    (ytonew >= blok.getY() and ytonew <= blok.getY() + BLOKSIZE)) {
                        if (xtonew >= blok.getX() and xtonew <= blok.getX() + BLOKSIZE / 2) {
                                if (xtoold <= blok.getX())
                                        return true;
                        }
                }
        }
        return false;
}

bool vlees::Botser::bovenbots(const vlees::Position& oldpos, const vlees::Position& newpos)
{
        float yfromold = oldpos.getY() + 1;
        float xfromnew = newpos.getX() + 1;
        float xtonew = newpos.getX() + BIJNABLOKSIZE;
        float yfromnew = newpos.getY() + 1;
        std::vector<Position> alleblokpositions = blokken;
        alleblokpositions.insert(alleblokpositions.end(), movingblokken.begin(), movingblokken.end());

        for (Position blok : alleblokpositions) {
                if ((xfromnew >= blok.getX() and xfromnew <= blok.getX() + BLOKSIZE) or
                    (xtonew >= blok.getX() and xtonew <= blok.getX() + BLOKSIZE)) {
                        if (yfromnew >= blok.getY() + BLOKSIZE / 2 and yfromnew <= blok.getY() + BLOKSIZE) {
                                if (yfromold >= blok.getY() + BLOKSIZE)
                                        return true;
                        }
                }
        }
        return false;
}

bool vlees::Botser::onderbots(const vlees::Position& oldpos, const vlees::Position& newpos)
{
        float ytoold = oldpos.getY() + BIJNABLOKSIZE;
        float xfromnew = newpos.getX() + 1;
        float xtonew = newpos.getX() + BIJNABLOKSIZE;
        float ytonew = newpos.getY() + BLOKSIZE;
        std::vector<Position> alleblokpositions = blokken;
        alleblokpositions.insert(alleblokpositions.end(), movingblokken.begin(), movingblokken.end());

        for (Position blok : alleblokpositions) {
                if ((xfromnew >= blok.getX() and xfromnew <= blok.getX() + BLOKSIZE) or
                    (xtonew >= blok.getX() and xtonew <= blok.getX() + BLOKSIZE)) {
                        if (ytonew >= blok.getY() and ytonew <= blok.getY() + BLOKSIZE / 2) {
                                if (ytoold <= blok.getY())
                                        return true;
                        }
                }
        }
        return false;
}

std::string vlees::Botser::springsoort(const vlees::Position& pos)
{
        if (onderbots(pos, Position(pos.getX(), pos.getY() + 3))) {
                return "onder";
        } else if (linksbots(pos, Position(pos.getX() - 3, pos.getY()))) {
                return "links";
        } else if (rechtsbots(pos, Position(pos.getX() + 3, pos.getY()))) {
                return "rechts";
        } else {
                return "lucht";
        }
}

void vlees::Botser::portaaltest(const vlees::Position& pos)
{
        float xfrom = pos.getX();
        float xto = pos.getX() + BLOKSIZE;
        float yfrom = pos.getY();
        float yto = pos.getY() + BLOKSIZE;
        for (const model::PortaalModel& portaal : portalen) {
                float portaalx = portaal.getDownPosition().getX();
                float portaaly = portaal.getDownPosition().getY();
                float portaaltox = portaal.getDownPosition().getX() + BLOKSIZE;
                float portaaltoy = portaal.getDownPosition().getY() + BLOKSIZE;
                if (xfrom >= portaalx and xfrom <= portaaltox) {
                        if ((yfrom >= portaaly and yfrom <= portaaltoy) or (yto >= portaaly and yto <= portaaltoy)) {
                                std::shared_ptr<vlees::event::BaseEvent> event = std::make_shared<event::PortaalEvent>(
                                    portaal.getUpPosition(), portaal.getDownRichting(), portaal.getUpRichting());
                                notify(event);
                        }
                } else if (xto >= portaalx and xto <= portaaltox) {
                        if ((yfrom >= portaaly and yfrom <= portaaltoy) or (yto >= portaaly and yto <= portaaltoy)) {
                                std::shared_ptr<vlees::event::BaseEvent> event = std::make_shared<event::PortaalEvent>(
                                    portaal.getUpPosition(), portaal.getDownRichting(), portaal.getUpRichting());
                                notify(event);
                        }
                }
        }
}

void vlees::Botser::wintest(const vlees::Position& pos)
{
        float xfrom = pos.getX();
        float xto = pos.getX() + BLOKSIZE;
        float yfrom = pos.getY();
        float yto = pos.getY() + BLOKSIZE;
        float doelx = doel.getX();
        float doely = doel.getY();
        float doeltox = doel.getX() + BLOKSIZE;
        float doeltoy = doel.getY() + BLOKSIZE;
        if (xfrom >= doelx and xfrom <= doeltox) {
                if ((yfrom >= doely and yfrom <= doeltoy) or (yto >= doely and yto <= doeltoy)) {
                        std::shared_ptr<vlees::event::BaseEvent> event = std::make_shared<event::GoalTouch>();
                        notify(event);
                }
        } else if (xto >= doelx and xto <= doeltox) {
                if ((yfrom >= doely and yfrom <= doeltoy) or (yto >= doely and yto <= doeltoy)) {
                        std::shared_ptr<vlees::event::BaseEvent> event = std::make_shared<event::GoalTouch>();
                        notify(event);
                }
        }
}
void vlees::Botser::update(std::shared_ptr<vlees::event::BaseEvent>& event)
{
        if (auto driemoveevent = std::dynamic_pointer_cast<event::MovableMovedEvent>(event)) {
                if (driemoveevent->getType() == "blok") {
                        for (Position& blok : movingblokken) {
                                if (blok.getX() == driemoveevent->getOldPosition().getX() and
                                    blok.getY() == driemoveevent->getOldPosition().getY()) {
                                        blok = driemoveevent->getNewPosition();
                                        return;
                                }
                        }
                } else if (driemoveevent->getType() == "stekel") {
                        for (Position& stekel : movingstekels) {
                                if (stekel.getX() == driemoveevent->getOldPosition().getX() and
                                    stekel.getY() == driemoveevent->getOldPosition().getY()) {
                                        stekel = driemoveevent->getNewPosition();
                                        return;
                                }
                        }
                }
        }
}
vlees::Botser::Botser()
{
        this->doel = Position(0, 0);
        this->blokken = std::vector<Position>();
        this->stekels = std::vector<Position>();
}
void vlees::Botser::doodtest(const vlees::Position& pos)
{
        float xfrom = pos.getX();
        float xto = pos.getX() + BLOKSIZE;
        float yfrom = pos.getY();
        float yto = pos.getY() + BLOKSIZE;
        std::vector<Position> allestekelpositions = stekels;
        allestekelpositions.insert(allestekelpositions.end(), movingstekels.begin(), movingstekels.end());
        for (Position stekel : allestekelpositions) {
                float stekelx = stekel.getX();
                float stekely = stekel.getY();
                float stekeltox = stekel.getX() + BLOKSIZE;
                float stekeltoy = stekel.getY() + BLOKSIZE;
                if (xfrom >= stekelx and xfrom <= stekeltox) {
                        if ((yfrom >= stekely and yfrom <= stekeltoy) or (yto >= stekely and yto <= stekeltoy)) {
                                std::shared_ptr<vlees::event::BaseEvent> event = std::make_shared<event::JongenDood>();
                                notify(event);
                                std::cout << "dood" << std::endl;
                        }
                } else if (xto >= stekelx and xto <= stekeltox) {
                        if ((yfrom >= stekely and yfrom <= stekeltoy) or (yto >= stekely and yto <= stekeltoy)) {
                                std::shared_ptr<vlees::event::BaseEvent> event = std::make_shared<event::JongenDood>();
                                notify(event);
                                std::cout << "dood" << std::endl;
                        }
                }
        }
}
void vlees::Botser::addMovingBlokken(const std::shared_ptr<std::vector<model::MovingBlokModel>>& moblokken)
{
        for (const auto& blok : *moblokken) {
                movingblokken.push_back(blok.getPosition());
        }
}
void vlees::Botser::addMovingStekels(const std::shared_ptr<std::vector<model::MovingStekelModel>>& mostekels)
{
        for (const model::MovingStekelModel& stekel : *mostekels) {
                movingstekels.push_back(stekel.getPosition());
        }
}
void vlees::Botser::addPortalen(const std::vector<model::PortaalModel>& ports) { this->portalen = ports; }
