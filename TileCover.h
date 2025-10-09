#pragma once
#include "Collider.h"

struct TileCover : Collider {

    TileCover(const sf::Vector2f& position, const sf::Texture& texture);

    sf::Sprite sprite;
    float opacity = 0;

    void increaseOpacity(const float& amount);

    void decreaseOpacity(const float& amount);

    sf::FloatRect getBounds() override;

};