#include "Player.h"
#include <iostream>
#include <cmath>

#pragma region Constructor

Player::Player(Data &pData) : pData(pData), currentFrame(0), animationSpeed(0.1f), engineVisible(false)
{
    if (!shipTexture.loadFromFile(pData.imagePath))
    {
        std::cerr << "Error loading player texture from " << pData.imagePath << std::endl;
        return;
    }

    shipSprite.setTexture(shipTexture);

    // Set the origin to the center of the sprite for correct rotation
    sf::Vector2u textureSize = shipTexture.getSize();
    shipSprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);

    // Initialize position
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

    animationClock.restart(); // Start the clock for animation timing

    orbitRadius = frameWidth * 0.05f; // Set the distance of the engine from the player based on engine size
}

Player::~Player()
{
    // Destructor logic if needed
}

#pragma endregion

#pragma region Update

void Player::update()
{
    // Convert mouse position from window coordinates to world coordinates
    sf::Vector2i mousePos = sf::Mouse::getPosition(pData.window);
    sf::Vector2f mousePosWorld = pData.window.mapPixelToCoords(mousePos);

    // Determine speed based on whether Shift is pressed
    float speed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 7.0f : 2.0f;

    // Reset velocity
    pData.velocity = sf::Vector2f(0, 0);

    // Update velocity based on input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        pData.velocity.x = -speed; // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        pData.velocity.x = speed; // Move right
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        pData.velocity.y = -speed; // Move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        pData.velocity.y = speed; // Move down
    }

    // Update position based on velocity
    pData.position += pData.velocity;
    shipSprite.setPosition(pData.position);

    // Determine the direction for rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        // When moving fast (Shift pressed), face the direction of movement
        if (pData.velocity != sf::Vector2f(0, 0))
        {
            float angle = std::atan2(pData.velocity.y, pData.velocity.x) * 180 / 3.14159f;
            shipSprite.setRotation(angle + 90);
        }
    }
    else
    {
        // When moving slowly (Shift not pressed), face the mouse
        sf::Vector2f direction = mousePosWorld - pData.position;
        float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;
        shipSprite.setRotation(angle + 90);
    }

    // Update engine visibility
    engineVisible = pData.velocity != sf::Vector2f(0, 0);

    // Update the engine sprite's position to orbit around the player
    if (engineVisible)
    {
        // Calculate the offset for the engine sprite to orbit around the player
        float angle = (shipSprite.getRotation() - 90) * 3.14159f / 180.0f; // Convert degrees to radians and adjust
        float engineX = shipSprite.getPosition().x - orbitRadius * std::cos(angle);
        float engineY = shipSprite.getPosition().y - orbitRadius * std::sin(angle);
        engineSprite.setPosition(engineX, engineY);
        engineSprite.setRotation(shipSprite.getRotation()); // Match the player's rotation

        // Animation update
        sf::Time dt = animationClock.getElapsedTime();
        if (dt.asSeconds() >= animationSpeed)
        {
            currentFrame = (currentFrame + 1) % frames.size();
            engineSprite.setTextureRect(frames[currentFrame]);
            animationClock.restart(); // Restart the clock after updating frame
        }
    }
}

#pragma endregion

#pragma region Draw

void Player::draw()
{
    pData.window.draw(shipSprite);
    if (engineVisible)
    {
        pData.window.draw(engineSprite); // Draw the animated engine sprite only if visible
    }
}

#pragma endregion

#pragma region Accessors

sf::Vector2f Player::getPosition() const
{
    return shipSprite.getPosition();
}

#pragma endregion
