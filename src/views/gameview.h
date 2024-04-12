#ifndef VLEESJONGEN_GAMEVIEW_H
#define VLEESJONGEN_GAMEVIEW_H

#include "view.h"

namespace sf {
class RenderWindow;
} // namespace sf

namespace vlees::view {
class GameView : public View
{
private:
        sf::RenderWindow& window;

public:
        explicit GameView(sf::RenderWindow& window);
        void draw();
};
} // namespace vlees::view

#endif // VLEESJONGEN_GAMEVIEW_H
