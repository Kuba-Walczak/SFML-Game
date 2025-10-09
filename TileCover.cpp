#include "TileCover.h"

TileCover::TileCover(const sf::Vector2f& position, const sf::Texture& texture) :
sprite(texture) {
    sprite.setPosition(position);
}

void TileCover::increaseOpacity(const float &amount) {
    opacity += amount;
    opacity = std::min(255.f, opacity);
}

void TileCover::decreaseOpacity(const float &amount) {
    opacity -= amount;
    opacity = std::max(0.f, opacity);
}

sf::FloatRect TileCover::getBounds() {
    return sprite.getGlobalBounds();
}