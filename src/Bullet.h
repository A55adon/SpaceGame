#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class Bullet
{
public:
    struct Data
    {
        sf::RenderWindow *window;
        std::string path;
        sf::Vector2f position;
        sf::Vector2f velocity;
    };

#pragma region Constructor
    Bullet(Data &bData);
#pragma endregion

#pragma region Methods
    void update();
    void draw();
#pragma endregion

#pragma region Variables
    sf::Texture bTexture;
    sf::Sprite bSprite;

    Data bulletData;
#pragma endregion
};
