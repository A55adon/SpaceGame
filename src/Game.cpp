#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include <iostream>
#include <memory>
#include <cmath>
#include "UI.h"
#include "Button.h"
#include "Game.h"

// Define the static members here

sf::RenderWindow Game::window(sf::VideoMode(1200, 1000), "Space Game", sf::Style::Fullscreen);
Player::Data playerData = {"res/Ships/PNGs/ship.png", "res/Engine Effects/PNGs/Nairan - Battlecruiser - Engine.png", {400, 300}, {0, 0}, Game::window};
Player Game::player(playerData);

std::vector<Enemy> Game::enemys; // Correctly define the static member
sf::Time Game::dt;               // Correctly define the static member

UI Game::ui(Game::window);

Background Game::stars(Game::window, "res/Background/stars.png");
Background Game::nebulae(Game::window, "res/Background/nebulae.png");
Background Game::dust(Game::window, "res/Background/dust.png");
Background Game::planets(Game::window, "res/Background/planets.png");

Game::Game() {}

void Game::enemyHandler()
{
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
                enemy.enemyData.hp -= bullet.bulletData.dmg;

                player.bullets.erase(player.bullets.begin() + j);

                if (enemy.enemyData.hp <= 0)
                {
                    std::cout << "Enemy destroyed at index: " << i << std::endl;
                    enemys.erase(enemys.begin() + i);
                    enemyRemoved = true;
                    break;
                }
            }
            else
            {
                ++j;
            }
        }

        if (!enemyRemoved)
        {
            ++i;
        }
    }
}
void Game::enemySpawner()
{
    if (enemys.size() < 40)
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
        Enemy::Data enemyData = {&window, enemyTexture, spawnPosition, {static_cast<float>(rand() % 10) - 5, static_cast<float>(rand() % 10) - 5}, {}, 10};

        enemys.push_back(Enemy(enemyData));
    }
}
void Game::bulletHandler()
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

int Game::run()
{
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f / 120.f);
    sf::Time accumulator = sf::Time::Zero;

    sf::View view(window.getDefaultView());
    sf::View uiView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    view.setCenter(player.getPosition());

    while (window.isOpen())
    {
        dt = clock.restart();
        accumulator += dt;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ui.update(window, event);

        if (ui.getUItrue())
        {
            window.clear(sf::Color::Black);
            window.setView(uiView); // Set the view to the UI view
            ui.draw(window);
        }
        else
        {
            window.clear(sf::Color::Black);
            window.setView(view); // Use the main view for game elements

            while (accumulator >= timePerFrame)
            {
                player.update();
                accumulator -= timePerFrame;

                for (auto &enemy : enemys)
                {
                    enemy.update(player.pData.position);
                }
                enemySpawner();
                stars.update(player.pData.position, 0.0f);
                nebulae.update(player.pData.position, 0.001f);
                dust.update(player.pData.position, 0.005f);
                planets.update(player.pData.position, 0.01f);
            }

            sf::Vector2f playerPosition = player.getPosition();
            sf::Vector2f viewCenter = view.getCenter();

            sf::Vector2f distance = player.pData.position - viewCenter;
            float distanceLength = std::sqrt(distance.x * distance.x + distance.y * distance.y);

            float speedFactor = 1.2f;
            float followSpeed = distanceLength * speedFactor;

            if (distanceLength > 1.0f)
            {
                sf::Vector2f direction = distance / distanceLength;
                viewCenter += direction * followSpeed * dt.asSeconds();
                view.setCenter(viewCenter);
            }

            bulletHandler();
            enemyHandler();
            window.setView(view);

            stars.draw(window);
            nebulae.draw(window);
            dust.draw(window);
            planets.draw(window);
            player.draw();
            for (auto &enemy : enemys)
            {
                enemy.draw();
            }
        }

        window.display();
    }
    return 0;
}