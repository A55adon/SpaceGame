#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
public:
    Button(float x, float y, float wf, float hf, std::string path, std::function<void()> callback);

    void draw(sf::RenderWindow &window);
    void handleEvent(const sf::Event &event, const sf::RenderWindow &window);
    void update(const sf::RenderWindow &window);

private:
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    std::function<void()> onClick; // Callback for the button click
};
