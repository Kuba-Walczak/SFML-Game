#include "Knowledge.h"
#include "../../Utility/RNG.h"

Knowledge::Knowledge(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, const int& tile) :
Enemy(position, enemyTexMap, effectTexMap, effectVec, tile) {
    sprite.setTexture(RNG::randomTexture(enemyTexMap.at("Knowledge")), true);
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().size.x / 2, sprite.getGlobalBounds().size.y / 2));

}

float Knowledge::getDamage() {
    return 0;
}

void Knowledge::update(const float& timeScale, Player& player) {
    timeThreshold += timeScale;
    while (timeThreshold >= 1) {
        timeThreshold -= 1;
        for (int i = 0; i < RNG::randomInt(0, 25); ++i)
            effectVec.emplace_back(std::make_unique<Effect>(Effect(sprite.getPosition(), effectTexMap.at("BinaryBlue"), .1f, .5f, 40, 10)));
    }
}

sf::FloatRect Knowledge::getBounds() {
    sprite.scale(sf::Vector2f(0.5f, 0.5f));
    auto tempBounds = sprite.getGlobalBounds();
    sprite.scale(sf::Vector2f(2, 2));
    return tempBounds;
}