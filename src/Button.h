#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
public:
    Button(float x, float y, float width, float height, const sf::Texture &texture, std::function<void()> callback);

    void draw(sf::RenderWindow &window);
    void handleEvent(const sf::Event &event, const sf::RenderWindow &window);
    void update(const sf::RenderWindow &window);

private:
    sf::RectangleShape buttonShape;
    std::function<void()> onClick;

    bool isHovered = false;
    bool isClicked = false;
    sf::Vector2f originalSize;
};
