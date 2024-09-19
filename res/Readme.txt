I got this code #ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Bullet.h"

class Player
{
public:
#pragma region Data Structure
    struct Data
    {
        std::string imagePath;
        std::string engineGif;
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::RenderWindow &window;
    };
#pragma endregion

#pragma region Constructor
    Player(Data &data);
    ~Player();
#pragma endregion

#pragma region Methods
    sf::Vector2f getPosition() const;
    void update();
    void draw() const;
    void shoot();
#pragma endregion

private:
#pragma region Variables
    sf::Texture shipTexture;
    sf::Sprite shipSprite;
    sf::Texture engineTexture;
    sf::Sprite engineSprite;
    std::vector<sf::IntRect> frames;
    int currentFrame;
    float animationSpeed;
    sf::Clock animationClock;
    sf::Vector2f engineOffset;
    float orbitRadius;
    bool engineVisible;
    Bullet::Data bulletData;
    bool shootable = true;
    int bulletcounter = 0;

public:
    std::vector<Bullet> bullets;
    Data pData;
    Bullet::Data bData = {&pData.window, "res/Shields/PNGs/Nairan - Frigate - Shield.png", {30, 30}, {0, 0}};

    Bullet bull;

#pragma endregion
};

#endif // PLAYER_H#include "Player.h"
#include <iostream>
#include <cmath>
#include "Bullet.h"

#pragma region Constructor

Player::Player(Data &pData)
    : pData(pData), currentFrame(0), animationSpeed(0.1f), engineVisible(false), bull(bData) // Initialize bull here
{
    if (!shipTexture.loadFromFile(pData.imagePath))
    {
        std::cerr << "Error loading player texture from " << pData.imagePath << std::endl;
        return;
    }

    shipSprite.setTexture(shipTexture);

    sf::Vector2u textureSize = shipTexture.getSize();
    shipSprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    shipSprite.setPosition(pData.position);

    if (!engineTexture.loadFromFile("res/Engine Effects/PNGs/mainship_tilesheet.png"))
    {
        std::cerr << "Error loading tilesheet from mainship_tilesheet.png" << std::endl;
    }

    int frameWidth = 128;
    int frameHeight = 128;
    int numFrames = 8;

    for (int i = 0; i < numFrames; ++i)
    {
        frames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
    }

    engineSprite.setTexture(engineTexture);
    engineSprite.setTextureRect(frames[currentFrame]);
    engineSprite.setOrigin(frameWidth / 2.0f, frameHeight / 2.0f);

    animationClock.restart();
    orbitRadius = frameWidth * 0.05f;
}

Player::~Player()
{
    // TODO: Player destructor
}

#pragma endregion

#pragma region Update

