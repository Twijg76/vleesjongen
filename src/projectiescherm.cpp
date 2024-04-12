#include "projectiescherm.h"
#include "events/jongenmovedevent.h"

#include <SFML/Graphics/Font.hpp>
#include <utility>

#define BLOCKSIZE 50.0f

void vlees::ProjectieScherm::draw(const std::shared_ptr<sf::RenderWindow>& window)
{
        float wbreed = window->getSize().x;
        float whoog = window->getSize().y;
        scale = wbreed / width;
        if (slider > 0) {
                baseline += 2;
                slider -= 0.2;
        }
        if (autoMove > 0) {
                baseline += autoMove;
        }
        jongensprite.setTexture(jongentexture);
        if (spritewidth == 0) {
                spritewidth = jongensprite.getTextureRect().width;
        }
        spritescale = (BLOCKSIZE / spritewidth) * scale;
        float heightoffset = whoog - (scale * height);
        sf::Sprite blok;
        int i = 0;
        std::vector<Position> alleblokken = blokken;
        // add movingblokken to alleblokken
        alleblokken.insert(alleblokken.end(), movingblokken.begin(), movingblokken.end());
        /**
        for (auto& movblok : movingblokken) {
                alleblokken.push_back(movblok);
        }**/
        for (auto& bloka : alleblokken) {
                bloksprites[i].setTexture(bloktexture);
                bloksprites[i].setPosition(bloka.getX() * scale, (bloka.getY() + baseline) * scale + heightoffset);
                bloksprites[i].setScale(spritescale, spritescale);
                window->draw(bloksprites[i]);
        }

        sf::Sprite portaal;
        for (auto& port : portalen) {

                portaal.setPosition(port[0].getX() * scale, (port[0].getY() + baseline) * scale + heightoffset);
                if (port[2].getX() == 1) {
                        if (port[2].getY() == 1) {
                                portaal.setTexture(portaalboventexture);
                        } else {
                                portaal.setTexture(portaalondertexture);
                        }
                } else if (port[2].getY() == 1) {
                        portaal.setTexture(portaallinkertexture);
                } else {
                        portaal.setTexture(portaaltexture);
                }
                portaal.setScale(spritescale, spritescale);
                window->draw(portaal);
                portaal.setPosition(port[1].getX() * scale, (port[1].getY() + baseline) * scale + heightoffset);
                portaal.setScale(spritescale, spritescale);
                if (port[3].getX() == 1) {
                        if (port[3].getY() == 1) {
                                portaal.setTexture(portaalboventexture);
                        } else {
                                portaal.setTexture(portaalondertexture);
                        }
                } else if (port[3].getY() == 1) {
                        portaal.setTexture(portaallinkertexture);
                } else {
                        portaal.setTexture(portaaltexture);
                }

                window->draw(portaal);
        }

        sf::Sprite stekel;
        i = 0;
        std::vector<Position> allestekels = stekels;
        for (auto& movstekel : movingstekels) {
                allestekels.push_back(movstekel);
        }
        for (auto& stekela : allestekels) {
                stekelsprites[i].setTexture(stekeltexture);
                stekelsprites[i].setPosition(stekela.getX() * scale,
                                             (stekela.getY() + baseline) * scale + heightoffset);
                stekelsprites[i].setScale(spritescale, spritescale);
                window->draw(stekelsprites[i]);
        }

        doelsprite.setTexture(doeltexture);
        doelsprite.setScale(spritescale, spritescale);
        doelsprite.setPosition(scale * doel.getX(), (doel.getY() + baseline) * scale + heightoffset);
        window->draw(doelsprite);

        jongensprite.setScale(spritescale, spritescale);
        jongensprite.setPosition(jongen.getX() * scale, (jongen.getY() + baseline) * scale + heightoffset);
        if ((jongen.getY() + baseline) * scale + heightoffset < 0.2 * whoog) {
                slider = 1;
        } else if ((jongen.getY() + 25 + baseline) * scale + heightoffset > whoog) {
                std::shared_ptr<vlees::event::BaseEvent> doodevent = std::make_shared<event::JongenDood>();
                notify(doodevent);
        }
        window->draw(jongensprite);
        window->display();
}

