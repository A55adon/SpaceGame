#include "Button.h"
#include <iostream> // For debug output

Button::Button(float x, float y, float width, float height, const sf::Texture &texture, std::function<void()> callback)
    : onClick(callback), originalSize(width, height)
{
    buttonShape.setSize(originalSize);
    buttonShape.setPosition(x, y);
    buttonShape.setTexture(&texture);
    std::cout << "Button initialized at position (" << x << ", " << y << ") with size (" << width << ", " << height << ")" << std::endl; // Debug info
}

void Button::draw(sf::RenderWindow &window)
{
    std::cout << "Drawing button at position: " << buttonShape.getPosition().x << ", " << buttonShape.getPosition().y << std::endl;
    window.draw(buttonShape);
}

void Button::handleEvent(const sf::Event &event, const sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::cout << "Mouse clicked at: " << mousePos.x << ", " << mousePos.y << std::endl;

            if (buttonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            {
                isClicked = true;
                std::cout << "Button clicked!" << std::endl;
                onClick();
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

    if (buttonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
    {
        if (!isHovered)
        {
            isHovered = true;
            buttonShape.setSize(originalSize * 1.1f);
        }
    }
    else
    {
        if (isHovered)
        {
            isHovered = false;
            buttonShape.setSize(originalSize);
        }
    }

    if (isClicked)
    {
        buttonShape.setSize(originalSize * 0.9f);
    }
    else if (!isHovered)
    {
        buttonShape.setSize(originalSize);
    }
}
