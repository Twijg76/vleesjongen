#include "view.h"
#include "../events/removeevent.h"
#include "../events/renderevent.h"

sf::Texture& vlees::view::View::getTexture() { return texture; }

sf::Sprite& vlees::view::View::getSprite() { return sprite; }

std::shared_ptr<vlees::GameWindow> vlees::view::View::getWindow() { return window; }

const std::string& vlees::view::View::getMediafile() const { return mediafile; }

bool vlees::view::View::isInit() const { return init; }

void vlees::view::View::setInit(bool init) { View::init = init; }

void vlees::view::View::setTexture(const sf::Texture& texture) { View::texture = texture; }

void vlees::view::View::setSprite(const sf::Sprite& sprite) { View::sprite = sprite; }

void vlees::view::View::setMediafile(const std::string& mediafile) { View::mediafile = mediafile; }

void vlees::view::View::update(std::shared_ptr<vlees::event::BaseEvent>& event)
{
        if (auto e = std::dynamic_pointer_cast<event::RenderEvent>(event)) {
                render();
        } else if (auto e2 = std::dynamic_pointer_cast<event::RemoveEvent>(event)) {
                // remove the view from the window TODO
        }
}

void vlees::view::View::setWindow(const std::shared_ptr<GameWindow>& wind) { window = wind; }

vlees::view::View::View(std::shared_ptr<GameWindow> wind) { window = wind; }

vlees::view::View::View(std::shared_ptr<GameWindow> window, const std::string& mediafile,
                        const std::shared_ptr<vlees::model::Model>& mod)
    : window(std::move(window)), model(mod)
{
        setMediafile(mediafile);
}
