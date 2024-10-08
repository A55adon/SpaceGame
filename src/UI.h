#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include "Button.h"

class UI
{
public:
    UI(sf::RenderWindow &window);
    void update(const sf::RenderWindow &window, const sf::Event &event);
    bool getUItrue();
    void draw(sf::RenderWindow &window);

private:
    bool UItrue = false;
    bool escapeKeyReleased = true;
    Button *exitButton;
    Button *continueButton;
    sf::Sprite uiBackgroundSprite;
    sf::Texture uiBackgroundTexture;
};

#endif // UI_H