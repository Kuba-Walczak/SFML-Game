#pragma once
#include "Collider.h"

#include <SFML/Graphics.hpp>

struct Collision : Collider {

    Collision(const sf::Vector2f& position, const sf::Texture& texture);

    sf::Sprite sprite;

    sf::FloatRect getBounds() override;

};