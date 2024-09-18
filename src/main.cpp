#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Background.h"

#pragma region Variables

sf::RenderWindow window(sf::VideoMode(800, 600), "Space Game");
Player::Data playerData = {"res/Ships/PNGs/ship.png", "res/Engine Effects/PNGs/Nairan - Battlecruiser - Engine.png", {400, 300}, {0, 0}, window};
Player player(playerData);

#pragma regionend

#pragma region Bulletlogic

void bulletHandler()
{
    for (int i = 0; i < player.bullets.size();)
    {
        float bulletX = player.bullets[i].bulletData.position.x;
        float bulletY = player.bullets[i].bulletData.position.y;

        float playerX = player.pData.position.x;
        float playerY = player.pData.position.y;

        if (bulletX > playerX + 1000 ||
            bulletX < playerX - 1000 ||
            bulletY > playerY + 1000 ||
            bulletY < playerY - 1000 ||
            player.bullets.size() > 200)
        {
            player.bullets.erase(player.bullets.begin() + i);
            printf("Bullet got removed \n");
        }
        else
        {
            i++;
        }
    }
}
#pragma endregion

int main()
{
#pragma region Initialization
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::Time accumulator = sf::Time::Zero;

    Background background("res/Background/Space Background(11).png");

    sf::View view(window.getDefaultView());
    view.setCenter(player.getPosition());
#pragma endregion

    while (window.isOpen())
    {
#pragma region EventHandling
        sf::Time dt = clock.restart();
        accumulator += dt;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
#pragma endregion

#pragma region Update
        while (accumulator >= timePerFrame)
        {
            player.update();
            background.update(player.getPosition());
            accumulator -= timePerFrame;
            for (auto &bullet : player.bullets)
            {
                bullet.update();
            }
        }

        sf::Vector2f playerPosition = player.getPosition();
        sf::Vector2f viewCenter = view.getCenter();

        sf::FloatRect deadZone(viewCenter.x - 100.f, viewCenter.y - 100.f, 200.f, 200.f);
        if (!deadZone.contains(playerPosition))
        {
            float followSpeed = 0.05f;
            viewCenter += (playerPosition - viewCenter) * followSpeed;
            view.setCenter(viewCenter);
        }

        bulletHandler();
        window.setView(view);
#pragma endregion

#pragma region Rendering
        window.clear(sf::Color::Black);
        background.draw(window);
        player.draw();
        for (auto &bullet : player.bullets)
        {
            bullet.draw();
        }
        window.display();
#pragma endregion
    }

    return 0;
}

//  TODO: camera endpositon --> following
// TODO: fix movementlagg
// TODO: unstatic movements
// TODO: normalize fast-movement vectors
// TODO: remove bullet deleation lag