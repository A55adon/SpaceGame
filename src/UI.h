#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Button.h"

class UI
{
public:
    UI();
    void update(const sf::RenderWindow &window, const sf::Event &event);
    bool getUItrue();
    void draw(sf::RenderWindow &window);

private:
    bool UItrue = false;
    bool escapeKeyReleased = true;
    sf::Texture buttonTexture;
    Button myButton;
};
