//
// Created by michal on 3/21/20.
//

#ifndef SEMESTRAL_WORK_RPGITEM_H
#define SEMESTRAL_WORK_RPGITEM_H

#include <string>
#include <SDL2/SDL_pixels.h>

using namespace std;

/**
 * Basic RPG representation of item
 */
class RPGItem {
public:
    /**
     * @brief Create instance of the  item with given index
     * @param index Item identifier
     * @return Instance of the item with index
     */
    static RPGItem *createItem(int index);

    /**
     * enum representing possible item types
     */
    enum Type {
        WEAPON, SHIRT, PANTS, CONSUMABLE
    };

    ~RPGItem();

    /**
     *
     * @return Id of item
     */
    int getId() const;

    /**
     *
     * @return Amount of HP to be added to maximum HP
     */
    int getMaxHealthEffect() const;

    /**
     *
     * @return Amount of HP to be added to current HP
     */
    int getHealthEffect() const;

    /**
     *
     * @return Amount to be added to current defense
     */
    int getDefenseEffect() const;

    /**
     *
     * @return Amount to be added to current attack
     */
    int getAttackEffect() const;

    /**
     *
     * @return Item type id
     */
    Type getType() const;

    /**
     *
     * @return Name of the item
     */
    const string &getName() const;

    /**
     *
     * @return Color tint for item when rendered
     */
    const SDL_Color &getColorTint() const;

    /**
     *
     * @return Index of region graphically representing item
     */
    const int &getRegionIndex() const;

    /**
     * @brief Sets color tint to desired color
     * @param colorTint Desired color tint color
     */
    void setColorTint(const SDL_Color &colorTint);

    /**
     *
     * @return Whatever item is equiped
     */
    bool isEquipped() const;

    /**
     * @brief Set whatever item is equiped
     * @param equipped
     */
    void setEquipped(bool equipped);

    /**
     * @brief Get whatever item is temporal eg. item representing that player is wearing nothing
     * @return True if item is temporal, false otherwise
     */
    bool isTemporal();

private:
    RPGItem(const int &id, const int &regionIndex, const string &name, const Type &category);

    int id;

    Type type;
    string name;

    int regionIndex;
    SDL_Color colorTint;

    bool equipped = false;
    bool temporal = false;
    int maxHealthEffect = 0;
    int healthEffect = 0;
    int defenseEffect = 0;
    int attackEffect = 0;
};


#endif //SEMESTRAL_WORK_RPGITEM_H
