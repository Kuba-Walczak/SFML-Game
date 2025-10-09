#include "SyntaxError.h"
#include "../../Utility/RNG.h"

#include <cmath>

SyntaxError::SyntaxError(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, const float& activationDistance, CollisionSide requiredSide, const int& tile) :
Enemy(position, enemyTexMap, effectTexMap, effectVec, tile), activationDistance(activationDistance), requiredSide(requiredSide) {
    auto randomScale = RNG::randomFloat(0.5f, 1);
    sprite.setScale(sf::Vector2f(randomScale, randomScale));
    switch (requiredSide) {
        case CollisionSide::Top: {
            sprite.rotate(-sf::Angle(sf::radians(std::numbers::pi / 2)));
        } break;
        case CollisionSide::Right: {
        } break;
        case CollisionSide::Bottom: {
            sprite.rotate(sf::Angle(sf::radians(std::numbers::pi / 2)));
        } break;
        case CollisionSide::Left: {
            sprite.rotate(sf::Angle(sf::radians(std::numbers::pi)));
        } break;
    }
}

SyntaxError::SyntaxError(const sf::Vector2f& position, const std::map<std::string,std::vector<sf::Texture>>& enemyTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec, const float& activationDistance, CollisionSide requiredSide, const float& scale, const int& tile) :
Enemy(position, enemyTexMap, effectTexMap, effectVec, tile), activationDistance(activationDistance), requiredSide(requiredSide) {
    sprite.setScale(sf::Vector2f(scale, scale));
    switch (requiredSide) {
        case CollisionSide::Top: {
            sprite.rotate(-sf::Angle(sf::radians(std::numbers::pi / 2)));
        } break;
        case CollisionSide::Right: {
        } break;
        case CollisionSide::Bottom: {
            sprite.rotate(sf::Angle(sf::radians(std::numbers::pi / 2)));
        } break;
        case CollisionSide::Left: {
            sprite.rotate(sf::Angle(sf::radians(std::numbers::pi)));
        } break;
    }
}

float SyntaxError::getDamage() {
    return damage;
}

void SyntaxError::update(const float& timeScale, Player& player) {

    if (!compile) {

        if (sleepLength > 0) {
            sprite.setTexture(enemyTexMap.at("SyntaxErrorSleep").at(0));
            sleepLength -= timeScale * .1f;
            std::max(0.f, sleepLength);
        }
        else {
            animationSpeed += timeScale * .5f;
            while (animationSpeed >= 1) {
                animationSpeed -= 1;
                sprite.setTexture(enemyTexMap.at("SyntaxErrorIdle").at(animationFrame++));
                if (animationFrame >= enemyTexMap.at("SyntaxErrorIdle").size()) {
                    animationFrame = 0;
                }
            }

            timeThreshold += timeScale;
            while (timeThreshold >= 1) {
                timeThreshold -= 1;
                for (int i = 0; i < RNG::randomInt(0, 50); ++i)
                    effectVec.emplace_back(std::make_unique<Effect>(Effect(sprite.getPosition(), effectTexMap.at("Glitch"), .1f, .4f, sprite.getScale().x * 100, 10)));
            }

            auto deltaX = player.sprite.getPosition().x - this->sprite.getPosition().x;
            auto deltaY = player.sprite.getPosition().y - this->sprite.getPosition().y;
            if (std::hypot(deltaX, deltaY) < activationDistance) {
                auto angle = std::atan2(deltaX, deltaY);
                auto directionX = std::sin(angle);
                auto directionY = std::cos(angle);
                velocity = sf::Vector2f(directionX, directionY) * timeScale * 2.f;
                sprite.move(velocity);
            }
        }

    }
    else {
    animationSpeed += timeScale;
        while (animationSpeed >= 1) {
            animationSpeed -= 1;
            sprite.setTexture(enemyTexMap.at("SyntaxErrorCompile").at(animationFrame++));
            if (animationFrame >= enemyTexMap.at("SyntaxErrorCompile").size()) {
                effectVec.emplace_back(std::make_unique<Effect>(Effect(sprite.getPosition(), effectTexMap.at("Compiled"))));
                alive = false;
                player.increaseKnowledge(.25f);
                effectVec.emplace_back(std::make_unique<Effect>(Effect(player.sprite.getPosition(), effectTexMap.at("Knowledge"))));
                break;
            }
        }
    }

}

sf::FloatRect SyntaxError::getBounds() {
    sprite.scale(sf::Vector2f(0.5f, 0.5f));
    auto tempBounds = sprite.getGlobalBounds();
    sprite.scale(sf::Vector2f(2, 2));
    return tempBounds;
}