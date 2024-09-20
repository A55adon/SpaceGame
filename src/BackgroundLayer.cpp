#include <SFML/Graphics.hpp>
#include <vector>
#include "BackgroundLayer.h"

//////Constructors //////

BackgroundLayer::BackgroundLayer(const Background::Data &bgData, int parallaxFactor, int screenWidth, int screenHeight)
    : parallaxFactor(parallaxFactor), screenWidth(screenWidth), screenHeight(screenHeight)
{
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            Background::Data newBgData = bgData;
            newBgData.x = i * bgData.w;
            newBgData.y = j * bgData.h;

            backgrounds.emplace_back(newBgData, parallaxFactor);
        }
    }
}

//////Methods//////

void BackgroundLayer::update(sf::Vector2f playerPosition)
{
    for (auto &background : backgrounds)
    {
        background.update(playerPosition);
    }
    repositionBackgrounds(playerPosition);
}

void BackgroundLayer::repositionBackgrounds(sf::Vector2f playerPosition)
{
    for (auto &background : backgrounds)
    {
        sf::Vector2f bgPosition = background.getPosition();
        float newX = bgPosition.x;
        float newY = bgPosition.y;

        if (playerPosition.x - bgPosition.x > screenWidth)
        {
            newX += 3 * background.bgData.w;
        }
        else if (playerPosition.x - bgPosition.x < -screenWidth)
        {
            newX -= 3 * background.bgData.w;
        }

        if (playerPosition.y - bgPosition.y > screenHeight)
        {
            newY += 3 * background.bgData.h;
        }
        else if (playerPosition.y - bgPosition.y < -screenHeight)
        {
            newY -= 3 * background.bgData.h;
        }

        background.setPosition(newX, newY);
    }
}

void BackgroundLayer::draw(sf::RenderWindow &window)
{
    for (auto &background : backgrounds)
    {
        background.draw(window);
    }
}
