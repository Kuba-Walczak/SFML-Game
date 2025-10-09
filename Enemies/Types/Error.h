#pragma once
#include "../Enemy.h"

struct Error : Enemy {

    Error(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, const int& tile);

    const float damage = .1f;

    float getDamage();

    void update(const float& timeScale, Player& player) override;

    sf::FloatRect getBounds() override;

};