#ifndef VLEESJONGEN_VIEW_H
#define VLEESJONGEN_VIEW_H

#include "../models/model.h"
#include "../object.h"
#include "../observer.h"

namespace vlees::view {
class View : public observer::Observer, public observer::Object, public std::enable_shared_from_this<View>
{
private:
        std::shared_ptr<GameWindow> window;
        std::string mediafile;
        sf::Sprite sprite;
        sf::Texture texture;
        bool init = false;
        std::weak_ptr<vlees::model::Model> model;

public:
        sf::Texture& getTexture();
        sf::Sprite& getSprite();
        std::shared_ptr<GameWindow> getWindow();
        const std::string& getMediafile() const;
        bool isInit() const;

        void setInit(bool init);
        void setTexture(const sf::Texture& texture);
        void setSprite(const sf::Sprite& sprite);
        void setMediafile(const std::string& mediafile);
        void update(std::shared_ptr<event::BaseEvent>& event) override;
        void setWindow(const std::shared_ptr<GameWindow>& window);

        // constructors
        View(std::shared_ptr<GameWindow> window);
        View(std::shared_ptr<GameWindow> window, const std::string& mediafile,
             const std::shared_ptr<vlees::model::Model>& model);
        virtual void render() = 0;
};
} // namespace vlees::view

#endif // VLEESJONGEN_VIEW_H
