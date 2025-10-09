#pragma once
#include "View.h"

#include <map>
#include <SFML/Graphics.hpp>

struct Menu {

    Menu(const std::map<std::string, std::vector<sf::Texture>>& menuTexMap);

    sf::Sprite background;
    sf::Sprite mainBackground;
    sf::Sprite play;
    sf::Sprite load;
    sf::Sprite pauseOverlay;
    sf::Sprite pauseBackground;
    sf::Sprite save;
    sf::Sprite quit;
    std::vector<sf::Sprite*> mainMenuVec;
    std::vector<sf::Sprite*> pauseMenuVec;
    bool mainMenu = true;
    bool pauseMenu = false;
    bool loadOverride = false;

    void update(const View& view);

};