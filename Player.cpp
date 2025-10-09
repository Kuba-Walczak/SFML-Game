#include "Player.h"
#include "Weapons/Weapon.h"

#include <cmath>
#include <algorithm>
#include <fmt/base.h>

Player::Player(const sf::Vector2f& position, const std::map<std::string, std::vector<sf::Texture>>& playerTexMap, const std::map<std::string, std::vector<sf::Texture>>& effectTexMap, std::vector<std::unique_ptr<Effect>>& effectVec) :
sprite(playerTexMap.at("Down").at(0)), compileButton(playerTexMap.at("CompileButton").at(0)), winButton(playerTexMap.at("WinButton").at(0)), tileCheck(sf::Vector2f(0, 0), playerTexMap.at("Empty1").at(0)), shadowSprite(playerTexMap.at("Shadow").at(0)), healthIcon(playerTexMap.at("HealthIcon").at(0)), staminaIcon(playerTexMap.at("StaminaIcon").at(0)), inventoryIcon(playerTexMap.at("InventoryIcon").at(0)), knowledgeIcon(playerTexMap.at("KnowledgeIcon").at(0)), healthBarBackground(playerTexMap.at("GenericBarBackground").at(0)), healthBar(playerTexMap.at("GenericBar").at(0)), healthBarOutline(playerTexMap.at("GenericBarOutline").at(0)), staminaBarBackground(playerTexMap.at("GenericBarBackground").at(0)), staminaBar(playerTexMap.at("GenericBar").at(0)), staminaBarOutline(playerTexMap.at("GenericBarOutline").at(0)), knowledgeBarBackground(playerTexMap.at("KnowledgeBarBackground").at(0)), knowledgeBar(playerTexMap.at("KnowledgeBar").at(0)), knowledgeLevelSprite(playerTexMap.at("Level").at(0)), unspentPoints(playerTexMap.at("UnspentPoints").at(0)), healthSprite(playerTexMap.at("Health").at(0)), staminaSprite(playerTexMap.at("Stamina").at(0)), slotSprite(playerTexMap.at("Slot").at(0)), playerTexMap(playerTexMap), effectTexMap(effectTexMap), effectVec(effectVec) {
    sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().size.x / 2, sprite.getGlobalBounds().size.y / 2));
    sprite.setPosition(sf::Vector2f(position.x + sprite.getOrigin().x, position.y + sprite.getOrigin().y));
    sprite.setScale(sf::Vector2f(.25f, .25f));
    shadowSprite.setOrigin(sf::Vector2f(shadowSprite.getGlobalBounds().size.x / 2, shadowSprite.getGlobalBounds().size.y / 2));
    compileButton.setOrigin(sf::Vector2f(compileButton.getGlobalBounds().size.x / 2, compileButton.getGlobalBounds().size.y / 2));
    winButton.setOrigin(sf::Vector2f(winButton.getGlobalBounds().size.x / 2, winButton.getGlobalBounds().size.y / 2));
    healthIcon.setOrigin(sf::Vector2f(healthIcon.getGlobalBounds().size.x / 2, healthIcon.getGlobalBounds().size.y / 2));
    staminaIcon.setOrigin(sf::Vector2f(staminaIcon.getGlobalBounds().size.x / 2, staminaIcon.getGlobalBounds().size.y / 2));
    inventoryIcon.setOrigin(sf::Vector2f(inventoryIcon.getGlobalBounds().size.x / 2, inventoryIcon.getGlobalBounds().size.y / 2));
    knowledgeIcon.setOrigin(sf::Vector2f(knowledgeIcon.getGlobalBounds().size.x / 2, knowledgeIcon.getGlobalBounds().size.y / 2));
    healthSprite.setOrigin(sf::Vector2f(healthSprite.getGlobalBounds().size.x / 2, healthSprite.getGlobalBounds().size.y / 2));
    healthBarBackground.setOrigin(sf::Vector2f(healthBarBackground.getGlobalBounds().size.x / 2, healthBarBackground.getGlobalBounds().size.y / 2));
    healthBar.setOrigin(sf::Vector2f(healthBar.getGlobalBounds().size.x / 2, healthBar.getGlobalBounds().size.y / 2));
    healthBarOutline.setOrigin(sf::Vector2f(healthBarOutline.getGlobalBounds().size.x / 2, healthBarOutline.getGlobalBounds().size.y / 2));
    staminaBarBackground.setOrigin(sf::Vector2f(staminaBarBackground.getGlobalBounds().size.x / 2, staminaBarBackground.getGlobalBounds().size.y / 2));
    staminaBar.setOrigin(sf::Vector2f(staminaBar.getGlobalBounds().size.x / 2, staminaBar.getGlobalBounds().size.y / 2));
    staminaBarOutline.setOrigin(sf::Vector2f(staminaBarOutline.getGlobalBounds().size.x / 2, staminaBarOutline.getGlobalBounds().size.y / 2));
    knowledgeBarBackground.setOrigin(sf::Vector2f(knowledgeBarBackground.getGlobalBounds().size.x / 2, knowledgeBarBackground.getGlobalBounds().size.y / 2));
    knowledgeBar.setOrigin(sf::Vector2f(knowledgeBar.getGlobalBounds().size.x / 2, knowledgeBar.getGlobalBounds().size.y / 2));
    knowledgeLevelSprite.setOrigin(sf::Vector2f(knowledgeLevelSprite.getGlobalBounds().size.x / 2, knowledgeLevelSprite.getGlobalBounds().size.y / 2));
    unspentPoints.setOrigin(sf::Vector2f(unspentPoints.getGlobalBounds().size.x / 2, unspentPoints.getGlobalBounds().size.y / 2));
    healthSprite.setOrigin(sf::Vector2f(healthSprite.getGlobalBounds().size.x / 2, healthSprite.getGlobalBounds().size.y / 2));
    staminaSprite.setOrigin(sf::Vector2f(staminaSprite.getGlobalBounds().size.x / 2, staminaSprite.getGlobalBounds().size.y / 2));
    slotSprite.setOrigin(sf::Vector2f(slotSprite.getGlobalBounds().size.x / 2, slotSprite.getGlobalBounds().size.y / 2));

    for (int i = 0; i < playerTexMap.at("Level").size(); ++i) {
        knowledgeLevels.emplace_back(playerTexMap.at("Level").at(i));
    }
    for (int i = 0; i < 3; ++i) {
        inventorySlots.emplace_back(playerTexMap.at("InventorySlotBackground").at(0));
        inventorySlots.back().setOrigin(sf::Vector2f(inventorySlots.back().getGlobalBounds().size.x / 2, inventorySlots.back().getGlobalBounds().size.y / 2));
    }
}

