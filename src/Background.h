#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Background
{
public:
#pragma region Constructor
    Background(std::string path);
#pragma endregion

#pragma region Methods
    void update(sf::Vector2f playerPosition);
    void draw(sf::RenderWindow &window);
#pragma endregion

private:
#pragma region Variables
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    sf::Sprite bgSpriteN;
    sf::Sprite bgSpriteNR;
    sf::Sprite bgSpriteR;
    sf::Sprite bgSpriteRS;
    sf::Sprite bgSpriteS;
    sf::Sprite bgSpriteSL;
    sf::Sprite bgSpriteL;
    sf::Sprite bgSpriteLN;
    int x = 0, y = 0;
#pragma endregion
};
