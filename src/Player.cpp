#include "Player.h"
#include <iostream>

Player::Player(Data pData) : pData(pData)
{
    if (!shipTexture.loadFromFile(pData.imagePath))
    {
        std::cerr << "Error loading player texture from " << pData.imagePath << std::endl;
        return;
    }

    shipSprite.setTexture(shipTexture);
    shipSprite.setPosition(pData.position);
}

Player::~Player()
{
    // TODO: Destructor implementation if needed
}

void Player::update()
{
    pData.position += pData.velocity;
    shipSprite.setPosition(pData.position);
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(shipSprite);
}
