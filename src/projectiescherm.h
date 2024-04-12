#ifndef VLEESJONGEN_PROJECTIESCHERM_H
#define VLEESJONGEN_PROJECTIESCHERM_H

#include "botser.h"
#include "events/jongendood.h"
#include "events/jongenmovedevent.h"
#include "events/movablemovedevent.h"
#include "object.h"
#include "observer.h"
#include "position.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

namespace vlees {

class ProjectieScherm : public observer::Object, public observer::Observer
{
private:
        sf::Texture bloktexture;
        sf::Texture jongentexture;
        sf::Texture doeltexture;
        sf::Texture stekeltexture;
        sf::Texture portaaltexture;
        sf::Texture portaalondertexture;
        sf::Texture portaalboventexture;
        sf::Texture portaallinkertexture;
        std::vector<sf::Sprite> bloksprites;
        std::vector<sf::Sprite> stekelsprites;
        std::vector<sf::Sprite> portaalsprites;
        sf::Sprite jongensprite;
        sf::Sprite doelsprite;
        float autoMove = 0.0;
        Position doel;
        Position jongen;
        std::vector<Position> blokken;
        std::vector<Position> stekels;
        std::vector<Position> movingblokken;
        std::vector<Position> movingstekels;
        std::vector<std::vector<Position>> portalen;
        float baseline = 0;
        float scale = 1;
        float spritescale = 1;
        float width = 0;
        float height = 0;
        float slider = 0;
        float spritewidth = 0;

public:
        ProjectieScherm(std::vector<Position> blokken, std::vector<Position> stekels,
                        const std::vector<Position>& movingblokken, const std::vector<Position>& movingstekels,
                        Position doelpos, Position jongenpos, float automove, float breed, float hoog);
        void update(std::shared_ptr<event::BaseEvent>& event) override;
        void draw(const std::shared_ptr<sf::RenderWindow>& window);
        void addPortalen(std::vector<std::vector<Position>> portalen);
};
} // namespace vlees

#endif // VLEESJONGEN_PROJECTIESCHERM_H
