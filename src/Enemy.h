#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include "Bullet.h"

class Enemy
{
public:
    struct Data
    {
        sf::RenderWindow *window;
        std::string path;
        sf::Vector2f position;
        sf::Vector2f velocity;
        std::vector<Bullet> bullets;
    };
#pragma region Constructor
    Enemy(Data &bData);
#pragma endregion

#pragma region Methods
    void update();
    void draw() const;
#pragma endregion

#pragma region Variables
    sf::Texture eTexture;
    sf::Sprite eSprite;

    Data enemyData;
#pragma endregion
};
