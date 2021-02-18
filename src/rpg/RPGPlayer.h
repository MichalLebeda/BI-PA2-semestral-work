//
// Created by michal on 3/21/20.
//

#ifndef SEMESTRAL_WORK_RPGPLAYER_H
#define SEMESTRAL_WORK_RPGPLAYER_H


#include "RPGCharacter.h"
#include "RPGItem.h"
#include "RPGInventory.h"
#include <iostream>

using namespace std;

/**
 * Basic RPG representation of player's stats
 */
class RPGPlayer : public RPGCharacter, public Serializable {
public:
    RPGPlayer();

    ~RPGPlayer();

    /**
     * @brief Equip desired item
     * @param item  Item to equip
     */
    void equip(RPGItem *item);

    /**
     * @brief Apply effect of the item e.g. raise stats or heal
     * @param item  Item to apply
     */
    void apply(RPGItem *item);

    /**
     *
     * @return Equiped Weapon
     */
    RPGItem *getWeapon() const;

    /**
     *
     * @return Equiped shirt
     */
    RPGItem *getShirt() const;

    /**
     *
     * @return Equiped pants
     */
    RPGItem *getPants() const;

    /**
     * @brief Get inventory with one use items
     * @return Inventory
     */
    RPGInventory *getInventory() const;

    void serialize(std::ostream &os) const override;

    void deserialize(std::istream &is) override;

    /**
     * @brief Set position for further serialization
     * @param x X coordinate in game units
     * @param y Y coordinate in game units
     */
    void setWorldPosition(int x, int y);

    /**
     * @brief Return whatever was this object loaded or created (new game)
     * @return True if loaded from file false if not
     */
    bool isFromFile();

    /**
     * @brief Get last x coordinate loaded from file
     * @return X coordinate in game units
     */
    int getStoredWorldX() const;

    /**
     * @brief Get last Y coordinate loaded from file
     * @return Y coordinate in game units
     */
    int getStoredWorldY() const;

    /**
     * @brief Get index of last level player has been to
     * @return Index of last level
     */
    int getLevelIndex() const;

    /**
     * @brief Set index of last level player has been to
     */
    void setLevelIndex(int levelIndex);

    /**
     * @brief Return whatever player has already hasWin the game
     * @return True if player hasWin the game false otherwise
     */
    bool hasWin() const;

    /**
     * @brief Set if player has win the game
     * @param hasWin True if player has win, false othervise
     */
    void setWin(bool hasWin);

    /**
     * @brief increments count of killed enemies
     */
    void incrementKilledEnemyCount();

    /**
     * @brief return killed enemy count
     * @return number representing count of enemies killed by player
     */
    int getKilledEnemyCount() const;

private:

    /**
     * @brief Unapply effect of the item e.g. unequip or remove temporal effect
     * @param item  Item to unapply
     */
    void unapply(RPGItem *item);

    bool fromFile = false;
    bool win = false;
    RPGItem *weapon = nullptr;
    RPGItem *shirt = nullptr;
    RPGItem *pants = nullptr;
    RPGInventory *inventory;
    int killedEnemyCount = 0;
    int storedWorldX, storedWorldY;
    int levelIndex = 0;
};


#endif //SEMESTRAL_WORK_RPGPLAYER_H
