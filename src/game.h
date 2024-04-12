#ifndef INC_2022_PROJECT_BLIVENS_GAME_H
#define INC_2022_PROJECT_BLIVENS_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "events/baseevent.h"

#include "clock.h"
#include "observer.h"

#include "../json.hpp"
#include "events/sfmlevent.h"

#include <fstream>
#include <map>

#include "botser.h"
#include "controllers/jongencontroller.h"
#include "models/jongenmodel.h"
#include "models/movablemodel.h"
#include "models/movingblokmodel.h"
#include "models/movingstekelmodel.h"
#include "models/portaalmodel.h"

#include "projectiescherm.h"

namespace vlees {

class Game : public observer::Observer, public observer::Object, public std::enable_shared_from_this<Game>
{
private:
        std::shared_ptr<sf::RenderWindow> window;
        bool running = true;
        std::string levelfile;
        std::shared_ptr<Botser> botser = std::make_shared<Botser>();
        std::vector<sf::Texture> textures;
        std::vector<sf::Sprite> sprites;
        std::shared_ptr<model::JongenModel> jongenmodel;
        std::shared_ptr<controller::JongenController> jongencontroller;
        std::shared_ptr<ProjectieScherm> projectiescherm =
            std::make_shared<ProjectieScherm>(std::vector<Position>(), std::vector<Position>(), std::vector<Position>(),
                                              std::vector<Position>(), Position(0, 0), Position(0, 0), 0, 0, 0);
        std::shared_ptr<std::vector<model::MovingBlokModel>> movingblokken;
        std::shared_ptr<std::vector<model::MovingStekelModel>> movingstekels;
        std::vector<model::PortaalModel> portalen;
        std::string runLoop();

public:
        void update(std::shared_ptr<event::BaseEvent>& event) override;
        std::string Start();
        void loadLevel(const std::string& levelname);
        void Load(std::string lfile);
        explicit Game(std::shared_ptr<sf::RenderWindow> window);
};
} // namespace vlees

#endif // INC_2022_PROJECT_BLIVENS_GAME_H
