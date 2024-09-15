#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>

class Player
{
public:
    struct Data
    {
        std::string imagePath;
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::RenderWindow &window;
    };

    Player(Data pData);
    ~Player();

    void update();
    void draw();

private:
    sf::Texture shipTexture;
    sf::Sprite shipSprite;
    Data pData;
};

#endif // PLAYER_H
