#ifndef VLEESJONGEN_SCREEN_H
#define VLEESJONGEN_SCREEN_H

#include "../json.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <fstream>
#include <iostream>
#include <string>

// https://github.com/SFML/SFML/wiki/Tutorial%3A-Manage-different-Screens
namespace vlees::screen {
class cScreen
{
public:
        virtual std::string Run(std::shared_ptr<sf::RenderWindow> window) = 0;
};

class screen_menu : public cScreen
{
private:
        int alpha_max;
        bool playing;

public:
        screen_menu();
        std::string Run(std::shared_ptr<sf::RenderWindow> window) override;
};

class screen_game : public cScreen
{
private:
        std::string levelfile;

public:
        explicit screen_game(std::string levelfile);
        std::string Run(std::shared_ptr<sf::RenderWindow> window) override;
};
} // namespace vlees::screen

#endif // VLEESJONGEN_SCREEN_H
