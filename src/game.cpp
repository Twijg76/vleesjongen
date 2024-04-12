#include "game.h"
#include "events/jongendood.h"

#include <utility>

#define BLOCKSIZE 50.0f

namespace vlees {
Game::Game(std::shared_ptr<sf::RenderWindow> windowww)
{
        window = std::move(windowww);
        jongenmodel = std::make_shared<model::JongenModel>(0, 0);
        jongencontroller = std::make_shared<controller::JongenController>();
        auto selfpointer = std::shared_ptr<Game>(this, [](Game*) {});
        movingstekels = std::make_shared<std::vector<model::MovingStekelModel>>();
        movingblokken = std::make_shared<std::vector<model::MovingBlokModel>>();
}

void Game::Load(std::string lfile)
{
        levelfile = std::move(lfile);
        std::vector<Position> positions;
}

std::string Game::Start()
{
        try {
                loadLevel(levelfile);
                std::string out = runLoop();
                return out;
        } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
        }
        return "menu";
}

std::string Game::runLoop()
{
        double timeperframe = (1000000000.0 / 60);
        window->setTitle("VleesJongen");
        while (window->isOpen() and running) {
                if (Clock::getInstance().secondsSinceReset() > timeperframe) {
                        sf::Event event{};
                        double seconds = Clock::getInstance().secondsSinceReset() / 1000000000;

                        Clock::getInstance().restartTime();
                        while (window->pollEvent(event)) {
                                if (event.type == sf::Event::Closed) {
                                        window->close();
                                        return "exit";
                                } else if (event.type == sf::Event::Resized) {
                                        sf::FloatRect view(0, 0, event.size.width, event.size.height);
                                        window->setView(sf::View(view));

                                } else if (event.type == sf::Event::KeyPressed) {
                                        if (event.key.code == sf::Keyboard::Escape) {
                                                return "menu";
                                        } else {
                                                std::shared_ptr<event::BaseEvent> ev =
                                                    std::make_shared<event::SFMLEvent>(event);
                                                jongencontroller->update(ev);
                                        }
                                }
                        }
                        window->clear(sf::Color::White);
                        for (auto& sprite : sprites) {
                                window->draw(sprite);
                        }
                        jongenmodel->move(seconds);
                        // move the movingblokken and movingstekels
                        for (auto& blok : *movingblokken) {
                                blok.move(seconds);
                        }
                        for (auto& stekel : *movingstekels) {
                                stekel.move(seconds);
                        }
                        projectiescherm->draw(window);
                        window->display();
                }
        }
        return "menu";
}

void Game::update(std::shared_ptr<event::BaseEvent>& event)
{
        if (auto ev = std::dynamic_pointer_cast<event::GoalTouch>(event)) {
                std::cout << "goal" << std::endl;
                sf::Font font;
                if (!font.loadFromFile("../Arial.ttf")) {
                        std::cerr << "kan font niet vinden" << std::endl;
                }
                sf::Text text;
                text.setFont(font);
                text.setString("Proficiat!");
                text.setCharacterSize(24);
                text.setFillColor(sf::Color(255, 0, 0, 255));
                text.setPosition(100, 100);
                window->clear(sf::Color(10, 50, 10, 0));
                window->draw(text);
                window->display();
                sf::sleep(sf::seconds(2));
                running = false;
        } else if (auto evdood = std::dynamic_pointer_cast<event::JongenDood>(event)) {
                std::cout << "dood" << std::endl;
                sf::Font font;
                if (!font.loadFromFile("../Arial.ttf")) {
                        std::cerr << "kan font niet vinden" << std::endl;
                }
                sf::Text text;
                text.setFont(font);
                text.setString("spijtig :(");
                text.setCharacterSize(24);
                text.setFillColor(sf::Color(255, 0, 0, 255));
                text.setPosition(100, 100);
                window->clear(sf::Color(10, 50, 10, 0));
                window->draw(text);
                window->display();
                sf::sleep(sf::seconds(2));
                running = false;
        } else if (auto evportaal = std::dynamic_pointer_cast<event::PortaalEvent>(event)) {
                std::cout << "portaal" << std::endl;
                Position pos = evportaal->getDest();
                jongenmodel->setPosition(pos);
                std::string fromrichting = evportaal->getFromrichting();
                std::string torichting = evportaal->getTorichting();
                if (fromrichting == "right") {
                        if (torichting == "up") {
                                jongenmodel->turn(270);
                        } else if (torichting == "down") {
                                jongenmodel->turn(90);
                        } else if (torichting == "left") {
                                jongenmodel->turn(180);
                        }
                } else if (fromrichting == "down") {
                        if (torichting == "up") {
                                jongenmodel->turn(180);
                        } else if (torichting == "right") {
                                jongenmodel->turn(270);
                        } else if (torichting == "left") {
                                jongenmodel->turn(90);
                        }
                } else if (fromrichting == "left") {
                        if (torichting == "up") {
                                jongenmodel->turn(90);
                        } else if (torichting == "right") {
                                jongenmodel->turn(180);
                        } else if (torichting == "down") {
                                jongenmodel->turn(270);
                        }
                } else if (fromrichting == "up") {
                        if (torichting == "right") {
                                jongenmodel->turn(90);
                        } else if (torichting == "down") {
                                jongenmodel->turn(180);
                        } else if (torichting == "left") {
                                jongenmodel->turn(270);
                        }
                }
        }
}

