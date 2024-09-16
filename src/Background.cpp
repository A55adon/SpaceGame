#include "Background.h"
#include <iostream>
#include <cmath>

#pragma region Constructor

Background::Background(std::string path)
{
    if (!bgTexture.loadFromFile(path))
    {
        std::cerr << "Loading background failed" << std::endl;
        return;
    }

    // Initial positions
    x = 0; // Set initial x position
    y = 0; // Set initial y position

    // Initialize sprites
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(x, y);
    bgSprite.setScale(0.5f, 0.5f);

    bgSpriteN.setTexture(bgTexture);
    bgSpriteN.setPosition(x, y + 600);
    bgSpriteN.setScale(0.5f, 0.5f);

    bgSpriteNR.setTexture(bgTexture);
    bgSpriteNR.setPosition(x + 600, y + 600);
    bgSpriteNR.setScale(0.5f, 0.5f);

    bgSpriteR.setTexture(bgTexture);
    bgSpriteR.setPosition(x + 600, y);
    bgSpriteR.setScale(0.5f, 0.5f);

    bgSpriteRS.setTexture(bgTexture);
    bgSpriteRS.setPosition(x + 600, y - 600);
    bgSpriteRS.setScale(0.5f, 0.5f);

    bgSpriteS.setTexture(bgTexture);
    bgSpriteS.setPosition(x, y - 600);
    bgSpriteS.setScale(0.5f, 0.5f);

    bgSpriteSL.setTexture(bgTexture);
    bgSpriteSL.setPosition(x - 600, y - 600);
    bgSpriteSL.setScale(0.5f, 0.5f);

    bgSpriteL.setTexture(bgTexture);
    bgSpriteL.setPosition(x - 600, y);
    bgSpriteL.setScale(0.5f, 0.5f);

    bgSpriteLN.setTexture(bgTexture);
    bgSpriteLN.setPosition(x - 600, y + 600);
    bgSpriteLN.setScale(0.5f, 0.5f);
}

#pragma endregion

#pragma region Update

void Background::update(sf::Vector2f playerPosition)
{
    // Calculate the shift needed to maintain the infinite effect
    float shiftX = std::floor((playerPosition.x - x) / 600) * 600;
    float shiftY = std::floor((playerPosition.y - y) / 600) * 600;

    // Update sprite positions
    bgSprite.setPosition(x + shiftX, y + shiftY);
    bgSpriteN.setPosition(x + shiftX, y + 600 + shiftY);
    bgSpriteNR.setPosition(x + 600 + shiftX, y + 600 + shiftY);
    bgSpriteR.setPosition(x + 600 + shiftX, y + shiftY);
    bgSpriteRS.setPosition(x + 600 + shiftX, y - 600 + shiftY);
    bgSpriteS.setPosition(x + shiftX, y - 600 + shiftY);
    bgSpriteSL.setPosition(x - 600 + shiftX, y - 600 + shiftY);
    bgSpriteL.setPosition(x - 600 + shiftX, y + shiftY);
    bgSpriteLN.setPosition(x - 600 + shiftX, y + 600 + shiftY);
}

void Background::draw(sf::RenderWindow &window)
{
    // Draw all sprites
    window.draw(bgSprite);
    window.draw(bgSpriteN);
    window.draw(bgSpriteNR);
    window.draw(bgSpriteR);
    window.draw(bgSpriteRS);
    window.draw(bgSpriteS);
    window.draw(bgSpriteSL);
    window.draw(bgSpriteL);
    window.draw(bgSpriteLN);
}
#pragma endregion
