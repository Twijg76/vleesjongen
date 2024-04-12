#include "game.h"
#include "screen.h"
#include <iostream>

int main()
{
        vlees::screen::screen_menu menu_screen;
        std::shared_ptr<sf::RenderWindow> gameProgram =
            std::make_shared<sf::RenderWindow>(sf::VideoMode(600, 600), "Vleesjongen");
        gameProgram->setFramerateLimit(60);
        gameProgram->setMouseCursorVisible(false);

        std::string screen = "menu";
        while (screen != "exit") {
                if (screen == "menu") {
                        screen = menu_screen.Run(gameProgram);
                } else {
                        vlees::screen::screen_game level = vlees::screen::screen_game(screen);
                        screen = level.Run(gameProgram);
                }
        }
        return 0;
}
