#include "Player.h"
#include <iostream>
#include <cmath>
#include "Bullet.h"

#pragma region Constructor

Player::Player(Data &pData)
    : pData(pData), currentFrame(0), animationSpeed(0.1f), engineVisible(false),
      bulletData({&pData.window, "", pData.position, pData.velocity}) // Pass the pointer
{
    if (!shipTexture.loadFromFile(pData.imagePath))
    {
        std::cerr << "Error loading player texture from " << pData.imagePath << std::endl;
        return;
    }

    shipSprite.setTexture(shipTexture);

    sf::Vector2u textureSize = shipTexture.getSize();
    shipSprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);

    shipSprite.setPosition(pData.position);

    if (!engineTexture.loadFromFile("res/Engine Effects/PNGs/mainship_tilesheet.png"))
    {
        std::cerr << "Error loading tilesheet from mainship_tilesheet.png" << std::endl;
    }

    int frameWidth = 128;
    int frameHeight = 128;
    int numFrames = 8;

    for (int i = 0; i < numFrames; ++i)
    {
        frames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
    }

    engineSprite.setTexture(engineTexture);
    engineSprite.setTextureRect(frames[currentFrame]);
    engineSprite.setOrigin(frameWidth / 2.0f, frameHeight / 2.0f);

    animationClock.restart();

    orbitRadius = frameWidth * 0.05f;

    bulletData.path = "res/Ships/PNGs/ship.png";
    bulletData.velocity = sf::Vector2f(0.5f, 0.0f);
}

Player::~Player()
{
    // TODO: Player destructor
}

#pragma endregion

#pragma region Update

void Player::update()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(pData.window);
    sf::Vector2f mousePosWorld = pData.window.mapPixelToCoords(mousePos);

    float speed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 7.0f : 2.0f;

    pData.velocity = sf::Vector2f(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        shoot();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        pData.velocity.x = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        pData.velocity.x = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        pData.velocity.y = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        pData.velocity.y = speed;
    }
    pData.position += pData.velocity;
    shipSprite.setPosition(pData.position);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if (pData.velocity != sf::Vector2f(0, 0))
        {
            float angle = std::atan2(pData.velocity.y, pData.velocity.x) * 180 / 3.14159f;
            shipSprite.setRotation(angle + 90);
        }
    }
    else
    {
        sf::Vector2f direction = mousePosWorld - pData.position;
        float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;
        shipSprite.setRotation(angle + 90);
    }

    engineVisible = pData.velocity != sf::Vector2f(0, 0);

    if (engineVisible)
    {
        float angle = (shipSprite.getRotation() - 90) * 3.14159f / 180.0f;
        float engineX = shipSprite.getPosition().x - orbitRadius * std::cos(angle);
        float engineY = shipSprite.getPosition().y - orbitRadius * std::sin(angle);
        engineSprite.setPosition(engineX, engineY);
        engineSprite.setRotation(shipSprite.getRotation());

        sf::Time dt = animationClock.getElapsedTime();
        if (dt.asSeconds() >= animationSpeed)
        {
            currentFrame = (currentFrame + 1) % frames.size();
            engineSprite.setTextureRect(frames[currentFrame]);
            animationClock.restart();
        }
    }

    if (!shootable && bulletcounter > 4)
    {
        shootable = true;
        bulletcounter = 0;
    }
    else
    {
        bulletcounter++;
    }
}

void Player::shoot()
{
    if (shootable)
    {
        bulletData.position = pData.position;
        Bullet bullet(bulletData);
        bullets.push_back(bullet);
        shootable = false;
    }
}

#pragma endregion

#pragma region Draw

void Player::draw() const
{
    pData.window.draw(shipSprite);
    if (engineVisible)
    {
        pData.window.draw(engineSprite);
    }
}

#pragma endregion

#pragma region Accessors

sf::Vector2f Player::getPosition() const
{
    return shipSprite.getPosition();
}

#pragma endregion
