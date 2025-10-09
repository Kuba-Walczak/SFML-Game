#pragma once
#include "Collider.h"
#include "Effect.h"
#include "Collision.h"
#include "Enemies/Enemy.h"

#include <SFML/Graphics.hpp>
#include <map>

struct Weapon;
struct Enemy;

struct Player : Collider {

    Player(const sf::Vector2f& position, const std::map<std::string, std::vector<sf::Texture>>& playerTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec);

    sf::Sprite sprite;
    std::vector<sf::Texture> currentTexVec;
    sf::Sprite shadowSprite;
    const std::map<std::string, std::vector<sf::Texture>>& playerTexMap;
    const std::map<std::string, std::vector<sf::Texture>>& effectTexMap;
    std::vector<std::unique_ptr<Effect>>& effectVec;
    sf::Vector2f velocity;

    sf::Sprite compileButton;
    sf::Sprite winButton;
    Collision tileCheck;
    int tile;

    sf::Sprite healthIcon;
    sf::Sprite staminaIcon;
    sf::Sprite inventoryIcon;
    sf::Sprite knowledgeIcon;

    int healthBarPosition;
    sf::Sprite healthBarBackground;
    sf::Sprite healthBar;
    sf::Sprite healthBarOutline;

    int staminaBarPosition;
    sf::Sprite staminaBarBackground;
    sf::Sprite staminaBar;
    sf::Sprite staminaBarOutline;

    sf::Sprite knowledgeBarBackground;
    sf::Sprite knowledgeBar;
    sf::Sprite knowledgeLevelSprite;
    sf::Sprite unspentPoints;
    sf::Sprite healthSprite;
    sf::Sprite staminaSprite;
    sf::Sprite slotSprite;
    std::vector<sf::Texture> knowledgeLevels;

    std::vector<std::unique_ptr<Weapon>> inventory;
    std::vector<sf::Sprite> inventorySlots;

    bool movingLeft = false;
    bool movingRight = false;
    bool movingUp = false;
    bool movingDown = false;
    bool dashing = false;
    bool shooting = false;

    float health = 1;
    int healthLevel = 1;

    int equippedSlot = 0;
    int inventoryCapacity = 1;

    float stamina = 1;
    int staminaLevel = 1;

    float knowledge = 0;
    int knowledgeLevel = 1;
    int upgradePoints = 0;

    bool emptyGround = true;

    float animationSpeed = 0;
    int animationFrame = 0;

    bool showFPS = false;
    bool performanceMode = false;
    
    void update(const float& timeScale, const sf::RenderWindow& window, const sf::View& view);

    void pickUp(std::unique_ptr<Weapon>&& weapon);

    void drop(std::vector<std::unique_ptr<Weapon>>& weapon);

    void inventorySlotForward();

    void inventorySlotBackward();

    void dash(const int& strength);

    void increaseHealthLevel();

    void setHealthLevel(const int& level);

    void increaseHealth(const float& amount);

    void increaseStaminaLevel();

    void setStaminaLevel(const int& level);

    void increaseKnowledge(const float& amount);

    void setKnowledgeLevel(const int& level);

    sf::FloatRect getBounds() override;

};
