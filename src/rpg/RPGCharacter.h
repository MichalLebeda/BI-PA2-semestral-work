//
// Created by michal on 3/19/20.
//

#ifndef SEMESTRAL_WORK_RPGCHARACTER_H
#define SEMESTRAL_WORK_RPGCHARACTER_H

/**
 * Representation of RPG character and his stats such as health, max health, defense, attack
 */
class RPGCharacter {
public:

    RPGCharacter() = default;

    virtual ~RPGCharacter() = default;

    /**
     *
     * @return Maximum health possible
     */
    int getMaxHealth() const;

    /**
     *
     * @return Current health amount
     */
    int getHealth() const;

    /**
     *
     * @return Defense points
     */
    int getDefense() const;

    /**
     *
     * @return Attack points
     */
    int getAttack() const;

    /**
     * Set health, cuts them of if > than maxHealth
     * @param health  HP to set
     */
    void setHealth(int health);

    /**
     *
     * @param defense Desired defense
     */
    void setDefense(int defense);

    /**
     *
     * @param attack Desired attack
     */
    void setAttack(int attack);

    /**
     *
     * @param maxHealth Desired maximum health
     */
    void setMaxHealth(int maxHealth);

    /**
     * Return whatever is character is alive or not
     * @return True if alive, false otherwise
     */
    bool alive();

    /**
     * Handle damage and update HP
     * @param damage Damage to handle
     */
    void handleDamage(int damage);

protected:

    int maxHealth;
    int health;
    int defense;
    int attack;
};


#endif //SEMESTRAL_WORK_RPGCHARACTER_H
