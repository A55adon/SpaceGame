#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "UI.h"
#include "Button.h"

class Game
{
public:
    Game();
    int run();

    // Change the access level of the static members
    static sf::RenderWindow window;
    static Player player;
    static std::vector<Enemy> enemys;
    static sf::Time dt;
    static UI ui;
    static Background stars;
    static Background nebulae;
    static Background dust;
    static Background planets;

private:
    void enemyHandler();
    void enemySpawner();
    void bulletHandler();
};

#endif // GAME_H