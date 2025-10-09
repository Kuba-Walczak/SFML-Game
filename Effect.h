#pragma once
#include <SFML/Graphics.hpp>

struct Effect {

    Effect(const sf::Vector2f& position, const std::vector<sf::Texture>& effectTexVec, sf::Vector2f& direction, const float& minScale, const float& maxScale, const int& radius, const int& maxLifeTime);

    Effect(const sf::Vector2f& position, const std::vector<sf::Texture>& effectTexVec, const float& minScale, const float& maxScale, const int& radius, const int& maxLifeTime);

    Effect(const sf::Vector2f& position, const std::vector<sf::Texture>& effectTexVec);

    sf::Sprite sprite;
    const std::vector<sf::Texture>& effectTexVec;
    const int type = 0;
    int radius = 0;
    int tile = 0;

    float animationSpeed = 0;
    int animationFrame = 0;
    float lifeTime = 0;
    float maxLifeTime = 0;
    bool alive = true;

    void update(const float& timeScale);

};