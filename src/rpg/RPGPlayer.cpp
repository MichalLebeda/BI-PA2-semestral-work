//
// Created by michal on 3/21/20.
//

#include "RPGPlayer.h"
#include <fstream>

RPGPlayer::RPGPlayer() {
    inventory = new RPGInventory();
}

RPGPlayer::~RPGPlayer() {
    delete weapon;
    delete shirt;
    delete pants;
    delete inventory;
}

void RPGPlayer::equip(RPGItem *item) {
    cout << "equiping: " << item->getName() << endl;
    switch (item->getType()) {
        case RPGItem::WEAPON:
            unapply(weapon);
            weapon = item;
            break;
        case RPGItem::SHIRT:
            unapply(shirt);
            shirt = item;
            break;
        case RPGItem::PANTS:
            unapply(pants);
            pants = item;
            break;
        default:
            cerr << "Cannot equip rpgItem of type: " << item->getType() << endl;
    }

    apply(item);
}

RPGItem *RPGPlayer::getWeapon() const {
    return weapon;
}

RPGItem *RPGPlayer::getShirt() const {
    return shirt;
}

RPGItem *RPGPlayer::getPants() const {
    return pants;
}

RPGInventory *RPGPlayer::getInventory() const {
    return inventory;
}

void RPGPlayer::apply(RPGItem *item) {
    item->setEquipped(true);
    setMaxHealth(getMaxHealth() + item->getMaxHealthEffect());
    setHealth(getHealth() + item->getHealthEffect());
    setDefense(getDefense() + item->getDefenseEffect());
    setAttack(getAttack() + item->getAttackEffect());
}

void RPGPlayer::unapply(RPGItem *item) {
    if (item == nullptr) {
        return;
    }

    item->setEquipped(false);
    setMaxHealth(getMaxHealth() - item->getMaxHealthEffect());
    setHealth(getHealth() - item->getHealthEffect());
    setDefense(getDefense() - item->getDefenseEffect());
    setAttack(getAttack() - item->getAttackEffect());
}

void RPGPlayer::serialize(ostream &os) const {
    os << levelIndex << endl;
    os << storedWorldX << ' ';
    os << storedWorldY << endl;
    os << health << ' ' << maxHealth << ' ' << defense << ' ' << attack << ' ' << killedEnemyCount << endl;
    os << weapon->getId() << ' ';
    os << shirt->getId() << ' ';
    os << pants->getId() << endl;
    os << win;

    inventory->serialize(os);
}

void RPGPlayer::deserialize(istream &is) {
    fromFile = true;

    is >> levelIndex;

    is >> storedWorldX;
    is >> storedWorldY;

    is >> health;
    is >> maxHealth;
    is >> defense;
    is >> attack;
    is >> killedEnemyCount;

    int index;
    is >> index;
    weapon = (RPGItem::createItem(index));
    is >> index;
    shirt = (RPGItem::createItem(index));
    is >> index;
    pants = (RPGItem::createItem(index));

    is >> win;

    weapon->setEquipped(true);
    shirt->setEquipped(true);
    pants->setEquipped(true);

    inventory->deserialize(is);

    if (is.bad()) {
        throw runtime_error("error reading Player file");
    }
}

void RPGPlayer::setWorldPosition(int x, int y) {
    this->storedWorldX = x;
    this->storedWorldY = y;
}

bool RPGPlayer::isFromFile() {
    return fromFile;
}

int RPGPlayer::getStoredWorldX() const {
    return storedWorldX;
}

int RPGPlayer::getStoredWorldY() const {
    return storedWorldY;
}

int RPGPlayer::getLevelIndex() const {
    return levelIndex;
}

void RPGPlayer::setLevelIndex(int levelIndex) {
    RPGPlayer::levelIndex = levelIndex;
}

bool RPGPlayer::hasWin() const {
    return win;
}

void RPGPlayer::setWin(bool hasWin) {
    this->win = hasWin;
}

void RPGPlayer::incrementKilledEnemyCount() {
    killedEnemyCount++;
}

int RPGPlayer::getKilledEnemyCount() const {
    return killedEnemyCount;
}
