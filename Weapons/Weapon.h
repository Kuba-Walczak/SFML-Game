#pragma once
#include "../Utility/Updatable.h"
#include "../Utility/Usable.h"
#include "../Collider.h"
#include "../Effect.h"
#include "../Player.h"

#include <SFML/Graphics.hpp>
#include <map>

//TEX SIZE: 400X400
//COLLISION SIZE: 100X100

struct  Projectile;

struct Weapon : Updatable, Usable, Collider {

    Weapon(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& weaponTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Projectile>>& projectileVec, std::vector<std::unique_ptr<Effect>>& effectVec);

    sf::Sprite sprite;
    const std::map<std::string, std::vector<sf::Texture>>& weaponTexMap;
    const std::map<std::string, std::vector<sf::Texture>>& effectTexMap;
    std::vector<std::unique_ptr<Projectile>>& projectileVec;
    std::vector<std::unique_ptr<Effect>>& effectVec;
    bool pickedUp = false;
    bool upgraded = false;

    float timeThreshold = 1;
    float animationSpeed = 0;
    int animationFrame = 0;
    bool alive = true;

    void update(const float& timeScale) override;

    void update(const float& timeScale, Player& player) override;

    sf::FloatRect getBounds() override;

};