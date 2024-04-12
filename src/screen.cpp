#include "screen.h"
#include "game.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <utility>

vlees::screen::screen_menu::screen_menu()
{
        alpha_max = 3 * 255;
        playing = false;
}

std::string vlees::screen::screen_menu::Run(std::shared_ptr<sf::RenderWindow> window)
{

        sf::Font font;
        sf::Event event{};
        if (!font.loadFromFile("../Arial.ttf")) {
                std::cerr << "kan font niet vinden" << std::endl;
                return ("exit");
        }
        int alpha = 0;
        // read index.json
        nlohmann::json jfile;
        std::ifstream file("../levels/index.json");
        jfile = nlohmann::json::parse(file);
        std::vector<std::string> levelfiles;
        file.close();
        // create level buttons

        std::vector<std::shared_ptr<sf::Text>> levels;
        for (auto& item : jfile["levels"]) {
                std::shared_ptr<sf::Text> level = std::make_shared<sf::Text>();
                level->setFont(font);
                level->setCharacterSize(24);
                level->setString(item.value("name", "unknown"));
                levelfiles.push_back(item.value("file", "unknown"));
                level->setPosition(sf::Vector2f(100, 100.0f + (levels.size() * 50.0f)));
                levels.push_back(level);
        }
        if (playing) {
                alpha = alpha_max;
        }
        int levelnum = 0;
        while (window->isOpen()) {
                while (window->pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                                return "exit";
                        } else if (event.type == sf::Event::KeyPressed) {
                                switch (event.key.code) {
                                case sf::Keyboard::Up:
                                        if (levelnum > 0) {
                                                levelnum--;
                                        }
                                        break;
                                case sf::Keyboard::Down:
                                        if (levelnum < levels.size() - 1) {
                                                levelnum++;
                                        }
                                        break;
                                case sf::Keyboard::Return:
                                        std::cout << "loading level " << levelfiles[levelnum] << std::endl;
                                        playing = true;
                                        return levelfiles[levelnum];

                                case sf::Keyboard::Escape:
                                        return "exit";
                                default:
                                        break;
                                }
                        } else if (event.type == sf::Event::Resized) {
                                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                                window->setView(sf::View(view));
                        }
                }
                if (alpha < alpha_max) {
                        alpha++;
                }
                for (int i = 0; i < levels.size(); i++) {
                        if (i == levelnum) {
                                levels[i]->setFillColor(sf::Color(255, 0, 0, 255));
                        } else {
                                levels[i]->setFillColor(sf::Color(255, 255, 255, 255));
                        }
                }
                window->clear(sf::Color(10, 50, 10, 0));
                for (auto& level : levels) {
                        window->draw(*level);
                }
                window->display();
        }
        return ("exit");
}
vlees::screen::screen_game::screen_game(std::string lfile) { levelfile = std::move(lfile); }
std::string vlees::screen::screen_game::Run(std::shared_ptr<sf::RenderWindow> window)
{

        std::shared_ptr<vlees::Game> game = std::make_shared<vlees::Game>(window);
        game->Load(levelfile);
        std::string out = game->Start();
        return out;
}
