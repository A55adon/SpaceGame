#include "Player.h"
#include <iostream>
#include <cmath>

#pragma region Constructor/Destructor

Player::Player(Data &pData) : pData(pData)
{
    if (!shipTexture.loadFromFile(pData.imagePath))
    {
        std::cerr << "Error loading player texture from " << pData.imagePath << std::endl;
        return;
    }

    shipSprite.setTexture(shipTexture);

    // Set the origin to the center of the sprite for correct rotation
    sf::Vector2u textureSize = shipTexture.getSize();
    shipSprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);

    // Initialize position
    shipSprite.setPosition(pData.position);
}

Player::~Player()
{
    // Destructor logic if needed
}

#pragma endregion

#pragma region Update

void Player::update()
{
    // Convert mouse position from window coordinates to world coordinates
    sf::Vector2i mousePos = sf::Mouse::getPosition(pData.window);
    sf::Vector2f mousePosWorld = pData.window.mapPixelToCoords(mousePos);

    // Determine speed based on whether Shift is pressed
    float speed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 7.0f : 2.0f;

    // Reset velocity
    pData.velocity = sf::Vector2f(0, 0);

    // Update velocity based on input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        pData.velocity.x = -speed; // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        pData.velocity.x = speed; // Move right
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        pData.velocity.y = -speed; // Move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        pData.velocity.y = speed; // Move down
    }

    // Update position based on velocity
    pData.position += pData.velocity;
    shipSprite.setPosition(pData.position);

    // Determine the direction for rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        // When moving fast (Shift pressed), face the direction of movement
        if (pData.velocity != sf::Vector2f(0, 0))
        {
            float angle = std::atan2(pData.velocity.y, pData.velocity.x) * 180 / 3.14159f;
            shipSprite.setRotation(angle + 90);
        }
    }
    else
    {
        // When moving slowly (Shift not pressed), face the mouse
        sf::Vector2f direction = mousePosWorld - pData.position;
        float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;
        shipSprite.setRotation(angle + 90);
    }
}

#pragma endregion

#pragma region Draw

void Player::draw()
{
    pData.window.draw(shipSprite);
}

#pragma endregion

#pragma region Accessors

sf::Vector2f Player::getPosition() const
{
    return shipSprite.getPosition();
}

#pragma endregion
