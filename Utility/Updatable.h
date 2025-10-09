#pragma once

struct Player;

struct Updatable {

    virtual ~Updatable();

    virtual void update(const float& timeScale) = 0;

    virtual void update(const float& timeScale, Player& player) = 0;

};