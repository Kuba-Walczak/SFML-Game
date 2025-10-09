#pragma once
#include "../Utility/Updatable.h"
#include "../Collider.h"
#include "../Effect.h"
#include "../Player.h"

#include <SFML/Graphics.hpp>
#include <map>

//FOR ENEMIES
//TEX SIZE: 400X400
//COLLISION SIZE: 200X200

//FOR ENEMY PROJECTILES
//TEX SIZE: 200X200
//COLLISION SIZE: 100X100

struct Enemy : Updatable, Collider {

    Enemy(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, const int& tile);

    sf::Sprite sprite;
    const std::map<std::string, std::vector<sf::Texture>>& enemyTexMap;
    const std::map<std::string, std::vector<sf::Texture>>& effectTexMap;
    std::vector<std::unique_ptr<Effect>>& effectVec;
    sf::Vector2f velocity;
    const int& tile = 0;

    float timeThreshold = 0;
    float animationSpeed = 0;
    int animationFrame = 0;
    float sleepLength = 0;
    bool compile = false;
    bool alive = true;

    virtual float getDamage() = 0;

    void update(const float& timeScale) override;

    void update(const float& timeScale, Player& player) override;

};