#include "CollisionTrigger.h"
#include "../../Utility/RNG.h"

#include <cmath>

CollisionTrigger::CollisionTrigger(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Projectile>>& projectileVec, std::vector<std::unique_ptr<Effect>>& effectVec) :
Weapon(position, weaponTexMap, effectTexMap, projectileVec, effectVec) {}

void CollisionTrigger::update(const float& timeScale, Player& player) {
    if (player.knowledgeLevel >= upgradeLevelThreshold)
        upgraded = true;
    if (pickedUp and player.knowledgeLevel < requiredKnowledgeLevel)
        sprite.setColor(sf::Color(50, 50, 50, 255));
    else
        sprite.setColor(sf::Color(255, 255, 255, 255));
    animationSpeed += timeScale;
    if (upgraded) {
        while (animationSpeed >= 1) {
            animationSpeed -= 1;
            sprite.setTexture(weaponTexMap.at("CollisionTriggerIdleUpgraded").at(animationFrame++));
            if (animationFrame >= weaponTexMap.at("CollisionTriggerIdleUpgraded").size()) {
                animationFrame = 0;
            }
        }
    }
    else
        while (animationSpeed >= 1) {
            animationSpeed -= 1;
            sprite.setTexture(weaponTexMap.at("CollisionTriggerIdle").at(animationFrame++));
            if (animationFrame >= weaponTexMap.at("CollisionTriggerIdle").size()) {
                animationFrame = 0;
            }
        }
}

void CollisionTrigger::use(const float& timeScale, Player& player, const sf::RenderWindow& window, const sf::View& view) {
    auto deltaX = static_cast<int>(sf::Mouse::getPosition(window).x - window.getSize().x / 2);
    auto deltaY = static_cast<int>(sf::Mouse::getPosition(window).y - window.getSize().y / 2);
    auto angle = std::atan2(deltaX, deltaY);
    auto directionX = std::sin(angle);
    auto directionY = std::cos(angle);
    timeThreshold += timeScale * 0.03f;
    while (timeThreshold >= 1) {
        timeThreshold -= 1;
        if (player.stamina >= requiredStamina and player.knowledgeLevel >= requiredKnowledgeLevel) {
            player.stamina -= requiredStamina;
            if (upgraded) {
                projectileVec.emplace_back(std::make_unique<CollisionTriggerProjectile>(CollisionTriggerProjectile(player.sprite.getPosition(), weaponTexMap, effectTexMap, effectVec, sf::Vector2f(directionX, directionY), 5)));
                projectileVec.back()->upgraded = true;
            }
            else
                projectileVec.emplace_back(std::make_unique<CollisionTriggerProjectile>(CollisionTriggerProjectile(player.sprite.getPosition(), weaponTexMap, effectTexMap, effectVec, sf::Vector2f(directionX, directionY), 5)));
        }
        else if (player.stamina < requiredStamina)
            effectVec.emplace_back(std::make_unique<Effect>(Effect(player.sprite.getPosition(), effectTexMap.at("NoStamina"))));
        else
            effectVec.emplace_back(std::make_unique<Effect>(Effect(player.sprite.getPosition(), effectTexMap.at("NoKnowledge"))));
        if (player.performanceMode)
            projectileVec.back()->sprite.setTexture(weaponTexMap.at("PerformanceProjectile").at(0));
    }
}

CollisionTriggerProjectile::CollisionTriggerProjectile(const sf::Vector2f& position, const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, sf::Vector2f direction, const float& maxLifeTime) :
Projectile(position, weaponTexMap, effectTexMap, effectVec, direction, maxLifeTime) {}

void CollisionTriggerProjectile::update(const float& timeScale) {
    sprite.move(direction * timeScale * 15.f);
    lifeTime += timeScale * .1f;
    if (lifeTime >= maxLifeTime) {
        alive = false;
    }
    timeThreshold += timeScale;
    while (timeThreshold >= 1) {
        timeThreshold -= 1;
        if (!bounced)
            for (int i = 0; i < RNG::randomInt(0, 25); ++i)
                effectVec.emplace_back(std::make_unique<Effect>(Effect(sprite.getPosition(), effectTexMap.at("CollisionTriggerProjectile"), direction, .2f, .4f, 2, 2)));
        else
            for (int i = 0; i < RNG::randomInt(0, 25); ++i)
                effectVec.emplace_back(std::make_unique<Effect>(Effect(sprite.getPosition(), effectTexMap.at("CollisionTriggerBounceProjectile"), direction, .4f, .4f, 2, 50)));

    }
}