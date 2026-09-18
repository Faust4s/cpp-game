#include "Hazard.hpp"
#include "Assets.hpp"

Hazard::Hazard(float x, float y, float width, float height, HazardType type)
: type(type)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);

    if (type == HazardType::playerOneRiver)
        applyTexture(Assets::Textures::HAZARD_PLAYER_ONE);
    else if (type == HazardType::playerTwoRiver)
        applyTexture(Assets::Textures::HAZARD_PLAYER_TWO);
    else
        applyTexture(Assets::Textures::HAZARD_GENERAL);
}

HazardType Hazard::getType() { return type; }