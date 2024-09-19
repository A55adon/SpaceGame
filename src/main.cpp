#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include <iostream>
#include <memory> // For std::make_shared

#pragma region Variables

sf::RenderWindow window(sf::VideoMode(800, 600), "Space Game");
Player::Data playerData = {"res/Ships/PNGs/ship.png", "res/Engine Effects/PNGs/Nairan - Battlecruiser - Engine.png", {400, 300}, {0, 0}, window};
Player player(playerData);
std::vector<Enemy> enemys;
Enemy::Data enemyData = {&window, "res/Ships/PNGs/enemy.png", {10, 10}, {10, 10}, {}};
Enemy enemy(enemyData);

#pragma endregion

#pragma region Bullet/Enemy logic

void enemyHandler()
{
    if (enemys.size() < 8)
    {
        // TODO: add enemy spawn logic
    }
    for (size_t i = 0; i < enemys.size();)
    {
        Enemy &enemy = enemys[i];
        bool enemyRemoved = false;

        for (size_t j = 0; j < player.bullets.size();)
        {
            Bullet &bullet = player.bullets[j];

            // Assuming you have methods or members to get sprite bounds
            sf::FloatRect enemyBounds = enemy.eSprite.getGlobalBounds();
            sf::FloatRect bulletBounds = bullet.bSprite.getGlobalBounds();

            // Check for intersection
            if (enemyBounds.intersects(bulletBounds))
            {
                // Debugging output
                std::cout << "Bullet position: " << bullet.bSprite.getPosition().x << ", " << bullet.bSprite.getPosition().y << std::endl;
                std::cout << "Enemy position: " << enemy.eSprite.getPosition().x << ", " << enemy.eSprite.getPosition().y << std::endl;

                // Remove the bullet
                player.bullets.erase(player.bullets.begin() + j);

                // Set flag for enemy removal
                enemyRemoved = true;

                // Break out of the bullet loop
                break;
            }
            else
            {
                ++j;
            }
        }

        if (enemyRemoved)
        {
            std::cout << "Removing enemy at index: " << i << std::endl;
            // Remove the enemy if it was marked for removal
            enemys.erase(enemys.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

void bulletHandler()
{
    auto it = std::remove_if(player.bullets.begin(), player.bullets.end(), [&](const Bullet &bullet)
                             {
        float bulletX = bullet.bSprite.getPosition().x;
        float bulletY = bullet.bSprite.getPosition().y;

        float playerX = player.pData.position.x;
        float playerY = player.pData.position.y;

        return (bulletX > playerX + 1000 ||
                bulletX < playerX - 1000 ||
                bulletY > playerY + 1000 ||
                bulletY < playerY - 1000 ||
                player.bullets.size() > 200); });

    if (it != player.bullets.end())
    {
        player.bullets.erase(it, player.bullets.end());
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
    enemys.push_back(enemy);

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
            for (auto &enemy : enemys)
            {
                enemy.update(player.pData.position);
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
        enemyHandler();
        window.setView(view);
#pragma endregion

#pragma region Rendering
        window.clear(sf::Color::Black);
        background.draw(window);
        player.draw();
        if (enemys.empty())
        {
            std::cout << "No enemies to render." << std::endl;
        }
        for (auto &enemy : enemys)
        {
            enemy.update(player.pData.position);
        }
        std::cout << enemys[1].enemyData.position.x << " and " << enemys[1].enemyData.position.y << std::endl;
        window.display();
#pragma endregion
    }

    return 0;
}
