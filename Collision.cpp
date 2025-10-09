#include "Collision.h"

Collision::Collision(const sf::Vector2f& position, const sf::Texture& texture) :
sprite(texture) {
    sprite.setPosition(position);
}

sf::FloatRect Collision::getBounds() {
    return sprite.getGlobalBounds();
}