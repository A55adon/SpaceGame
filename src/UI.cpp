#include "UI.h"
#include "Button.h"
#include <iostream>

UI::UI(sf::RenderWindow &window)
{
    exitButton = new Button(10.0f, 10.0f, 2.0f, 2.0f, "res/Buttons/exit.png",
                            [&]() // Capture `this` by reference
                            {
                                window.close();
                            });

    continueButton = new Button(200.0f, 30.0f, 4.0f, 4.0f, "res/Buttons/continue.png",
                                [&]() // Capture `this` by reference
                                {
                                    UItrue = false;
                                });

    std::cout << exitButton->buttonSprite.getPosition().x << " + "
              << exitButton->buttonSprite.getPosition().y << std::endl;
    std::cout << continueButton->buttonSprite.getPosition().x << " + "
              << continueButton->buttonSprite.getPosition().y << std::endl;
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
