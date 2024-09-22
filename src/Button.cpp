#include "Button.h"
#include <iostream>

Button::Button(float x, float y, float wf, float hf, std::string path, std::function<void()> callback)
    : onClick(callback)
{
    if (!buttonTexture.loadFromFile(path))
    {
        std::cerr << "Error loading tilesheet from " << path << std::endl;
    }
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setPosition(0, 0);
    buttonSprite.setScale(wf, hf);
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(buttonSprite);
}

void Button::handleEvent(const sf::Event &event, const sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::FloatRect bounds = buttonSprite.getGlobalBounds();

            if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            {
                if (onClick)
                {
                    onClick();
                }
            }
        }
    }
}

void Button::update(const sf::RenderWindow &window)
{
}
