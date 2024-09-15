#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(Data pData) : pData(pData)
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
    // TODO: Deconstructor if needed
}

void Player::update()
{
    pData.velocity = sf::Vector2f(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        pData.velocity.x = -5.0f; // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        pData.velocity.x = 5.0f; // Move right
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        pData.velocity.y = -5.0f; // Move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        pData.velocity.y = 5.0f; // Move down
    }
    pData.position += pData.velocity;

    shipSprite.setPosition(pData.position);

    sf::Vector2i mousePos = sf::Mouse::getPosition(pData.window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    sf::Vector2f direction = mousePosF - pData.position;
    float angle = std::atan2(direction.y, direction.x);
    shipSprite.setRotation((angle * 180 / 3.14159f) + 90);
}

void Player::draw()
{
    pData.window.draw(shipSprite);
}
