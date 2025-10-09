#include "Effect.h"
#include "Utility/RNG.h"

Effect::Effect(const sf::Vector2f& position, const std::vector<sf::Texture>& effectTexVec, const float& minScale, const float& maxScale, const int& radius, const int& maxLifeTime) :
sprite(effectTexVec.at(0)), effectTexVec(effectTexVec), radius(radius), maxLifeTime(maxLifeTime) {
    sprite.setTexture(RNG::randomTexture(effectTexVec), true);
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().size.x / 2, sprite.getGlobalBounds().size.y / 2));
    sprite.setPosition(position);
    sprite.move(sf::Vector2f(RNG::randomFloatGaussian(0, radius), RNG::randomFloatGaussian(0, radius)));
    auto randomScale = RNG::randomFloat(minScale, maxScale);
    sprite.setScale(sf::Vector2f(randomScale, randomScale));
    sprite.setColor(sf::Color(255, 255, 255, RNG::randomInt(50, 255)));
    this->maxLifeTime = RNG::randomFloatGaussian(maxLifeTime, 3);
}

Effect::Effect(const sf::Vector2f& position, const std::vector<sf::Texture>& effectTexVec, sf::Vector2f& direction, const float& minScale, const float& maxScale, const int& radius, const int& maxLifeTime) :
sprite(effectTexVec.at(0)), effectTexVec(effectTexVec), radius(radius), maxLifeTime(maxLifeTime), type(1) {
    sprite.setTexture(RNG::randomTexture(effectTexVec), true);
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().size.x / 2, sprite.getGlobalBounds().size.y / 2));
    sprite.setPosition(position);
    sprite.move(sf::Vector2f(RNG::randomFloatGaussian(0, radius), RNG::randomFloatGaussian(0, radius)));
    auto randomScale = RNG::randomFloat(minScale, maxScale);
    sprite.setScale(sf::Vector2f(randomScale, randomScale));
    sprite.setColor(sf::Color(255, 255, 255, RNG::randomInt(50, 255)));
    this->maxLifeTime = RNG::randomFloatGaussian(maxLifeTime, 3);
    sprite.setRotation(sf::radians(std::atan2(direction.y, direction.x)) + sf::degrees(90));
}

Effect::Effect(const sf::Vector2f& position, const std::vector<sf::Texture>& effectTexVec) :
sprite(effectTexVec.at(0)), effectTexVec(effectTexVec), type(1) {
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().size.x / 2, sprite.getGlobalBounds().size.y / 2));
    sprite.setPosition(position);
}

void Effect::update(const float& timeScale) {
    if (type == 0) {
        lifeTime += timeScale;
        if (lifeTime >= maxLifeTime)
            alive = false;
    }
    else if (type == 1) {
        animationSpeed += timeScale * .5f;
        while (animationSpeed >= 1 and alive) {
            animationSpeed -= 1;
            sprite.setTexture(effectTexVec.at(animationFrame++));
            if (animationFrame >= effectTexVec.size()) {
                alive = false;
            }
        }
    }
}