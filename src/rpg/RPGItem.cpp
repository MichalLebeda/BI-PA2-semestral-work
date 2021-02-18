//
// Created by michal on 3/21/20.
//

#include "RPGItem.h"
#include <iostream>

RPGItem *RPGItem::createItem(int index) {
    SDL_Color clothColor{223, 224, 232, 255};

    SDL_Color clothDarkerColor{194, 201, 183, 255};

    SDL_Color leatherColor{171, 81, 48, 255};

    SDL_Color leatherDarkerColor{125, 56, 51, 255};

    SDL_Color steelColor{104, 111, 153, 255};

    SDL_Color steelDarkerColor{64, 73, 115, 255};

    switch (index) {
        case 0: {
            auto item = new RPGItem(index, 0, "Klacek", WEAPON);
            item->attackEffect = 1;
            return item;
        }
        case 1: {
            auto item = new RPGItem(index, 1, "Železný meč", WEAPON);
            item->attackEffect = 5;
            return item;
        }
        case 2: {
            auto item = new RPGItem(index, 2, "Ocelový meč", WEAPON);
            item->attackEffect = 10;
            return item;
        }
        case 3: {
            auto item = new RPGItem(index, 3, "Meč zabiják", WEAPON);
            item->attackEffect = 40;
            return item;
        }
        case 4: {
            auto item = new RPGItem(index, 4, "Plátěné triko", SHIRT);
            item->setColorTint(clothColor);
            item->defenseEffect = 1;
            return item;
        }
        case 5: {
            auto item = new RPGItem(index, 4, "Kožené triko", SHIRT);
            item->maxHealthEffect = 10;
            item->healthEffect = 10;
            item->defenseEffect = 2;
            item->setColorTint(leatherColor);
            return item;
        }
        case 6: {
            auto item = new RPGItem(index, 4, "Kroužkové brnění", SHIRT);
            item->maxHealthEffect = 20;
            item->healthEffect = 20;
            item->defenseEffect = 3;
            item->attackEffect = -5;
            item->setColorTint(steelColor);
            return item;
        }
        case 7: {
            auto item = new RPGItem(index, 5, "Plátěné kalhoty", PANTS);
            item->setColorTint(clothDarkerColor);
            return item;
        }
        case 8: {
            auto item = new RPGItem(index, 5, "Kožené kalhoty", PANTS);
            item->defenseEffect = 2;
            item->setColorTint(leatherDarkerColor);
            return item;
        }
        case 9: {
            auto item = new RPGItem(index, 5, "Ocelové kalhoty", PANTS);
            item->defenseEffect = 3;
            item->setColorTint(steelDarkerColor);
            return item;
        }
        case 10: {
            auto item = new RPGItem(index, 6, "Jedovatá houba", CONSUMABLE);
            item->healthEffect = -30;
            return item;
        }
        case 11: {
            auto item = new RPGItem(index, 7, "Chutná houba", CONSUMABLE);
            item->healthEffect = 30;
            return item;
        }
        case 12: {
            auto item = new RPGItem(index, 4, "Modré tričko", SHIRT);
            item->defenseEffect = 1;
            item->setColorTint({100, 140, 220, 255});
            return item;
        }
        case 13: {
            auto item = new RPGItem(index, 4, "Fialové tričko", SHIRT);
            item->defenseEffect = 1;
            item->setColorTint({80, 30, 220, 255});
            return item;
        }
        case 14: {
            auto item = new RPGItem(index, 4, "Brčálové tričko", SHIRT);
            item->defenseEffect = 1;
            item->setColorTint({80, 255, 40, 255});
            return item;
        }
        case 15: {
            auto item = new RPGItem(index, 4, "Růžové tričko", SHIRT);
            item->defenseEffect = 1;
            item->setColorTint({255, 140, 190, 255});
            return item;
        }
        case 16: {
            auto item = new RPGItem(index, 4, "Červené tričko", SHIRT);
            item->defenseEffect = 1;
            item->setColorTint({200, 40, 40, 255});
            return item;
        }
        case 17: {
            auto item = new RPGItem(index, 4, "Oranžové tričko", SHIRT);
            item->defenseEffect = 1;
            item->setColorTint({250, 80, 10, 255});
            return item;
        }
        case 18: {
            auto item = new RPGItem(index, 5, "Modré kalhoty", PANTS);
            item->setColorTint({100 - 20, 140 - 20, 220 - 20, 255});
            return item;
        }
        case 19: {
            auto item = new RPGItem(index, 5, "Fialové kalhoty", PANTS);
            item->setColorTint({80 - 20, 30 - 20, 220 - 20, 255});
            return item;
        }
        case 20: {
            auto item = new RPGItem(index, 5, "Brčálové kalhoty", PANTS);
            item->setColorTint({80 - 20, 255 - 20, 40 - 20, 255});
            return item;
        }
        case 21: {
            auto item = new RPGItem(index, 5, "Růžové kalhoty", PANTS);
            item->setColorTint({255 - 20, 140 - 20, 190 - 20, 255});
            return item;
        }
        case 22: {
            auto item = new RPGItem(index, 5, "Červené kalhoty", PANTS);
            item->setColorTint({200 - 20, 40 - 20, 40 - 20, 255});
            return item;
        }
        case 23: {
            auto item = new RPGItem(index, 5, "Oranžové Kalhoty", PANTS);
            item->setColorTint({250 - 20, 80 - 20, 10 - 10, 255});
            return item;
        }
        case 24: {
            auto item = new RPGItem(index, 4, "nic", SHIRT);
            item->defenseEffect = 1;
            item->temporal = true;
            item->setColorTint({255, 194, 161, 255});
            return item;
        }
        case 25: {
            auto item = new RPGItem(index, 5, "nic", PANTS);
            item->temporal = true;
            item->setColorTint({255, 194, 161, 255});
            return item;
        }
        default:
            cerr << "No such item for id: " << index << endl;
            throw runtime_error("Item not found");
    }
}

RPGItem::RPGItem(const int &id, const int &regionIndex, const string &name, const RPGItem::Type &type) :
        id(id),
        type(type),
        name(name),
        regionIndex(regionIndex),
        colorTint{255, 255, 255, 255} {
    this->id = id;
    this->type = type;
    this->name = name;
    this->regionIndex = regionIndex;
}

RPGItem::~RPGItem() {

}

int RPGItem::getId() const {
    return id;
}

int RPGItem::getMaxHealthEffect() const {
    return maxHealthEffect;
}

int RPGItem::getHealthEffect() const {
    return healthEffect;
}

int RPGItem::getDefenseEffect() const {
    return defenseEffect;
}

int RPGItem::getAttackEffect() const {
    return attackEffect;
}

RPGItem::Type RPGItem::getType() const {
    return type;
}

const string &RPGItem::getName() const {
    return name;
}

const SDL_Color &RPGItem::getColorTint() const {
    return colorTint;
}

void RPGItem::setColorTint(const SDL_Color &colorTint) {
    this->colorTint = colorTint;
}

const int &RPGItem::getRegionIndex() const {
    return regionIndex;
}

bool RPGItem::isEquipped() const {
    return equipped;
}

void RPGItem::setEquipped(bool equipped) {
    this->equipped = equipped;
}

bool RPGItem::isTemporal() {
    return temporal;
}
