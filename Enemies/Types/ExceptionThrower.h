#pragma once
#include "../Enemy.h"
#include "../../Weapons/Projectile.h"

struct ExceptionThrower : Enemy {

    ExceptionThrower(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Projectile>>& projectileVec, std::vector<std::unique_ptr<Effect>>& effectVec, const float& activationDistance, const int& tile);

    ExceptionThrower(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Projectile>>& projectileVec, std::vector<std::unique_ptr<Effect>>& effectVec, const float& activationDistance, const float& scale, const int& tile);

    const float damage = .2f;
    const float activationDistance = 0;
    const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap;
    std::vector<std::unique_ptr<Projectile>>& projectileVec;
    float additionalTimeThreshold = 0;

    float getDamage();

    void update(const float& timeScale, Player& player) override;

    sf::FloatRect getBounds() override;

};

struct ExceptionThrowerProjectile : Projectile {

    ExceptionThrowerProjectile(const sf::Vector2f& position, const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, sf::Vector2f direction, const float& maxLifeTime);

    const float damage = .2f;

    float getDamage();

    void update(const float& timeScale) override;

};