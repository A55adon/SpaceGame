#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include "Bullet.h"
#include "Enemy.h"

Enemy::Enemy(Data &enemyData)
    : enemyData(enemyData) // Just copy the data
{
    // Load texture and handle errors
    if (!eTexture.loadFromFile(enemyData.path))
    {
        std::cerr << "Error loading enemy texture from " << enemyData.path << std::endl;
    }
    eSprite.setTexture(eTexture);
    eSprite.setOrigin(eTexture.getSize().x / 2.0f, eTexture.getSize().y / 2.0f);
}

void Enemy::update() {}

void Enemy::draw() const
{
    enemyData.window->draw(eSprite);
}
