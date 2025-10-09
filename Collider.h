#pragma once
#include <SFML/Graphics.hpp>

enum class CollisionSide {None = 0, Top = 1, Right = 2, Bottom = 3, Left = 4};

struct Collider {

    virtual ~Collider();

    CollisionSide side = CollisionSide::None;
    float distanceX = 0;
    float distanceY = 0;

    virtual sf::FloatRect getBounds() = 0;

    bool checkCollision(Collider& collider);

};