#include "Collider.h"
#include <cmath>

Collider::~Collider() = default;

bool Collider::checkCollision(Collider& collider) {

    float deltaX = collider.getBounds().position.x + collider.getBounds().size.x / 2.f - (getBounds().position.x + getBounds().size.x / 2.f);
    distanceX = std::abs(deltaX) - (collider.getBounds().size.x / 2.f + getBounds().size.x / 2.f);

    if (distanceX < 0) {
        float deltaY = collider.getBounds().position.y + collider.getBounds().size.y / 2.f - (getBounds().position.y + getBounds().size.y / 2.f);
        distanceY = std::abs(deltaY) - (collider.getBounds().size.y / 2.f + getBounds().size.y / 2.f);
        if (distanceY < 0) {

            if (deltaX > 0 and deltaY > 0) {
                if (std::abs(deltaX) > std::abs(deltaY))
                    side = CollisionSide::Left;
                else
                    side = CollisionSide::Top;
            }
            else if (deltaX < 0 and deltaY > 0) {
                if (std::abs(deltaX) > std::abs(deltaY))
                    side = CollisionSide::Right;
                else
                    side = CollisionSide::Top;
            }
            else if (deltaX < 0 and deltaY < 0) {
                if (std::abs(deltaX) > std::abs(deltaY))
                    side = CollisionSide::Right;
                else
                    side = CollisionSide::Bottom;
            }
            else {
                if (std::abs(deltaX) > std::abs(deltaY))
                    side = CollisionSide::Left;
                else
                    side = CollisionSide::Bottom;
            }
            return true;

        }
    }
    return false;

}