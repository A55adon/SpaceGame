#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class UI
{
public:
    UI(sf::RenderWindow &window); // Updated constructor
    void update(const sf::RenderWindow &window, const sf::Event &event);
    bool getUItrue();
    void draw(sf::RenderWindow &window);
    void setButtonPosition(float x, float y);

    bool UItrue;
    bool escapeKeyReleased;
    sf::Texture buttonTexture;
    Button myButton;
};