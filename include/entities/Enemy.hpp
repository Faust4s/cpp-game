#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "SpriteAnimator.hpp"
#include "Config.hpp"

class Player;

enum class EnemyState
{
    PATROL,
    CHASE
};

class Enemy
{
public:
    Enemy(float x, float y, sf::Color color = sf::Color::Magenta, const std::string &spriteFile = "");

    void update(float dt, const std::vector<Player *> &players);
    void draw(sf::RenderWindow &window);
    sf::FloatRect getBounds() const;

    void applyGravity(float dt);
    void setOnGround(bool v);
    void setPositionX(float x);
    void setPositionY(float y);
    void setVelocityY(float v);
    float getVelocityY() const;

    bool isAlive() const;
    void kill();

    EnemyState state = EnemyState::PATROL;
    float patrolSpeed = 60.f;
    float patrolDirection = 1.f; // 1 = dešinėn, -1 = kairėn
    float turnCooldown = 0.f;    // kad nesukiotųsi vietoje
    
    void patrol(float dt);
    void reversePatrolDirection();

private:
    sf::RectangleShape shape;
    SpriteAnimator animator;

    float velocityY = 0.f;
    float gravity = Config::ENEMY_GRAVITY;
    float speed = Config::ENEMY_SPEED;
    float previousX = 0.f;
    bool onGround = false;
    bool alive = true;

    void chasePlayer(const Player &target, float dt);
    const Player *findClosest(const std::vector<Player *> &players) const;
};