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
    float e = 0.001f;

    // If the direction to player is too small, set a default direction
    if (length(directionToPlayer) <= e)
    {
        directionToPlayer = {1.f, 0.f}; // Default direction
    }
    else
    {
        // Normalize the direction to the player
        directionToPlayer = normalize(directionToPlayer);

        // Ensure viewDirection is initialized; if not, set a default
        if (length(viewDirection) <= e)
        {
            viewDirection = {1.f, 0.f}; // Default view direction
        }

        // Calculate a new direction using the direction to the player
        sf::Vector2f newDirection = directionToPlayer;

        // Normalize the new direction
        newDirection = normalize(newDirection);

        // Set a fixed speed for the enemy movement (e.g., 100.0f)
        float speed = 100.0f; // You can adjust this value

        // Update the enemy's position based on the normalized direction and speed
        enemyData.position += newDirection * speed * 0.016f; // Multiply by delta time (~16 ms for 60fps)

        // Update the sprite position to match the enemy's new position
        eSprite.setPosition(enemyData.position);
    }
}

void Enemy::draw() const
{
    enemyData.window->draw(eSprite);
}

sf::Vector2f Enemy::normalize(const sf::Vector2f &vec)
{

    float len = length(vec);
    if (len != 0)
    {
        return vec / len;
    }
    return {1.f, 0.f}; // Fallback if vector length is zero
}
float Enemy::length(const sf::Vector2f &vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}
