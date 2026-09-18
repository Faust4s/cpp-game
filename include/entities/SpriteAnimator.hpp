#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Config.hpp"

class SpriteAnimator
{
public:
    SpriteAnimator() = default;

    [[nodiscard]] bool load(const std::string& spriteFile, float hitboxSize = Config::PLAYER_HITBOX);
    void update(float dt, float currentX, float previousX);
    void draw(sf::RenderWindow& window);
    void syncPosition(sf::Vector2f position, sf::Vector2f hitboxSize);
    void setFacingRight(bool right);
    void resetToIdle();

    bool isLoaded() const { return hasSprite; }

private:
    sf::Texture spriteSheet;
    sf::Sprite sprite;
    bool hasSprite = false;
    bool facingRight = true;
    int animationIndex = 0;
    float animationTimer = 0.f;

    void updateTextureRect(int frame = -1);
    void syncVisualPosition(sf::Vector2f position, sf::Vector2f hitboxSize);
    void createSpriteSheet(const std::string& spriteFile, float hitboxSize);
};