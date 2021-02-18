//
// Created by michal on 3/25/20.
//

#ifndef SEMESTRAL_WORK_ITEM_H
#define SEMESTRAL_WORK_ITEM_H


#include "../entities/PhysicalEntity.h"
#include "../Assets.h"
#include "../rpg/RPGItem.h"

/**
 * Graphical representation of RPGItem
 */
class Item : public PhysicalEntity {
public:

    /**
     *
     * @param tileX X coordinate of the tile item is located on
     * @param tileY Y coordinate of the tile item is located on
     * @param rpgItem RPG representation of that item
     * @param physWorld Phys world
     * @param assets Assets instance for obtaining textures
     */
    Item(int tileX, int tileY, RPGItem *rpgItem, PhysWorld *physWorld, const Assets *assets);

    void render(CameraRenderer *renderer) override;

    /**
     * @brief get identifier of this particular item
     * @return Type identifier from underlying RPGItem
     */
    int getId();

    /**
     * @brief Get tile X coordinate in game units
     * @return
     */
    int getTileX();

    /**
     * @brief Get tile Y coordinate in game units
     * @return
     */
    int getTileY();

private:
    int tileX;
    int tileY;
    const Assets *assets;
};

#endif //SEMESTRAL_WORK_ITEM_H
