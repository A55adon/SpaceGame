#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class Bullet
{
public:
    struct Data
    {
        sf::Window *window;
        std::string path;
        sf::Vector2f position;
        sf::Vector2f velocity;
    };

#pragma region Constructor
    Bullet(Data &bData);
#pragma endregion

#pragma region Methods
    void update();
    void draw(sf::RenderWindow &window);
#pragma endregion

#pragma region Variables
    sf::Texture bTexture;
    sf::Sprite bSprite;

    Data bulletData;
#pragma endregion
};
