#pragma once
#include "../Weapon.h"
#include "../Projectile.h"

#include <SFML/Graphics.hpp>
#include <map>

struct ThreadManager : Weapon {

    ThreadManager(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Projectile>>& projectileVec, std::vector<std::unique_ptr<Effect>>& effectVec);

    float requiredStamina = .5f;
    int requiredKnowledgeLevel = 6;
    int upgradeLevelThreshold = 9;

    void update(const float& timeScale, Player& player) override;

    void use(const float& timeScale, Player& player, const sf::RenderWindow& window, const sf::View& view) override;

};

struct ThreadManagerProjectile : Projectile {

    ThreadManagerProjectile(const sf::Vector2f& position, const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, sf::Vector2f direction, const float& maxLifeTime);

    void update(const float& timeScale) override;

};