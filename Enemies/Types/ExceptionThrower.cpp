#include "ExceptionThrower.h"
#include "../../Utility/RNG.h"

#include <cmath>
#include <fmt/base.h>

ExceptionThrower::ExceptionThrower(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Projectile>>& projectileVec, std::vector<std::unique_ptr<Effect>>& effectVec, const float& activationDistance, const int& tile) :
Enemy(position, enemyTexMap, effectTexMap, effectVec, tile), activationDistance(activationDistance), weaponTexMap(weaponTexMap), projectileVec(projectileVec) {
    auto randomScale = RNG::randomFloat(0.5f, 1);
    sprite.setScale(sf::Vector2f(randomScale, randomScale));
}

ExceptionThrower::ExceptionThrower(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Projectile>>& projectileVec, std::vector<std::unique_ptr<Effect>>& effectVec, const float& activationDistance, const float& scale, const int& tile) :
Enemy(position, enemyTexMap, effectTexMap, effectVec, tile), activationDistance(activationDistance), weaponTexMap(weaponTexMap), projectileVec(projectileVec) {
    sprite.setScale(sf::Vector2f(scale, scale));
}

float ExceptionThrower::getDamage() {
    return damage;
}

void ExceptionThrower::update(const float& timeScale, Player& player) {

    if (!compile) {

        if (sleepLength > 0) {
            sprite.setTexture(enemyTexMap.at("ExceptionThrowerSleep").at(0));
            sleepLength -= timeScale * .1f;
            std::max(0.f, sleepLength);
        }
        else {
            animationSpeed += timeScale * .5f;
            while (animationSpeed >= 1) {
                animationSpeed -= 1;
                sprite.setTexture(enemyTexMap.at("ExceptionThrowerIdle").at(animationFrame++));
                if (animationFrame >= enemyTexMap.at("ExceptionThrowerIdle").size()) {
                    animationFrame = 0;
                }
            }

            timeThreshold += timeScale;
            while (timeThreshold >= 1) {
                timeThreshold -= 1;
                for (int i = 0; i < RNG::randomInt(0, 25); ++i)
                    effectVec.emplace_back(std::make_unique<Effect>(Effect(sprite.getPosition(), effectTexMap.at("Glitch"), .1f, .4f, sprite.getScale().x * 100, 10)));
            }

            auto deltaX = player.sprite.getPosition().x - this->sprite.getPosition().x;
            auto deltaY = player.sprite.getPosition().y - this->sprite.getPosition().y;
            if ((std::hypot(deltaX, deltaY) < activationDistance)) {
                additionalTimeThreshold += timeScale * 0.1f;
                if (additionalTimeThreshold >= 5) {
                    additionalTimeThreshold -= 5;
                    auto angle = std::atan2(deltaX, deltaY);
                    auto directionX = std::sin(angle);
                    auto directionY = std::cos(angle);
                    velocity = sf::Vector2f(directionX, directionY) * timeScale;
                    projectileVec.emplace_back(std::make_unique<ExceptionThrowerProjectile>(ExceptionThrowerProjectile(sprite.getPosition(), weaponTexMap, effectTexMap, effectVec, sf::Vector2f(directionX, directionY), 20)));
                }
            }
        }

    }
    else {
    animationSpeed += timeScale;
        while (animationSpeed >= 1) {
            animationSpeed -= 1;
            sprite.setTexture(enemyTexMap.at("ExceptionThrowerCompile").at(animationFrame++));
            if (animationFrame >= enemyTexMap.at("ExceptionThrowerCompile").size()) {
                effectVec.emplace_back(std::make_unique<Effect>(Effect(sprite.getPosition(), effectTexMap.at("Compiled"))));
                alive = false;
                player.increaseKnowledge(.35f);
                effectVec.emplace_back(std::make_unique<Effect>(Effect(player.sprite.getPosition(), effectTexMap.at("Knowledge"))));
                break;
            }
        }
    }

}

sf::FloatRect ExceptionThrower::getBounds() {
    sprite.scale(sf::Vector2f(0.5f, 0.5f));
    auto tempBounds = sprite.getGlobalBounds();
    sprite.scale(sf::Vector2f(2, 2));
    return tempBounds;
}

ExceptionThrowerProjectile::ExceptionThrowerProjectile(const sf::Vector2f& position, const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, sf::Vector2f direction, const float& maxLifeTime) :
Projectile(position, weaponTexMap, effectTexMap, effectVec, direction, maxLifeTime) {
    sprite.setTexture(RNG::randomTexture(weaponTexMap.at("ExceptionThrowerProjectile")), true);
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().size.x / 2, sprite.getGlobalBounds().size.y / 2));
}

void ExceptionThrowerProjectile::update(const float& timeScale) {
    lifeTime += timeScale * .1f;
    if (lifeTime >= maxLifeTime) {
        alive = false;
    }
    sprite.move(direction * timeScale * 5.f);
    timeThreshold += timeScale;
    while (timeThreshold >= 1) {
        timeThreshold -= 1;
        for (int i = 0; i < RNG::randomInt(0, 50); ++i)
            effectVec.emplace_back(std::make_unique<Effect>(Effect(sprite.getPosition(), effectTexMap.at("Glitch"), direction, .2f, .5f, 25, 5)));
    }
}