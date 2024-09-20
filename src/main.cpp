#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include <iostream>
#include <memory>
#include <cmath>

sf::RenderWindow window(sf::VideoMode(1200, 1000), "Space Game");
Player::Data playerData = {"res/Ships/PNGs/ship.png", "res/Engine Effects/PNGs/Nairan - Battlecruiser - Engine.png", {400, 300}, {0, 0}, window};
Player player(playerData);
std::vector<Enemy> enemys;

void enemyHandler()
{
    if (enemys.size() < 8)
    {
    }
    for (size_t i = 0; i < enemys.size();)
    {
        Enemy &enemy = enemys[i];
        bool enemyRemoved = false;

        for (size_t j = 0; j < player.bullets.size();)
        {
            Bullet &bullet = player.bullets[j];
            sf::FloatRect enemyBounds = enemy.eSprite.getGlobalBounds();
            sf::FloatRect bulletBounds = bullet.bSprite.getGlobalBounds();

            if (enemyBounds.intersects(bulletBounds))
            {
                std::cout << "Bullet position: " << bullet.bSprite.getPosition().x << ", " << bullet.bSprite.getPosition().y << std::endl;
                std::cout << "Enemy position: " << enemy.eSprite.getPosition().x << ", " << enemy.eSprite.getPosition().y << std::endl;

                player.bullets.erase(player.bullets.begin() + j);
                enemyRemoved = true;
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
            enemys.erase(enemys.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

void enemySpawner()
{
    if (enemys.size() < 80)
    {
        sf::Vector2f playerPosition = player.getPosition();
        float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f;
        float distance = 800.0f + static_cast<float>(rand()) / RAND_MAX * 700.0f;
        sf::Vector2f spawnPosition = playerPosition + sf::Vector2f(std::cos(angle) * distance, std::sin(angle) * distance);

        std::shared_ptr<sf::Texture> enemyTexture = std::make_shared<sf::Texture>();
        if (!enemyTexture->loadFromFile("res/Ships/PNGs/enemy2.png"))
        {
            std::cerr << "Failed to load enemy texture!" << std::endl;
            return;
        }
        Enemy::Data enemyData = {&window, enemyTexture, spawnPosition, {static_cast<float>(rand() % 10) - 5, static_cast<float>(rand() % 10) - 5}, {}};

        enemys.push_back(Enemy(enemyData));
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
                bulletY < playerY - 1000); });

    if (it != player.bullets.end())
    {
        player.bullets.erase(it, player.bullets.end());
    }

    if (player.bullets.size() > 200)
    {
        player.bullets.erase(player.bullets.begin(), player.bullets.begin() + (player.bullets.size() - 200));
    }
}

int main()
{
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::Time accumulator = sf::Time::Zero;

    Background background("res/Background/Space Background(11).png");
    sf::View view(window.getDefaultView());
    view.setCenter(player.getPosition());

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        accumulator += dt;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        while (accumulator >= timePerFrame)
        {
            player.update();
            background.update(player.getPosition());
            accumulator -= timePerFrame;

            for (auto &enemy : enemys)
            {
                enemy.update(player.pData.position);
            }
            enemySpawner();
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

        window.clear(sf::Color::Black);
        background.draw(window);
        player.draw();
        for (auto &enemy : enemys)
        {
            enemy.draw();
        }
        window.display();
    }
    return 0;
}
