#include "Enemy.hpp"
#include "Player.hpp"
#include <cmath>

 Enemy::Enemy(float x, float y, sf::Color color, const std::string &spriteFile)
{
    shape.setSize(sf::Vector2f(Config::ENEMY_HITBOX * Config::ENEMY_HITBOX_WIDTH_SCALE,
                               Config::ENEMY_HITBOX * Config::ENEMY_HITBOX_HEIGHT_SCALE));
    shape.setFillColor(color);
    shape.setPosition(x, y);

    previousX = x;

    if (!spriteFile.empty())
        animator.load(spriteFile, Config::ENEMY_HITBOX);
}

bool Enemy::isAlive() const { return alive; }
void Enemy::kill() { alive = false; }

sf::FloatRect Enemy::getBounds() const
{
    return shape.getGlobalBounds();
}

void Enemy::applyGravity(float dt)
{
    velocityY += gravity * dt;
    shape.move(0.f, velocityY * dt);
    animator.syncPosition(shape.getPosition(), shape.getSize());
}

void Enemy::setOnGround(bool v) { onGround = v; }
void Enemy::setVelocityY(float v) { velocityY = v; }
float Enemy::getVelocityY() const { return velocityY; }

void Enemy::setPositionX(float x)
{
    shape.setPosition(x, shape.getPosition().y);
    animator.syncPosition(shape.getPosition(), shape.getSize());
}

void Enemy::setPositionY(float y)
{
    shape.setPosition(shape.getPosition().x, y);
    animator.syncPosition(shape.getPosition(), shape.getSize());
}

const Player *Enemy::findClosest(const std::vector<Player *> &players) const
{
    const Player *closest = nullptr;
    float minDist = std::numeric_limits<float>::max();

    for (const auto *p : players)
    {
        float dx = std::fabs(p->getBounds().left - shape.getPosition().x);
        if (dx < minDist)
        {
            minDist = dx;
            closest = p;
        }
    }
    return closest;
}

void Enemy::chasePlayer(const Player &target, float dt)
{
    sf::FloatRect targetBounds = target.getBounds();
    float targetCenterX = targetBounds.left + targetBounds.width * 0.5f;
    float enemyCenterX = shape.getPosition().x + shape.getSize().x * 0.5f;

    if (targetCenterX < enemyCenterX)
    {
        shape.move(-speed * dt, 0.f);
        animator.setFacingRight(false);
    }
    else
    {
        shape.move(speed * dt, 0.f);
        animator.setFacingRight(true);
    }
    animator.syncPosition(shape.getPosition(), shape.getSize());
}

void Enemy::update(float dt, const std::vector<Player *> &players)
{
    if (!alive)
        return;

    const Player *target = findClosest(players);
    if (!target)
        return;

    float dx = std::fabs(target->getBounds().left - shape.getPosition().x);

    // --- State perėjimai ---
    if (dx < Config::ENEMY_DETECTION)
        state = EnemyState::CHASE;
    else
        state = EnemyState::PATROL;

    // --- Elgesys pagal state ---
    if (state == EnemyState::CHASE)
    {
        chasePlayer(*target, dt);
    }
    else
    {
        patrol(dt);
    }

    animator.update(dt, shape.getPosition().x, previousX);
    previousX = shape.getPosition().x;
}

void Enemy::patrol(float dt)
{
    turnCooldown -= dt;

    shape.move(patrolSpeed * patrolDirection * dt, 0.f);
    animator.setFacingRight(patrolDirection > 0.f);
    animator.syncPosition(shape.getPosition(), shape.getSize());
}

void Enemy::reversePatrolDirection()
{
    if (state == EnemyState::PATROL && turnCooldown <= 0.f)
    {
        patrolDirection *= -1.f;
        turnCooldown = 0.3f;
    }
}

void Enemy::draw(sf::RenderWindow &window)
{
    if (!alive)
        return;

    if (animator.isLoaded())
        animator.draw(window);
    else
        window.draw(shape);
}