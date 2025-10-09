#pragma once
#include <SFML/Graphics.hpp>

struct Player;

struct Usable {

    virtual ~Usable();
    virtual void use(const float& timeScale, Player& player, const sf::RenderWindow& window, const sf::View& view) = 0;
    
};