#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Background.h"

int main()
{
#pragma region Initialization
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Game");
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::Time accumulator = sf::Time::Zero;

    Background background("res/Background/Space Background(11).png");
    Player::Data playerData = {"res/Ships/PNGs/Nairan - Battlecruiser - Base.png", "res/Engine Effects/PNGs/Nairan - Battlecruiser - Engine.png", {400, 300}, {0, 0}, window};
    Player player(playerData);

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

        window.setView(view);
#pragma endregion

#pragma region Rendering
        window.clear(sf::Color::Black);
        background.draw(window);
        player.draw();
        window.display();
#pragma endregion
    }

    return 0;
}

// specialtodos
//  TODO: camera endpositon --> following
// TODO: fix movementlagg
// TODO: unstatic movements
// TODO: schaun ob felix sich einkriegt oder ich muss das so steuerung machen mal schaun