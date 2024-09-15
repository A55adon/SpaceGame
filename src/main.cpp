#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Game");

    // Set frame rate limit
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 FPS
    sf::Time accumulator = sf::Time::Zero;

    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("res/Background/All.png")) // Assuming space_bg.png is your background image
    {
        printf("Loading background failed");
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Create the view (camera)
    sf::View view(window.getDefaultView());

    // Initialize player data
    Player::Data playerData = {"res/Ships/PNGs/Nairan - Battlecruiser - Base.png", {400, 300}, {0, 0}, window};
    Player player(playerData);

    // Set view to the player's starting position
    view.setCenter(playerData.position);

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        accumulator += dt;

        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        while (accumulator >= timePerFrame)
        {
            accumulator -= timePerFrame;
            player.update();
        }

        // Camera movement logic with latency
        sf::Vector2f viewCenter = view.getCenter();
        sf::Vector2f playerPosition = playerData.position;

        // Define the size of the "dead zone" in the center where the camera won't move
        sf::FloatRect deadZone(viewCenter.x - 100.f, viewCenter.y - 100.f, 200.f, 200.f);

        // Check if the player is outside the dead zone
        if (!deadZone.contains(playerPosition))
        {
            // Interpolate the view position to follow the player with a smooth transition
            float followSpeed = 0.05f; // Controls how smoothly the camera follows the player (higher = slower follow)
            viewCenter += (playerPosition - viewCenter) * followSpeed;
            view.setCenter(viewCenter);
        }

        // Apply the view to the window (camera follows the player)
        window.setView(view);

        window.clear(sf::Color::Black);

        // Draw the background
        window.draw(backgroundSprite);

        // Draw the player
        player.draw();

        window.display();
    }

    return 0;
}
