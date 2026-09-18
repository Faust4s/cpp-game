#include "Button.hpp"
#include "Assets.hpp"

Button::Button(float x, float y, float width, float height)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);

    applyTexture(Assets::Textures::BUTTON_UNPRESSED);
}

void Button::setPressed(bool p)
{
    if (pressed == p)
        return;
        
    pressed = p;
    applyTexture(pressed ? Assets::Textures::BUTTON_PRESSED : Assets::Textures::BUTTON_UNPRESSED);
}

bool Button::isPressed() const { return pressed; }