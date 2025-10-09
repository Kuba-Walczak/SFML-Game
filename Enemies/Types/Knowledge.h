#pragma once
#include "../Enemy.h"

struct Knowledge : Enemy {

    Knowledge(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, const int& tile);

    float getDamage();

    void update(const float& timeScale, Player& player) override;

    sf::FloatRect getBounds() override;

};