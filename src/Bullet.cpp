#include "Bullet.h"
#include <iostream>

#pragma region Constructor

Bullet::Bullet(Data &bData) : bulletData(bData), bTexture(bData.texture) // Initialize shared_ptr
{
    if (!bTexture)
    {
        std::cerr << "Texture pointer is null!" << std::endl;
        return;
    }

    bSprite.setTexture(*bTexture);

    bSprite.setPosition(bulletData.position);
    if (!bSprite.getTexture())
    {
        std::cerr << "Bullet sprite does not have a texture applied." << std::endl;
    }
    bSprite.setScale(0.5, 0.5);
}

#pragma endregion

#pragma region Methods

void Bullet::draw(sf::RenderWindow &win) const
{
    win.draw(bSprite);
}

void Bullet::update()
{
    bulletData.position += bulletData.velocity; // Move the bullet in the direction of its velocity

    bSprite.setPosition(bulletData.position);
    bSprite.setRotation(bulletData.angle * 180.0f / 3.14159f + 90); // Set rotation in degrees
}

#pragma endregion
