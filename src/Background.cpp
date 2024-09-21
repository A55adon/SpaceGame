#include "Background.h"
#include <iostream>
#include <cmath>
#include <memory>

Background::Background(sf::RenderWindow &window, const std::string &texturePath) : window(window)
{
    texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(texturePath))
    {
        std::cout << "Error loading texture for background" << std::endl;
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sf::Sprite sprite(*texture);
            sprite.setPosition(i * 2000.f, j * 2000.f);
            sprites.push_back(sprite);
        }
    }

    previousPlayerPosition = sf::Vector2f(0.f, 0.f);
}

void Background::update(const sf::Vector2f &playerPosition, float parallax)
{
    const float textureWidth = 2000.f;
    const float textureHeight = 2000.f;

    const float parallaxFactor = parallax;

    sf::Vector2f playerOffset = playerPosition - previousPlayerPosition;
    previousPlayerPosition = playerPosition;

    float offsetX = playerOffset.x * parallaxFactor;
    float offsetY = playerOffset.y * parallaxFactor;

    for (size_t i = 0; i < sprites.size(); i++)
    {
        sf::Vector2f currentPosition = sprites[i].getPosition();

        sprites[i].setPosition(currentPosition.x + offsetX, currentPosition.y + offsetY);
    }

    for (auto &sprite : sprites)
    {
        sf::Vector2f position = sprite.getPosition();

        if (position.x + textureWidth < playerPosition.x - textureWidth)
            sprite.setPosition(position.x + 3 * textureWidth, position.y);
        if (position.x > playerPosition.x + textureWidth)
            sprite.setPosition(position.x - 3 * textureWidth, position.y);

        if (position.y + textureHeight < playerPosition.y - textureHeight)
            sprite.setPosition(position.x, position.y + 3 * textureHeight);
        if (position.y > playerPosition.y + textureHeight)
            sprite.setPosition(position.x, position.y - 3 * textureHeight);
    }
}

void Background::draw(sf::RenderWindow &window)
{
    for (const auto &sprite : sprites)
    {
        if (sprite.getTexture() != nullptr)
        {
            window.draw(sprite);
        }
        else
        {
            std::cout << "Sprite has no texture!" << std::endl;
        }
        // sf::Vector2f position = sprite.getPosition();
        // std::cout << "Sprite Position: (" << position.x << ", " << position.y << ")" << std::endl;
    }
}