void Player::update()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(pData.window);
    sf::Vector2f mousePosWorld = pData.window.mapPixelToCoords(mousePos);

    float speed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 7.0f : 2.0f;

    pData.velocity = sf::Vector2f(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        shoot();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        pData.velocity.x = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        pData.velocity.x = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        pData.velocity.y = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        pData.velocity.y = speed;
    }
    pData.position += pData.velocity;
    shipSprite.setPosition(pData.position);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if (pData.velocity != sf::Vector2f(0, 0))
        {
            float angle = std::atan2(pData.velocity.y, pData.velocity.x) * 180 / 3.14159f;
            shipSprite.setRotation(angle + 90);
        }
    }
    else
    {
        sf::Vector2f direction = mousePosWorld - pData.position;
        float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;
        shipSprite.setRotation(angle + 90);
    }

    engineVisible = pData.velocity != sf::Vector2f(0, 0);

    if (engineVisible)
    {
        float angle = (shipSprite.getRotation() - 90) * 3.14159f / 180.0f;
        float engineX = shipSprite.getPosition().x - orbitRadius * std::cos(angle);
        float engineY = shipSprite.getPosition().y - orbitRadius * std::sin(angle);
        engineSprite.setPosition(engineX, engineY);
        engineSprite.setRotation(shipSprite.getRotation());

        sf::Time dt = animationClock.getElapsedTime();
        if (dt.asSeconds() >= animationSpeed)
        {
            currentFrame = (currentFrame + 1) % frames.size();
            engineSprite.setTextureRect(frames[currentFrame]);
            animationClock.restart();
        }
    }

    if (!shootable && bulletcounter > 4)
    {
        shootable = true;
        bulletcounter = 0;
    }
    else
    {
        bulletcounter++;
    }

    bull.update();

    std::cout << "Number of bullets: " << bullets.size() << std::endl;

    if (!bullets.empty())
    {
        Bullet &firstBullet = bullets[0];

        std::cout << "First bullet position: ("
                  << firstBullet.bulletData.position.x << ", "
                  << firstBullet.bulletData.position.y << ")" << std::endl;

        std::cout << "First bullet velocity: ("
                  << firstBullet.bulletData.velocity.x << ", "
                  << firstBullet.bulletData.velocity.y << ")" << std::endl;

        std::cout << "First bullet image path: "
                  << firstBullet.bulletData.path << std::endl;
    }

    // Continue updating the bullets

    for (auto &bullet : bullets)
    {
        bullet.update();
    }
}

void Player::shoot()
{

    if (shootable)
    {
        bData.position = pData.position;
        Bullet bullet(bData);
        bullets.push_back(bullet);
        shootable = false;
    }
}

#pragma endregion

#pragma region Draw

void Player::draw() const
{
    pData.window.draw(shipSprite);
    if (engineVisible)
    {
        pData.window.draw(engineSprite);
    }

    bull.draw(pData.window);

    for (const auto &bullet : bullets)
    {
        bullet.draw(pData.window);
    }
}

#pragma endregion

sf::Vector2f Player::getPosition() const
{
    return pData.position;
}for a player and this code for a bullet:
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class Bullet
{
public:
    struct Data
    {
        sf::RenderWindow *window;
        std::string path;
        sf::Vector2f position;
        sf::Vector2f velocity;
    };

#pragma region Constructor
    Bullet(Data &bData);
#pragma endregion

#pragma region Methods
    void update();
    void draw(sf::RenderWindow &window) const;
#pragma endregion

#pragma region Variables
    sf::Texture bTexture;
    sf::Sprite bSprite;

    Data bulletData;
#pragma endregion
};#include "Bullet.h"
#include <iostream>

#pragma region Constructor

Bullet::Bullet(Data &bData) : bulletData(bData)
{
    if (!bTexture.loadFromFile(bData.path))
    {
        std::cerr << "Error loading bullet texture from " << bData.path << std::endl;
        return;
    }

    bSprite.setTexture(bTexture);

    bSprite.setPosition(bulletData.position);
    if (!bSprite.getTexture())
    {
        std::cerr << "Bullet sprite does not have a texture applied." << std::endl;
    }
    bSprite.setScale(0.5, 0.5);
}

#pragma endregion

#pragma region Methods
void Bullet::draw(sf::RenderWindow &win) const
{
    win.draw(bSprite);
}
void Bullet::update()
{
    bulletData.position += bulletData.velocity;

    bSprite.setPosition(bulletData.position);
}

#pragma endregion and my problem is that the bullets arent rendered propperly when stored in a vector, I found someone with a similar problem and he fixed it like this, he  had this code: 

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.hpp"
#include "Global.hpp"
#include "Enemy.hpp"