void Player::update(const float& timeScale, const sf::RenderWindow& window, const sf::View& view) {

    if (stamina <= staminaLevel) {
        stamina += timeScale * .002f;
        std::min(static_cast<float>(staminaLevel), stamina);
    }

    tileCheck.sprite.setPosition(view.getCenter());
    shadowSprite.setPosition(view.getCenter());

    inventorySlots.at(0).setPosition(sf::Vector2f(view.getCenter().x - 840, view.getCenter().y + 420));
    inventorySlots.at(1).setPosition(sf::Vector2f(view.getCenter().x - 690, view.getCenter().y + 420));
    inventorySlots.at(2).setPosition(sf::Vector2f(view.getCenter().x - 540, view.getCenter().y + 420));

    for (auto& slot : inventorySlots)
        slot.setScale(sf::Vector2f(.5f, .5f));

    inventorySlots.at(equippedSlot).setScale(sf::Vector2f(.625f, .625f));

    for (int i = 0; i < inventory.size(); ++i) {
        inventory.at(i)->sprite.setPosition(inventorySlots.at(i).getPosition());
        if (i == equippedSlot)
            inventory.at(i)->sprite.setScale(sf::Vector2f(.6f, .6f));
        else
            inventory.at(i)->sprite.setScale(sf::Vector2f(.4f, .4f));
        inventory.at(i)->update(timeScale, *this);
    }

    healthIcon.setPosition(sf::Vector2f(view.getCenter().x - 900, view.getCenter().y - 450));
    staminaIcon.setPosition(sf::Vector2f(view.getCenter().x - 900, view.getCenter().y - 300));
    inventoryIcon.setPosition(sf::Vector2f(view.getCenter().x - 690, view.getCenter().y + 420));
    knowledgeIcon.setPosition(sf::Vector2f(view.getCenter().x - 690, view.getCenter().y + 240));

    auto healthBarOffset = 180 * (1 - health);

    healthBarBackground.setPosition(sf::Vector2f(view.getCenter().x - 960 + healthBarPosition, view.getCenter().y - 450));
    healthBar.setPosition(sf::Vector2f(view.getCenter().x - 960 - healthBarOffset, view.getCenter().y - 450));
    healthBarOutline.setPosition(sf::Vector2f(view.getCenter().x - 960 + healthBarPosition, view.getCenter().y - 450));

    auto staminaBarOffset = 180 * (1 - stamina);

    staminaBarBackground.setPosition(sf::Vector2f(view.getCenter().x - 960 + staminaBarPosition, view.getCenter().y - 300));
    staminaBar.setPosition(sf::Vector2f(view.getCenter().x - 960 - staminaBarOffset, view.getCenter().y - 300));
    staminaBarOutline.setPosition(sf::Vector2f(view.getCenter().x - 960 + staminaBarPosition, view.getCenter().y - 300));

    knowledgeBarBackground.setPosition(sf::Vector2f(view.getCenter().x - 640, view.getCenter().y + 240));
    knowledgeBar.setPosition(sf::Vector2f(view.getCenter().x - 640, view.getCenter().y + 240));
    knowledgeBar.setTextureRect(sf::IntRect(sf::Vector2(0, 0), sf::Vector2(static_cast<int>(knowledge * 380), 60)));
    knowledgeLevelSprite.setPosition(sf::Vector2f(view.getCenter().x - 870, view.getCenter().y + 152));

    if ((healthLevel >= 3 and staminaLevel >= 3 and inventoryCapacity >= 3) or upgradePoints == 0) {
        unspentPoints.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y - 1000));
        healthSprite.setPosition(sf::Vector2f(view.getCenter().x - 120, view.getCenter().y - 1000));
        staminaSprite.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y - 1000));
        slotSprite.setPosition(sf::Vector2f(view.getCenter().x + 120, view.getCenter().y - 1000));
    }
    else {
        unspentPoints.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y - 420));
        healthSprite.setPosition(sf::Vector2f(view.getCenter().x - 120, view.getCenter().y - 400));
        staminaSprite.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y - 400));
        slotSprite.setPosition(sf::Vector2f(view.getCenter().x + 120, view.getCenter().y - 400));
    }

    compileButton.setPosition(sf::Vector2f(view.getCenter().x + 760, view.getCenter().y + 340));
    winButton.setPosition(sf::Vector2f(view.getCenter().x + 760, view.getCenter().y + 340));

    animationSpeed += timeScale * .25f / (knowledgeLevel / 4.f + .5f);
    if (animationSpeed >= 1) {
        animationSpeed -= 1;
        if (movingUp && !movingLeft && !movingRight && !movingDown) {
            currentTexVec = playerTexMap.at("Up");
            sprite.setTexture(playerTexMap.at("Up").at(animationFrame++));
        }
        else if (movingUp && movingRight && !movingLeft && !movingDown) {
            currentTexVec = playerTexMap.at("UpRight");
            sprite.setTexture(playerTexMap.at("UpRight").at(animationFrame++));
        }
        else if (movingRight && !movingUp && !movingDown && !movingLeft) {
            currentTexVec = playerTexMap.at("Right");
            sprite.setTexture(playerTexMap.at("Right").at(animationFrame++));
        }
        else if (movingRight && movingDown && !movingUp && !movingLeft) {
            currentTexVec = playerTexMap.at("DownRight");
            sprite.setTexture(playerTexMap.at("DownRight").at(animationFrame++));
        }
        else if (movingDown && !movingLeft && !movingRight && !movingUp) {
            currentTexVec = playerTexMap.at("Down");
            sprite.setTexture(playerTexMap.at("Down").at(animationFrame++));
        }
        else if (movingDown && movingLeft && !movingRight && !movingUp) {
            currentTexVec = playerTexMap.at("DownLeft");
            sprite.setTexture(playerTexMap.at("DownLeft").at(animationFrame++));
        }
        else if (movingLeft && !movingUp && !movingDown && !movingRight) {
            currentTexVec = playerTexMap.at("Left");
            sprite.setTexture(playerTexMap.at("Left").at(animationFrame++));
        }
        else if (movingUp && movingLeft && !movingRight && !movingDown) {
            currentTexVec = playerTexMap.at("UpLeft");
            sprite.setTexture(playerTexMap.at("UpLeft").at(animationFrame++));
        }
        else if (movingLeft && movingRight && movingUp) {
            currentTexVec = playerTexMap.at("Up");
            sprite.setTexture(playerTexMap.at("Up").at(animationFrame++));
        }
        else if (movingLeft && movingRight) {
            currentTexVec = playerTexMap.at("Down");
            sprite.setTexture(playerTexMap.at("Down").at(animationFrame++));
        }
        else if (!movingUp && !movingDown && !movingLeft && !movingRight) {
            currentTexVec = playerTexMap.at("Down");
            sprite.setTexture(playerTexMap.at("Down").at(animationFrame++));
        }
        else {
            sprite.setTexture(currentTexVec.at(animationFrame++));
        }

        if (animationFrame >= playerTexMap.at("Down").size())
            animationFrame = 0;
    }


    if (movingLeft)
        velocity.x -= .5f * timeScale;
    if (movingRight)
        velocity.x += .5f * timeScale;
    if (movingUp)
        velocity.y -= .5f * timeScale;
    if (movingDown)
        velocity.y += .5f * timeScale;
    if (shooting and equippedSlot < inventory.size()) {
        inventory.at(equippedSlot)->use(timeScale, *this, window, view);
    }

    if (std::abs(velocity.x) > .01f)
        velocity.x *= std::pow(.92f, timeScale);
    else
        velocity.x = 0;

    if (std::abs(velocity.y) > .01f)
        velocity.y *= std::pow(.92f, timeScale);
    else
        velocity.y = 0;

    sprite.move(velocity * timeScale);

}

