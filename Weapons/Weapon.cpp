#include "Weapon.h"

//TEX SIZE: 200X200
//COLLISION SIZE: 100X100

Weapon::Weapon(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Projectile>>& projectileVec, std::vector<std::unique_ptr<Effect>>& effectVec) :
sprite(weaponTexMap.at("Empty400").at(0)), weaponTexMap(weaponTexMap), effectTexMap(effectTexMap), projectileVec(projectileVec), effectVec(effectVec) {
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().size.x / 2, sprite.getGlobalBounds().size.y / 2));
    sprite.setPosition(position);
}

void Weapon::update(const float& timeScale) {
    //NOT USED
}

void Weapon::update(const float& timeScale, Player& player) {
    //SUBCLASS OVERRIDES
}

sf::FloatRect Weapon::getBounds() {
    sprite.scale(sf::Vector2f(0.25f, 0.25f));
    auto tempBounds = sprite.getGlobalBounds();
    sprite.scale(sf::Vector2f(4, 4));
    return tempBounds;
}