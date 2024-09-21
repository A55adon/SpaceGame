#include "Button.h"
#include <iostream>

Button::Button() : originalSize(100.0f, 50.0f) // Default size
{
}

Button::Button(float x, float y, const sf::Texture &texture, std::function<void()> callback)
    : onClick(callback), originalSize(16.0f, 16.0f) // Default size
{
    buttonSprite.setPosition(0, 0);
    // buttonSprite.setPosition(x, y);
    buttonSprite.setTexture(texture); // Set origin for scaling
    buttonSprite.setScale(2, 2);      // Scale to original size
}

void Button::draw(sf::RenderWindow &window)
{
    buttonSprite.setPosition(-200, -200);
    window.draw(buttonSprite);
}

void Button::handleEvent(const sf::Event &event, const sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (buttonSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            {
                isClicked = true;
                onClick(); // Call the callback function
                std::cout << "Clicked" << std::endl;
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        isClicked = false;
    }
}

void Button::update(const sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Print both button and mouse positions
    std::cout << "Button position: (" << buttonSprite.getPosition().x << ", " << buttonSprite.getPosition().y << "), "
              << "Mouse position: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;

    if (buttonSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
    {
        if (!isHovered)
        {
            isHovered = true;
            buttonSprite.setScale(1.1f, 1.1f); // Scale up when hovered
        }
    }
    else
    {
        if (isHovered)
        {
            isHovered = false;
            buttonSprite.setScale(1.0f, 1.0f); // Reset scale when not hovered
        }
    }

    if (isClicked)
    {
        buttonSprite.setScale(0.9f, 0.9f); // Scale down when clicked
    }
    else if (!isHovered)
    {
        buttonSprite.setScale(1.0f, 1.0f); // Reset scale
    }
}

void Button::setPosition(float x, float y)
{
    buttonSprite.setPosition(x, y);
}
