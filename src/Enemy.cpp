#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include "Bullet.h"
#include "Enemy.h"
#include <cmath>

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

void Enemy::update(const sf::Vector2f &playerPosition)
{
    // Calculate the direction to the player
    sf::Vector2f directionToPlayer = playerPosition - enemyData.position;

    // Small epsilon value for floating-point comparison
    float epsilon = 0.00001f;

    // Normalize the direction if its length is greater than epsilon
    if (length(directionToPlayer) > epsilon)
    {
        directionToPlayer = normalize(directionToPlayer);
    }
    else
    {
        directionToPlayer = {1.f, 0.f}; // Default direction if player is at the same position
    }

    // Set a reasonable speed for the enemy movement
    float speed = 0.1f; // Adjust this value as needed

    // Update the enemy's position based on the direction and speed
    enemyData.position += directionToPlayer * speed;

    // Update the sprite position to match the enemy's new position
    eSprite.setPosition(enemyData.position);
}

void Enemy::draw() const
{
    enemyData.window->draw(eSprite);
}

sf::Vector2f Enemy::normalize(const sf::Vector2f &vec)
{
    float len = length(vec);
    if (len > 0.00001f) // Ensure the length is not too small to avoid division by zero
    {
        return vec / len;
    }
    return sf::Vector2f(1.f, 0.f); // Default direction if vector length is zero or too small
}
float Enemy::length(const sf::Vector2f &vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}
