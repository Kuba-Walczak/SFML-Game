#pragma once
#include <SFML/Graphics.hpp>
#include <random>

struct RNG {

    static std::random_device device;

    static int randomInt(const int& min, const int& max);

    static float randomFloatGaussian(const float& mean, const float& deviation);

    static float randomFloat(const float& min, const float& max);

    static bool percentChance(const int& percentChance);

    template <typename T>
    const static sf::Texture& randomTexture(T& vec) {
    int randomIndex = randomInt(0, vec.size() - 1);
    return vec.at(randomIndex);
    }

};