#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Background
{
public:
    Background(sf::RenderWindow &window, const std::string &texturePath);

    void update(const sf::Vector2f &playerPosition, float parallax);
    void draw(sf::RenderWindow &window);

private:
    sf::RenderWindow &window;
    std::shared_ptr<sf::Texture> texture;
    std::vector<sf::Sprite> sprites;
    sf::Vector2f previousPlayerPosition;
};

#endif