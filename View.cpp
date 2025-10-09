#include "View.h"
#include "Utility/RNG.h"

#include <cmath>

void View::update(const float& timeScale) {

    if (zoomOut) {
        showOverlay = false;
        view.zoom(std::pow(1.05f, timeScale));
        view.setSize(sf::Vector2f(std::min(7680.f, view.getSize().x), std::min(4320.f, view.getSize().y)));
    }
    else {
        view.zoom(std::pow(.95f, timeScale));
        view.setSize(sf::Vector2f(std::max(1920.f, view.getSize().x), std::max(1080.f, view.getSize().y)));
        if (view.getSize().x == originalSizeX)
            showOverlay = true;
    }
    if (shakeStrength > 0) {
        view.move(sf::Vector2f(RNG::randomFloat(-shakeStrength, shakeStrength), RNG::randomFloat(-shakeStrength, shakeStrength)));
        shakeStrength -= 0.99f * timeScale;
        shakeStrength = std::max(0.f, shakeStrength);
    }

}

void View::shake(const int& shakeStrength) {
    this->shakeStrength = shakeStrength;
}