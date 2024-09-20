#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <memory>

class Bullet
{
public:
    struct Data
    {
        sf::RenderWindow *window;
        std::shared_ptr<sf::Texture> texture;
        sf::Vector2f position;
        sf::Vector2f velocity;
        float angle;
    };

#pragma region Constructor
    Bullet(Data &bData);
#pragma endregion

#pragma region Methods
    void update();
    void draw(sf::RenderWindow &window) const;
#pragma endregion

#pragma region Variables
    std::shared_ptr<sf::Texture> bTexture;
    sf::Sprite bSprite;

    Data bulletData;

    std::vector<sf::IntRect> frames;
    int currentFrame;
    float animationSpeed;
    sf::Clock animationClock;
#pragma endregion
};
