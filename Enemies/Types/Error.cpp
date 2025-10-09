#include "Error.h"
#include "../../Utility/RNG.h"

Error::Error(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, const int& tile) :
Enemy(position, enemyTexMap, effectTexMap, effectVec, tile) {
    sprite.setTexture(RNG::randomTexture(enemyTexMap.at("Error")));
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().size.x / 2, sprite.getGlobalBounds().size.y / 2));
    auto randomScale = RNG::randomFloat(0.5f, 1);
    sprite.setScale(sf::Vector2f(randomScale, randomScale));
    sprite.setRotation(sf::degrees(RNG::randomInt(0, 360)));
}

float Error::getDamage() {
    return damage;
}

void Error::update(const float& timeScale, Player& player) {
    timeThreshold += timeScale;
    while (timeThreshold >= 1) {
        timeThreshold -= 1;
        for (int i = 0; i < RNG::randomInt(0, 500); ++i)
            effectVec.emplace_back(std::make_unique<Effect>(Effect(sprite.getPosition(), effectTexMap.at("Glitch"), .1f, .4f, sprite.getScale().x * 50, 3)));
    }
}

sf::FloatRect Error::getBounds() {
    sprite.scale(sf::Vector2f(0.2f, 0.2f));
    auto tempBounds = sprite.getGlobalBounds();
    sprite.scale(sf::Vector2f(5, 5));
    return tempBounds;
}