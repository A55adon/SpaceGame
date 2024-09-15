#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Game");
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 FPS
    sf::Time accumulator = sf::Time::Zero;

    // Initialize player data
    Player::Data playerData = {"res/Ships/PNGs/Nairan - Battlecruiser - Base.png", {400, 300}, {0, 0}, window};
    Player player(playerData);

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        accumulator += dt;

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update game logic with a fixed time step
        while (accumulator >= timePerFrame)
        {
            accumulator -= timePerFrame;

            // Update player
            player.update();
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw player
        player.draw();

        // Display the contents of the window
        window.display();
    }

    return 0;
}
