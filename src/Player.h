#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
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
    void draw() const;
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
    std::shared_ptr<sf::Texture> bulletTexture; // Use shared_ptr
    bool lastShotLeft = true;                   // Track the last shot direction
    float borbitRadius = 50.0f;                 // Distance from the player where bullets will spawn
    int shootCounter = 0;
    int shootable = 0;

public:
    std::vector<Bullet>
        bullets;
    Data pData;

    Bullet::Data bData;

    Bullet bull;

#pragma endregion
};

#endif // PLAYER_H
