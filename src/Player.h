#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Bullet.h"

class Player
{
public:
#pragma region Data Structure
    struct Data
    {
        std::string imagePath;
        std::string engineGif;
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::RenderWindow &window;
    };
#pragma endregion

#pragma region Constructor
    Player(Data &data);
    ~Player();
#pragma endregion

#pragma region Methods
    sf::Vector2f getPosition() const;
    void update();
    void draw();
    void shoot();
#pragma endregion

private:
#pragma region Variables
    sf::Texture shipTexture;
    sf::Sprite shipSprite;
    sf::Texture engineTexture;
    sf::Sprite engineSprite;
    std::vector<sf::IntRect> frames;
    int currentFrame;
    float animationSpeed;
    sf::Clock animationClock;
    sf::Vector2f engineOffset;
    float orbitRadius;
    bool engineVisible;
    Bullet::Data bulletData;
    bool shootable = true;
    int bulletcounter = 0;

public:
    std::vector<Bullet> bullets;
    Data pData;
#pragma endregion
};

#endif // PLAYER_H