#include "Menu.h"

Menu::Menu(const std::map<std::string, std::vector<sf::Texture>>& menuTexMap) :
background(menuTexMap.at("Background").at(0)), pauseOverlay(menuTexMap.at("PauseOverlay").at(0)), mainBackground(menuTexMap.at("MainBackground").at(0)), pauseBackground(menuTexMap.at("PauseBackground").at(0)), play(menuTexMap.at("Play").at(0)), save(menuTexMap.at("Save").at(0)), load(menuTexMap.at("Load").at(0)), quit(menuTexMap.at("Quit").at(0)) {
    background.setOrigin(sf::Vector2f(background.getGlobalBounds().size.x / 2, background.getGlobalBounds().size.y / 2));
    pauseOverlay.setOrigin(sf::Vector2f(pauseOverlay.getGlobalBounds().size.x / 2, pauseOverlay.getGlobalBounds().size.y / 2));
    mainBackground.setOrigin(sf::Vector2f(mainBackground.getGlobalBounds().size.x / 2, mainBackground.getGlobalBounds().size.y / 2));
    pauseBackground.setOrigin(sf::Vector2f(pauseBackground.getGlobalBounds().size.x / 2, pauseBackground.getGlobalBounds().size.y / 2));
    play.setOrigin(sf::Vector2f(play.getGlobalBounds().size.x / 2, play.getGlobalBounds().size.y / 2));
    save.setOrigin(sf::Vector2f(save.getGlobalBounds().size.x / 2, save.getGlobalBounds().size.y / 2));
    load.setOrigin(sf::Vector2f(load.getGlobalBounds().size.x / 2, load.getGlobalBounds().size.y / 2));
    quit.setOrigin(sf::Vector2f(quit.getGlobalBounds().size.x / 2, quit.getGlobalBounds().size.y / 2));

    mainMenuVec.push_back(&background);
    mainMenuVec.push_back(&mainBackground);
    mainMenuVec.push_back(&play);
    mainMenuVec.push_back(&load);
    mainMenuVec.push_back(&quit);

    pauseMenuVec.push_back(&pauseOverlay);
    pauseMenuVec.push_back(&pauseBackground);
    pauseMenuVec.push_back(&save);
    pauseMenuVec.push_back(&load);
    pauseMenuVec.push_back(&quit);
}

void Menu::update(const View& view) {
    pauseOverlay.setPosition(view.view.getCenter());
    background.setPosition(view.view.getCenter());
    mainBackground.setPosition(view.view.getCenter());
    pauseBackground.setPosition(view.view.getCenter());
    play.setPosition(sf::Vector2f(view.view.getCenter().x, view.view.getCenter().y - 150));
    save.setPosition(sf::Vector2f(view.view.getCenter().x, view.view.getCenter().y - 150));
    load.setPosition(view.view.getCenter());
    quit.setPosition(sf::Vector2f(view.view.getCenter().x, view.view.getCenter().y + 150));
}