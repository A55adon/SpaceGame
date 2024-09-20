#include "Enemy.h"
#include <iostream>
#include <cmath>

Enemy::Enemy(Data &enemyData)
    : enemyData(enemyData), eTexture(enemyData.texture)
{
    if (!eTexture)
    {
        std::cerr << "Error: Enemy texture pointer is null!" << std::endl;
        return;
    }
    eSprite.setTexture(*eTexture);
    eSprite.setOrigin(eTexture->getSize().x / 2.0f, eTexture->getSize().y / 2.0f);
}

void Enemy::update(const sf::Vector2f &playerPosition)
{
    sf::Vector2f directionToPlayer = playerPosition - enemyData.position;

    float epsilon = 0.00001f;
    if (length(directionToPlayer) > epsilon)
    {
        directionToPlayer = normalize(directionToPlayer);
    }
    else
    {
        directionToPlayer = {1.f, 0.f};
    }

    float speed = 1.1f;

    enemyData.position += directionToPlayer * speed;

    eSprite.setPosition(enemyData.position);

    float angleRad = std::atan2(directionToPlayer.y, directionToPlayer.x);
    float angleDeg = angleRad * 180.f / 3.14159f;
    eSprite.setRotation(angleDeg + 90.f);
}

void Enemy::draw() const
{
    enemyData.window->draw(eSprite);
}

sf::Vector2f Enemy::normalize(const sf::Vector2f &vec)
{
    float len = length(vec);
    if (len > 0.00001f)
    {
        return vec / len;
    }
    return sf::Vector2f(1.f, 0.f);
}

float Enemy::length(const sf::Vector2f &vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}
