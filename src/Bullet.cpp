#include "Bullet.h"
#include <iostream>

#pragma region Constructor

Bullet::Bullet(Data &bData) : bulletData(bData)
{
    if (!bTexture.loadFromFile(bData.path))
    {
        std::cerr << "Error loading bullet texture from " << bData.path << std::endl;
        return;
    }

    bSprite.setTexture(bTexture);

    bSprite.setPosition(bulletData.position);
    if (!bSprite.getTexture())
    {
        std::cerr << "Bullet sprite does not have a texture applied." << std::endl;
    }
    bSprite.setScale(0.5, 0.5);
}

#pragma endregion

#pragma region Methods

void Bullet::update()
{
    bulletData.position += bulletData.velocity;

    bSprite.setPosition(bulletData.position);
}

void Bullet::draw(sf::RenderWindow &window)
{
    window.draw(bSprite);

    if (!bSprite.getTexture())
    {
        printf("test");
    }
}

#pragma endregion