void Player::pickUp(std::unique_ptr<Weapon>&& weapon) {
    inventory.push_back(std::move(weapon));
}

void Player::drop(std::vector<std::unique_ptr<Weapon>>& weaponVec) {
    inventory.at(equippedSlot)->pickedUp = false;
    inventory.at(equippedSlot)->sprite.setScale(sf::Vector2f(1, 1));
    weaponVec.push_back(std::move(inventory.at(equippedSlot)));
    weaponVec.back()->sprite.setPosition(sprite.getPosition());
    inventory.erase(inventory.begin() + equippedSlot);
}

void Player::inventorySlotForward() {
    if (equippedSlot >= inventoryCapacity - 1)
        equippedSlot = 0;
    else
        ++equippedSlot;

}

void Player::inventorySlotBackward() {
    if (equippedSlot <= 0)
        equippedSlot = inventoryCapacity - 1;
    else
        --equippedSlot;
}

void Player::dash(const int& strength) {
    if (dashing == false) {
        velocity.x *= strength;
        velocity.y *= strength;
    }
    dashing = true;
}

void Player::increaseHealthLevel() {
    upgradePoints -= 1;
    healthLevel += 1;
    healthBarPosition += 180;
}

void Player::setHealthLevel(const int& level) {
    healthLevel = level;
    healthBarPosition = 180 * (level - 1);
}

