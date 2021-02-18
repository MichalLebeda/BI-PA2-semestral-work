//
// Created by michal on 3/21/20.
//

#ifndef SEMESTRAL_WORK_RPGINVENTORY_H
#define SEMESTRAL_WORK_RPGINVENTORY_H


#include "RPGItem.h"
#include "../Serializable.h"
#include <vector>
#include <map>

/**
 * Basic RPG representation of inventory
 */
class RPGInventory : public Serializable {
public:
    RPGInventory() = default;

    virtual ~RPGInventory();

    /**
     * Add item to inventory, create slot if needed or insert into existing
     * @param item Item to be added
     */
    void add(RPGItem *item);

    void serialize(std::ostream &os) const override;

    void deserialize(std::istream &is) override;

    /**
     * Get map containing all slots with item type as a key
     * @return Map containing slots
     */
    map<int, vector<RPGItem *>> *getSlots();

    /**
     * @brief Remove instance of one item from inventory
     * @param item Item to be removed
     */
    void remove(RPGItem *&item);

    /**
     * @brief Get amount of different slots aka different items in inventory
     * @return Amount of different slots
     */
    int getAmountOfSlots();

private:
    map<int, vector<RPGItem *>> items;
};


#endif //SEMESTRAL_WORK_RPGINVENTORY_H
