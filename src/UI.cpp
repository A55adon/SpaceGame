#include "UI.h"
#include "Button.h"
#include <iostream>

UI::UI(sf::RenderWindow &window)
{
    exitButton = new Button(0.0f, 0.0f, 1.0f, 1.0f, "res/Buttons/exit.png",
                            []()
                            {
                                delete main;
                            });

    continueButton = new Button(40.0f, 40.0f, 2.0f, 2.0f, "res/Buttons/continue.png",
                                []()
                                {
                                    UItrue = false;
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
        exitButton->handleEvent(event, window);
        continueButton->handleEvent(event, window);
    }
}

void UI::draw(sf::RenderWindow &window)
{
    if (UItrue)
    {
        exitButton->draw(window);
        continueButton->draw(window);
    }
}

bool UI::getUItrue()
{
    return UItrue;
}
