#pragma once
#include <SFML/Graphics.hpp>

struct View {

    bool zoomOut = false;
    bool showOverlay = false;
    float shakeStrength = 0;

    sf::View view = sf::View(sf::Vector2f(), sf::Vector2f(1920, 1080));
    int originalSizeX = view.getSize().x;

    void update(const float& timeScale);

    void shake(const int& shakeStrength);

};