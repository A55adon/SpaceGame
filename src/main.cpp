#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Game");
    sf::Clock clock;                                    // To keep track of time
    const sf::Time frameTime = sf::seconds(1.f / 30.f); // 30 FPS

    Player::Data playerData = {{"res/Ships/PNGs/Nairan - Battlecruiser - Base.png"}, {0, 0}, {1, 0}};
    Player player(playerData);

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart(); // Get the time since last frame

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Ensure we only update and draw if enough time has passed
        if (elapsed >= frameTime)
        {
            player.update(); // Update player position

            window.clear(sf::Color::Black);

            player.draw(window); // Draw player

            window.display();
        }
        else
        {
            // Sleep for the remaining time to maintain the desired frame rate
            sf::sleep(frameTime - elapsed);
        }
    }

    return 0;
}
