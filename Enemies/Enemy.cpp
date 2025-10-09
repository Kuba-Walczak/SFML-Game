#include "Enemy.h"

//TEX SIZE: 400X400
//COLLISION SIZE: 200X200

//FOR ENEMY PROJECTILES
//TEX SIZE: 200X200
//COLLISION SIZE: 100X100

Enemy::Enemy(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, const int& tile) :
sprite(enemyTexMap.at("Empty400").at(0)), enemyTexMap(enemyTexMap), effectTexMap(effectTexMap), effectVec(effectVec), tile(tile) {
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().size.x / 2, sprite.getGlobalBounds().size.y / 2));
    sprite.setPosition(position);
}

void Enemy::update(const float& timeScale) {
    //NOT USED
}

void Enemy::update(const float& timeScale, Player& player) {
    //SUBCLASS OVERRIDES
}