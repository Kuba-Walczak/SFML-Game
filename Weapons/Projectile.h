#pragma once
#include "../Utility/Updatable.h"
#include "../Collider.h"
#include "../Effect.h"

#include <SFML/Graphics.hpp>
#include <map>

//TEX SIZE: 100X100
//COLLISION SIZE: 25X25

struct Projectile : Updatable, Collider {

    Projectile(const sf::Vector2f& position, const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, sf::Vector2f direction, const float& maxLifeTime);

    sf::Sprite sprite;
    const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap;
    const std::map<std::string, std::vector<sf::Texture>>& effectTexMap;
    std::vector<std::unique_ptr<Effect>>& effectVec;
    sf::Vector2f direction;
    int tile = 0;
    bool upgraded = false;

    float timeThreshold = 0;
    float animationSpeed = 0;
    int animationFrame = 0;
    float lifeTime = 0;
    float maxLifeTime = 0;
    bool alive = true;

    void update(const float& timeScale) override;

    void update(const float& timeScale, Player& player) override;

    sf::FloatRect getBounds() override;

};