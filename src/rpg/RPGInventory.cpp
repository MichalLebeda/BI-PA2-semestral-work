//
// Created by michal on 3/21/20.
//

#include "RPGInventory.h"
#include <algorithm>
#include <iostream>
#include <fstream>

RPGInventory::~RPGInventory() {
    for (auto it = items.begin(); it != items.end(); it++) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            delete *it2;
        }
    }
}

void RPGInventory::add(RPGItem *item) {
    auto it = items.find(item->getId());
    if (it != items.end()) {
        (*it).second.push_back(item);
    } else {
        vector<RPGItem *> category;
        category.push_back(item);
        items.insert(pair<int, vector<RPGItem *>>(item->getId(), category));
    }
}

void RPGInventory::remove(RPGItem *&item) {
    auto it = items.find(item->getId());
    if (it != items.end()) {
//        it->second.back() = nullptr;
        delete it->second.back();
        it->second.pop_back();
        if (it->second.size() == 0) {
            items.erase(it);
        }
    } else {
        throw runtime_error("cannot remove item from no slot");
    }
}

int RPGInventory::getAmountOfSlots() {
    return items.size();
}

map<int, vector<RPGItem *>> *RPGInventory::getSlots() {
    return &items;
}

void RPGInventory::deserialize(istream &is) {
    int typeCount;
    is >> typeCount;

    for (int i = 0; i < typeCount; i++) {
        if (is.bad()) {
            throw runtime_error("error reading save");
        }
        int itemID;
        int amount;

        is >> itemID;
        is >> amount;

        for (int j = 0; j < amount; j++) {
            RPGItem *item = RPGItem::createItem(itemID);
            add(item);
        }
    }
}

void RPGInventory::serialize(ostream &os) const {
    os << endl << items.size() << endl;

    for (auto it:items) {
        os << endl << it.second.front()->getId() << endl;
        os << it.second.size() << endl;
    }
}