void Player::increaseHealth(const float& amount) {
    health += amount;
    health = std::min(health, static_cast<float>(healthLevel));
}

void Player::increaseStaminaLevel() {
    upgradePoints -= 1;
    staminaLevel += 1;
    staminaBarPosition += 180;
}

void Player::setStaminaLevel(const int& level) {
    staminaLevel = level;
    staminaBarPosition = 180 * (level - 1);
}

void Player::increaseKnowledge(const float& amount) {
    knowledge += amount;
    if (knowledgeLevel >= 10)
        knowledge = std::min(knowledge, 1.f);
    if (knowledge >= 1 and knowledgeLevel <= 9) {
        knowledge -= 1;
        knowledgeLevel += 1;
        upgradePoints += 1;
        knowledgeLevelSprite.setTexture(knowledgeLevels.at(knowledgeLevel - 1));
        sprite.scale(sf::Vector2f(1.1f, 1.1f));
        shadowSprite.scale(sf::Vector2f(1.1f, 1.1f));
        effectVec.emplace_back(std::make_unique<Effect>(Effect(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 50), effectTexMap.at("LevelUp"))));
    }
}

void Player::setKnowledgeLevel(const int& level) {
    knowledgeLevel = level;
    knowledgeLevelSprite.setTexture(knowledgeLevels.at(knowledgeLevel - 1));
    for (int i = 1; i < knowledgeLevel; ++i) {
        sprite.scale(sf::Vector2f(1.1f, 1.1f));
        shadowSprite.scale(sf::Vector2f(1.1f, 1.1f));
    }
}

sf::FloatRect Player::getBounds() {
    sprite.scale(sf::Vector2f(0.4f, 0.4f));
    auto tempBounds = sprite.getGlobalBounds();
    sprite.scale(sf::Vector2f(2.5f, 2.5f));
    return tempBounds;
}