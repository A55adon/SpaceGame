#include "UI.h"
#include "Button.h"
#include <iostream>

UI::UI(sf::RenderWindow &window)
{
    testButton = new Button(0.0f, 0.0f, 1.0f, 1.0f, "res/Ships/PNGs/ship.png",
                            []()
                            {
                                std::cout << "Button clicked!" << std::endl;
                            });
}

void UI::update(const sf::RenderWindow &window, const sf::Event &event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escapeKeyReleased)
    {
        UItrue = !UItrue;
        escapeKeyReleased = false;
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        escapeKeyReleased = true;
    }

    if (UItrue)
    {
        testButton->handleEvent(event, window);
    }
}

void UI::draw(sf::RenderWindow &window)
{
    if (UItrue)
    {
        testButton->draw(window);
    }
}

bool UI::getUItrue()
{
    return UItrue;
}
