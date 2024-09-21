#include "UI.h"
#include "Button.h"
#include <iostream>

UI::UI(sf::RenderWindow &window) : escapeKeyReleased(true), UItrue(false)
{
    if (!buttonTexture.loadFromFile("res/Ships/PNGs/enemy2.png"))
    {
        std::cout << "Failed to load button texture!" << std::endl;
    }
    else
    {
        myButton = Button(0, 0, buttonTexture, []()
                          { std::cout << "Button clicked!" << std::endl; });
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