void Game::loadLevel(const std::string& filename)
{
        nlohmann::json level;
        std::ifstream file("../levels/" + filename);
        if (file.is_open()) {
                level = nlohmann::json::parse(file);
        } else {
                std::cerr << "kan level niet vinden" << std::endl;
        }
        file.close();
        float x = 0;
        float y = 0;
        botser = std::make_shared<vlees::Botser>();
        std::vector<Position> blokken;
        std::vector<Position> stekels;
        std::vector<Position> movingblokkenpos;
        std::vector<Position> movingstekelspos;
        Position jongenpos = Position(0, 0);
        Position doelpos = Position(0, 0);
        float automove = level["automove"];
        float br = 0;
        float ho = 0;
        std::array<char, 10> cijfers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        unsigned short int movecounter = 0;
        for (std::string row : level["layout"]) {
                ho += 1;
                float t = 0;
                for (auto el : row) {
                        t += 1;
                        // if it is an 'x', add a blok, if it is a p, add the jongen, if it is an s, add a stekel
                        if (el == 'x') {
                                blokken.emplace_back(x, y);
                                botser->addBlok(Position(x, y));
                                x += BLOCKSIZE;

                        } else if (el == 'j') {
                                jongenmodel->setPosition(Position(x, y));
                                jongenmodel->botser = botser;
                                jongenpos = Position(x, y);
                                x += BLOCKSIZE;

                        } else if (el == 'd') {
                                doelpos = Position(x, y);
                                botser->setDoel(Position(x, y));
                                x += BLOCKSIZE;

                        } else if (el == '_') {
                                x += BLOCKSIZE;
                        } else if (el == 's') {
                                stekels.emplace_back(x, y);
                                botser->addStekel(Position(x, y));
                                x += BLOCKSIZE;
                        } else if (el == 'm') {
                                if (level["movers"][movecounter]["type"] == "s") {
                                        float up = level["movers"][movecounter]["up"];
                                        float right = level["movers"][movecounter]["right"];
                                        float goalx = x + right * BLOCKSIZE;
                                        float goaly = y - up * BLOCKSIZE;
                                        movingstekels->emplace_back(x, y, goalx, goaly);
                                        // auto mover = std::make_shared<model::MovingStekelModel>(x, y, goalx, goaly);
                                        // mover->attach(projectiescherm);
                                        // movingstekels.push_back(*mover);
                                        movingstekels->back().attach(projectiescherm);
                                        movingstekelspos.emplace_back(x, y);
                                        movecounter++;
                                } else if (level["movers"][movecounter]["type"] == "x") {
                                        float up = level["movers"][movecounter]["up"];
                                        float right = level["movers"][movecounter]["right"];
                                        float goalx = x + right * BLOCKSIZE;
                                        float goaly = y - up * BLOCKSIZE;
                                        // auto mover = std::make_shared<model::MovingBlokModel>(x, y, goalx, goaly);
                                        // mover->attach(projectiescherm);
                                        // movingblokken->push_back(*mover);
                                        movingblokken->emplace_back(x, y, goalx, goaly);
                                        movingblokkenpos.emplace_back(x, y);
                                        movecounter++;
                                }
                        } else if (std::find(cijfers.begin(), cijfers.end(), el) != cijfers.end()) {
                                bool found = false;
                                for (model::PortaalModel& portaal : portalen) {
                                        if (portaal.getId() == el) {
                                                portaal.addDown(Position(x, y));
                                                std::string id(1, el);
                                                found = true;

                                                portaal.setDownRichting(level["portals"][id]["downricht"]);
                                                portaal.setUpRichting(level["portals"][id]["upricht"]);
                                        }
                                }
                                if (!found) {
                                        portalen.emplace_back(Position(x, y), Position(0, 0), el);
                                }
                                x += BLOCKSIZE;
                        }
                }
                if (t > br) {
                        br = t;
                }
                x = 0;
                y += BLOCKSIZE;
        }

        projectiescherm =
            std::make_shared<vlees::ProjectieScherm>(blokken, stekels, movingblokkenpos, movingstekelspos, doelpos,
                                                     jongenpos, automove, br * BLOCKSIZE, ho * BLOCKSIZE);
        std::vector<std::vector<Position>> portalenpos;
        for (auto& port : portalen) {
                std::string downpos = port.getDownRichting();
                std::string uppos = port.getUpRichting();
                Position downricht = Position(0, 0);
                Position upricht = Position(0, 0);
                if (downpos == "up") {
                        downricht = Position(1, 1);
                } else if (downpos == "down") {
                        downricht = Position(1, 0);
                } else if (downpos == "left") {
                        downricht = Position(0, 1);
                }
                if (uppos == "up") {
                        upricht = Position(1, 1);
                } else if (uppos == "down") {
                        upricht = Position(1, 0);
                } else if (uppos == "left") {
                        upricht = Position(0, 1);
                }
                portalenpos.push_back({port.getUpPosition(), port.getDownPosition(), upricht, downricht});
        }
        projectiescherm->addPortalen(portalenpos);
        botser->addPortalen(portalen);
        jongenmodel->attach(projectiescherm);
        projectiescherm->attach(jongenmodel);
        botser->addMovingBlokken(movingblokken);
        botser->addMovingStekels(movingstekels);
        botser->attach(jongenmodel);
        jongenmodel->attach(shared_from_this());
        jongencontroller->attach(jongenmodel);
        projectiescherm->attach(shared_from_this());
        for (auto& blok : *movingblokken) {
                blok.attach(projectiescherm);
                blok.attach(botser);
        }
        for (auto& stekel : *movingstekels) {
                stekel.attach(projectiescherm);
                stekel.attach(botser);
        }
}

} // namespace vlees
