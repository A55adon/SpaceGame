#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include "Bullet.h"
#include <memory>

class Enemy
{
public:
    struct Data
    {
        sf::RenderWindow *window;
        std::shared_ptr<sf::Texture> texture;
        sf::Vector2f position;
        sf::Vector2f velocity;
        std::vector<Bullet> bullets;
    };

#pragma region Constructor
    Enemy(Data &bData);
#pragma endregion

#pragma region Methods
    void update(const sf::Vector2f &playerPos);
    void draw() const;
    sf::Vector2f normalize(const sf::Vector2f &vec);
    float length(const sf::Vector2f &vec);
#pragma endregion

#pragma region Variables
    std::shared_ptr<sf::Texture> eTexture;
    sf::Sprite eSprite;
    sf::Vector2f viewDirection;

    Data enemyData;
#pragma endregion
};