vlees::ProjectieScherm::ProjectieScherm(std::vector<Position> blokkenpos, std::vector<Position> stekelspos,
                                        const std::vector<Position>& movblokken,
                                        const std::vector<Position>& movstekels, Position doelpos, Position jongenpos,
                                        float automo, float breed, float hoog)
    : blokken(std::move(blokkenpos)), stekels(std::move(stekelspos)), doel(doelpos), jongen(jongenpos),
      autoMove(automo), width(breed), height(hoog)
{
        std::vector<sf::Color> kleuren = {sf::Color::Red,    sf::Color::Blue,    sf::Color::Green,
                                          sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan};

        if (!jongentexture.loadFromFile("../img/jongen.png")) {
                std::cout << "Error loading texture" << std::endl;
        }
        if (!bloktexture.loadFromFile("../img/blok.png")) {
                std::cout << "Error loading texture" << std::endl;
        }
        if (!doeltexture.loadFromFile("../img/doel.png")) {
                std::cout << "Error loading texture" << std::endl;
        }
        if (!stekeltexture.loadFromFile("../img/stekel.png")) {
                std::cout << "Error loading texture" << std::endl;
        }
        if (!portaaltexture.loadFromFile("../img/portaal.png")) {
                std::cout << "Error loading texture" << std::endl;
        }
        if (!portaalondertexture.loadFromFile("../img/portaalonder.png")) {
                std::cout << "Error loading texture" << std::endl;
        }
        if (!portaalboventexture.loadFromFile("../img/portaalboven.png")) {
                std::cout << "Error loading texture" << std::endl;
        }
        if (!portaallinkertexture.loadFromFile("../img/portaallinks.png")) {
                std::cout << "Error loading texture" << std::endl;
        }
        for (auto& blokpos : blokken) {
                sf::Sprite bloksprite;
                bloksprite.setTexture(bloktexture);
                bloksprite.setPosition(blokpos.getX(), blokpos.getY());

                bloksprites.push_back(bloksprite);
        }
        for (auto& blokpos : movblokken) {
                sf::Sprite bloksprite;
                bloksprite.setTexture(bloktexture);
                bloksprite.setPosition(blokpos.getX(), blokpos.getY());

                bloksprites.push_back(bloksprite);
        }
        for (auto& stekelpos : stekels) {
                sf::Sprite stekelsprite;
                stekelsprite.setTexture(stekeltexture);
                stekelsprite.setPosition(stekelpos.getX(), stekelpos.getY());

                stekelsprites.push_back(stekelsprite);
        }
        for (auto& stekelpos : movstekels) {
                sf::Sprite stekelsprite;
                stekelsprite.setTexture(stekeltexture);
                stekelsprite.setPosition(stekelpos.getX(), stekelpos.getY());

                stekelsprites.push_back(stekelsprite);
        }
        int i = 0;
        for (auto& portaal : portalen) {
                sf::Sprite portaalSprite;
                portaalSprite.setTexture(portaaltexture);
                portaalSprite.setPosition(portaal[0].getX(), portaal[0].getY());
                portaalSprite.setColor(kleuren[i]);
                if (portaal[2].getX() == 1) {
                        if (portaal[2].getY() == 1) {
                                portaalSprite.setTexture(portaalboventexture);
                        } else {
                                portaalSprite.setTexture(portaalondertexture);
                        }
                } else if (portaal[2].getY() == 1) {
                        portaalSprite.setTexture(portaallinkertexture);
                }

                portaalsprites.push_back(portaalSprite);
                sf::Sprite portaalSprite2;
                portaalSprite2.setTexture(portaaltexture);
                portaalSprite2.setPosition(portaal[1].getX(), portaal[1].getY());
                portaalSprite2.setColor(kleuren[i]);
                if (portaal[3].getX() == 1) {
                        if (portaal[3].getY() == 1) {
                                portaalSprite2.setTexture(portaalboventexture);
                        } else {
                                portaalSprite2.setTexture(portaalondertexture);
                        }
                } else if (portaal[3].getY() == 1) {
                        portaalSprite2.setTexture(portaallinkertexture);
                }
                portaalsprites.push_back(portaalSprite2);
                kleuren.erase(kleuren.begin());
                i++;
        }
        movingblokken = movblokken;
        movingstekels = movstekels;
        doelsprite.setTexture(doeltexture);
        doelsprite.setPosition(doelpos.getX(), doelpos.getY());
        sf::Sprite jongenspr;
        jongenspr.setTexture(jongentexture);
        jongenspr.setPosition(jongenpos.getX(), jongenpos.getY());
}

void vlees::ProjectieScherm::update(std::shared_ptr<event::BaseEvent>& event)
{
        if (auto moveEvent = std::dynamic_pointer_cast<event::JongenMovedEvent>(event)) {
                jongen.setX(moveEvent->getPosition().getX());
                jongen.setY(moveEvent->getPosition().getY());
        } else if (auto driemoveEvent = std::dynamic_pointer_cast<event::MovableMovedEvent>(event)) {
                if (driemoveEvent->getType() == "stekel") {
                        for (Position& stekel : movingstekels) {
                                if (stekel.getX() == driemoveEvent->getOldPosition().getX() and
                                    stekel.getY() == driemoveEvent->getOldPosition().getY()) {
                                        stekel.setX(driemoveEvent->getNewPosition().getX());
                                        stekel.setY(driemoveEvent->getNewPosition().getY());
                                        return;
                                }
                        }
                } else if (driemoveEvent->getType() == "blok") {
                        for (Position& blok : movingblokken) {
                                if (blok.getX() == driemoveEvent->getOldPosition().getX() and
                                    blok.getY() == driemoveEvent->getOldPosition().getY()) {
                                        blok.setX(driemoveEvent->getNewPosition().getX());
                                        blok.setY(driemoveEvent->getNewPosition().getY());
                                        return;
                                }
                        }
                }
        }
}
void vlees::ProjectieScherm::addPortalen(std::vector<std::vector<Position>> ports)
{
        this->portalen = std::move(ports);
}
