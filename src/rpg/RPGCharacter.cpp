//
// Created by michal on 3/19/20.
//

#include "RPGCharacter.h"
#include <algorithm>
#include <iostream>

int RPGCharacter::getMaxHealth() const {
    return maxHealth;
}

void RPGCharacter::setMaxHealth(int maxHealth) {
    RPGCharacter::maxHealth = maxHealth;
}

int RPGCharacter::getHealth() const {
    if (health < 0) {
        return 0;
    }

    return health;
}

int RPGCharacter::getDefense() const {
    if (defense < 0) {
        return 0;
    }
    return defense;
}

int RPGCharacter::getAttack() const {
    if (attack < 0) {
        return 0;
    }
    return attack;
}

void RPGCharacter::setHealth(int health) {
    RPGCharacter::health = health;

    if (RPGCharacter::health > maxHealth) {
        RPGCharacter::health = maxHealth;
    }
}

void RPGCharacter::setDefense(int defense) {
    RPGCharacter::defense = defense;
}

void RPGCharacter::setAttack(int attack) {
    RPGCharacter::attack = attack;
}

void RPGCharacter::handleDamage(int damage) {
    health -= std::max(0, damage / defense);

    if (health < 0) {
        health = 0;
    }

    std::cout << "damage: " << damage << std::endl;
    std::cout << "health: " << health << std::endl;
    std::cout << "defense: " << defense << std::endl << std::endl;
}

bool RPGCharacter::alive() {
    return health > 0;
}
