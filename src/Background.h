#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Background
{
public:
    struct Data
    {
        int x, y, w, h;
        std::string path;
        sf::Texture texture;
        sf::Sprite sprite;
    };

    //////Constructors //////

    Background(Data bgData, int parallaxFactor);

    //////Methods//////

    void update(sf::Vector2f playerPosition);
    void draw(sf::RenderWindow &window);

    sf::Vector2f getPosition() const;

    void setPosition(float x, float y);

    Data bgData;
    int parallaxFactor;
};
