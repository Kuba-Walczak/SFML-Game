#include "Projectile.h"

//TEX SIZE: 100X100
//COLLISION SIZE: 25X25

Projectile::Projectile(const sf::Vector2f& position, const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, sf::Vector2f direction, const float& maxLifeTime) :
sprite(weaponTexMap.at("Empty100").at(0)), weaponTexMap(weaponTexMap), effectTexMap(effectTexMap), effectVec(effectVec), direction(direction), maxLifeTime(maxLifeTime) {
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().size.x / 2, sprite.getGlobalBounds().size.y / 2));
    sprite.setPosition(position);
}

void Projectile::update(const float& timeScale) {
    //SUBCLASS OVERRIDES
}

void Projectile::update(const float& timeScale, Player& player) {
    //NOT USED
}

sf::FloatRect Projectile::getBounds() {
    sprite.scale(sf::Vector2f(0.25f, 0.25f));
    auto tempBounds = sprite.getGlobalBounds();
    sprite.scale(sf::Vector2f(4, 4));
    return tempBounds;
}