float randint(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

int main() {
    Player player;

    player.setPos({ gbl::winWidth / 2.f, gbl::winHeight / 2.f });

    std::vector<Enemy> enemies;

    sf::RenderWindow window(sf::VideoMode(gbl::winWidth, gbl::winHeight), gbl::title);

    for (int i = 0; i < 5; i++) {
        Enemy newEnemy;
        newEnemy.setPos({ randint(10 + newEnemy.getSize().x, gbl::winWidth - newEnemy.getSize().x), 100 });
        enemies.push_back(newEnemy);
        
    }

    sf::Event ev;
    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            switch (ev.type) {
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape) window.close();
                break;
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyReleased:
                if (ev.key.code == sf::Keyboard::R) {
                    player.reset();
                    for (auto& enemy : enemies) {
                        enemy.setPos({ randint(0, gbl::winWidth), 100 });
                    }
                }
            }
        }


        window.clear(gbl::bgColor);

        player.draw(window);
        for (Enemy& enemy : enemies) {
            enemy.update();
            if (enemy.getPos().y + enemy.getSize().y > gbl::winHeight + enemy.getSize().y) {
                enemy.setOffscreen();
            }
            enemy.draw(window);
        }

        player.move();

        window.display();
    }

    return 0;
}

I tried manually creating object of type Enemy and push them in the vector. When i run the game doing this everything works as intended. But when i use a for loop to fill the vector and i run the game only the player's sprite is rendered. I tried putting the for loop inside and outside the main loop but it didn't work. What should i do?

Note: the random header file is in one of the header files

#include "Enemy.hpp"
#include <random>

static inline float randint(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

Enemy::Enemy() {
    texture.loadFromFile("assets/images/Enemy.png");
    sprite.setTexture(texture);
    speed = 0.1f;
    offscreen = false;
}


sf::Sprite Enemy::getSprite() const {
    return sprite;
}

sf::Vector2f Enemy::getPos() const {
    return sprite.getPosition();
}

sf::Texture Enemy::getTexture() const {
    return texture;
}

float Enemy::getSpeed() const {
    return speed;
}

bool Enemy::getOffscreen() const {
    return offscreen;
}

sf::Vector2u Enemy::getSize() const {
    return texture.getSize();
}


void Enemy::setPos(sf::Vector2f e_pos) {
    sprite.setPosition(e_pos);
}


void Enemy::setOffscreen() {
    offscreen = true;
}



void Enemy::draw(sf::RenderWindow& d_window){
    
    d_window.draw(sprite);
}


void Enemy::update() {
    if (offscreen == false)
        sprite.move({ 0, speed });
    else {
        setPos({ randint(getSize().x, 800.f - getSize().x), 0 });
        offscreen = false;
    }
    
}

This is the code for the Enemy class
and this was the fix,in your Enemy constructor you bind the sprite to the texture

Enemy::Enemy() {
    texture.loadFromFile("assets/images/Enemy.png");
    sprite.setTexture(texture);
    speed = 0.1f;
    offscreen = false;
}

but when you insert it into the vector, a copy of the object is inserted into the vector, and the original texture is destroyed, so the sprite now has no texture. (and you don't/shouldn't implement a copy/move constructor)

you need the sf::Texture to not change its location in memory, so you need to store a pointer to it inside Enemy object instead, the best option is to use std::shared_ptr<sf::Texture> shared_ptr link instead of storing the texture by value, this way even if Enemy got copied/moved the texture will remain in the same location in memory.

PS: don't forget to initialize the shared_ptr with std::make_shared, also you could initialize only 1 enemy texture outside of Enemy and pass it into the constructor of Enemy as an argument to save memory.

// in main
auto enemyTexture = std::make_shared<sf::Texture>();
enemyTexture->loadFromFile("assets/images/Enemy.png");
for (int i = 0; i < 5; i++) {
        Enemy newEnemy{enemyTexture};
        ...
    }

// in Enemy
Enemy::Enemy(std::shared_ptr<sf::Texture> texture) {
    texture_shared_ptr = std::move(texture);
    sprite.setTexture(*texture_shared_ptr);
    speed = 0.1f;
    offscreen = false;
}

A raw pointer will work here too, but shared_ptr will save you from thinking about object lifetimes.
can you replicate this fix for my code?