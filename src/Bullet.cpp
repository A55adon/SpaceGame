#include "Bullet.h"
#include <iostream>

#pragma region Constructor

Bullet::Bullet(Data &bData) : bulletData(bData), bTexture(bData.texture), currentFrame(0), animationSpeed(0.1f) // Initialize shared_ptr
{
    if (!bTexture)
    {
        std::cerr << "Texture pointer is null!" << std::endl;
        return;
    }

    bSprite.setTexture(*bTexture);

    int frameWidth = 9;
    int frameHeight = 9;
    int numFrames = 5;
    for (int i = 0; i < numFrames; ++i)
    {
        frames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
    }

    bSprite.setTextureRect(frames[currentFrame]);
    bSprite.setOrigin(frameWidth / 2.0f, frameHeight / 2.0f);
    bSprite.setScale(4, 4);
    animationClock.restart();
}

#pragma endregion

#pragma region Methods

void Bullet::draw(sf::RenderWindow &win) const
{
    win.draw(bSprite);
}

void Bullet::update()
{
    bulletData.position += bulletData.velocity;
    bSprite.setPosition(bulletData.position);
    bSprite.setRotation(bulletData.angle * 180.0f / 3.14159f + 90);

    sf::Time dt = animationClock.getElapsedTime();
    if (!frames.empty())
    {
        if (dt.asSeconds() >= animationSpeed)
        {
            currentFrame = (currentFrame + 1) % frames.size();
            bSprite.setTextureRect(frames[currentFrame]);
            animationClock.restart();
        }
    }
}

#pragma endregion
