#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platform.hpp"
#include "Hazard.hpp"
#include "Gem.hpp"
#include "Door.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class CollisionManager
{
public:
    void check(Player& entity, std::vector<Platform>& platforms, sf::RenderWindow& window);
    void check(Enemy& entity, std::vector<Platform>& platforms, sf::RenderWindow& window);

    bool checkHazardCollision(Player& player, Hazard& hazard);
    bool checkHazardCollision(Enemy& enemy, Hazard& hazard);

    bool checkGemCollision(Player& player, Gem& gem);
    bool checkDoorCollision(Player& player, Door& door);
    bool checkButtonCollision(Player& player, Button& button);

private:
    void resolveCollision(Player& player, const sf::FloatRect& platformBounds);
    void resolveCollision(Enemy& enemy, const sf::FloatRect& platformBounds);
};