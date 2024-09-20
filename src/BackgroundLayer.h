#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Background.h"

class BackgroundLayer
{
public:
    //////Constructors //////

    BackgroundLayer(const Background::Data &bgData, int parallaxFactor, int screenWidth, int screenHeight);

    //////Methods//////

    void update(sf::Vector2f playerPosition);
    void draw(sf::RenderWindow &window);

private:
    std::vector<Background> backgrounds;
    int screenWidth, screenHeight;
    int parallaxFactor;

    void repositionBackgrounds(sf::Vector2f playerPosition);
};
