#include <SFML/Graphics.hpp>
#include <string>
#include "Background.h"

//////Constructors //////

Background::Background(Data bgData, int parallaxFactor)
    : bgData(bgData), parallaxFactor(parallaxFactor)
{
    if (!bgData.texture.loadFromFile(bgData.path))
    {
        // Handle error
    }
    bgData.sprite.setTexture(bgData.texture);
    bgData.sprite.setPosition(bgData.x, bgData.y);
}

//////Methods//////

void Background::update(sf::Vector2f playerPosition)
{
    bgData.sprite.setPosition(bgData.x - playerPosition.x / parallaxFactor, bgData.y - playerPosition.y / parallaxFactor);
}

void Background::draw(sf::RenderWindow &window)
{
    window.draw(bgData.sprite);
}

sf::Vector2f Background::getPosition() const
{
    return bgData.sprite.getPosition();
}

void Background::setPosition(float x, float y)
{
    bgData.sprite.setPosition(x, y);
}
