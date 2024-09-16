#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>

class Player
{
public:
#pragma region Data Structure
    struct Data
    {
        std::string imagePath;
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::RenderWindow &window;
    };
#pragma endregion

#pragma region Constructor/Destructor
    Player(Data &pData);
    ~Player();
#pragma endregion

#pragma region Methods
    sf::Vector2f getPosition() const;
    void update();
    void draw();
#pragma endregion

private:
#pragma region Variables
    sf::Texture shipTexture;
    sf::Sprite shipSprite;
    Data pData;
#pragma endregion
};

#endif // PLAYER_H
