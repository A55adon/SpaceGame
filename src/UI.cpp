#include "UI.h"
#include <iostream>

UI::UI() : myButton(200.0f, 150.0f, 16.0f, 16.0f, buttonTexture, []()
                    { std::cout << "Button clicked!" << std::endl; })
{
    if (!buttonTexture.loadFromFile("res/Buttons/info_button.png"))
    {
        std::cout << "Failed to load button texture!" << std::endl;
    }
    else
    {
        std::cout << "Button texture loaded successfully." << std::endl;
    }
}

void UI::update(const sf::RenderWindow &window, const sf::Event &event)
{
    myButton.update(window);
    myButton.handleEvent(event, window);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escapeKeyReleased)
    {
        UItrue = !UItrue;
        escapeKeyReleased = false;
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        escapeKeyReleased = true;
    }
}

bool UI::getUItrue()
{
    return UItrue;
}

void UI::draw(sf::RenderWindow &window)
{
    myButton.draw(window);
}
