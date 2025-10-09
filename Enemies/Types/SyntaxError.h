#pragma once
#include "../Enemy.h"

#include <SFML/Graphics.hpp>

struct SyntaxError : Enemy {

    SyntaxError(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, const float& activationDistance, CollisionSide requiredSide,const int& tile);

    SyntaxError(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, const float& activationDistance, CollisionSide requiredSide, const float& scale, const int& tile);

    const float damage = .15f;
    const float activationDistance = 0;
    CollisionSide requiredSide = CollisionSide::None;

    float getDamage();

    void update(const float& timeScale, Player& player) override;

    sf::FloatRect getBounds() override;

};