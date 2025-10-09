#include "RNG.h"
#include "../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics.hpp"

std::random_device RNG::device;

int RNG::randomInt(const int& min, const int& max) {
    return std::uniform_int_distribution(min, max)(device);
}

float RNG::randomFloatGaussian(const float& mean, const float& deviation) {
    return std::normal_distribution(mean, deviation)(device);
}

float RNG::randomFloat(const float& min, const float& max) {
    return std::uniform_real_distribution(min, max)(device);
}

bool RNG::percentChance(const int& percentChance) {
    return std::uniform_int_distribution(1, 100)(device) <= percentChance;
}