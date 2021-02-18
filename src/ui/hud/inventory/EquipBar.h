//
// Created by michal on 3/26/20.
//

#ifndef SEMESTRAL_WORK_EQUIPBAR_H
#define SEMESTRAL_WORK_EQUIPBAR_H


#include "../../../rpg/RPGPlayer.h"
#include "../../../graphics/Renderable.h"
#include "../../../Assets.h"
#include "ConsumablesBar.h"

/**
 * Class for drawing equiped items
 */
class EquipBar : public Renderable {
public:

    /**
     *
     * @param rpgPlayer RPGPlayer whose equiped items will be displayed
     * @param assets Assets instance for rendering
     */
    EquipBar(RPGPlayer *rpgPlayer, Assets *assets);

    ~EquipBar();

    void render(CameraRenderer *renderer) override;

    /**
     * @brief Set position
     * @param x X in window coordinates
     * @param y Y in window coordinates
     */
    void setPosition(int x, int y);

    /**
     * @return EquipBar width
     */
    int getWidth() const;

    /**
     * @return EquipBar height
     */
    int getHeight() const;

    /**
     * @brief Check if point is inside bounding box
     * @param x X in screen coordinates
     * @param y Y in screen coordinates
     * @return True if x y is in bounding box
     */
    bool hit(int x, int y);

    /**
     * @brief Handle mouse hover
     * @param x X in pixel coordinates
     * @param y Y in pixel coordinates
     */
    void handleHover(int x, int y);

    /**
     * @brief Set equipBar to not hovered state
     */
    void setNotHovered();

    /**
     * @return Currently hovered item by cursor, can be null if not hovered
     */
    RPGItem *getHoveredItem();

private:
    /**
     * @brief Update bounding box
     */
    void updateBoundingBox();

    RPGPlayer *rpgPlayer;
    RPGInventory *rpgInventory;
    Assets *assets;
    SDL_Rect boundingBox;
    RPGItem *hoveredItem = nullptr;

    static const int SLOT_SIZE = 64;
    static const int SPACE = 8;
    static const int CATEGORY_SPACE = 16;
    static const int SLOT_BG_INDEX = 81;
    static const int SLOT_BG_EQUIPPED_INDEX = 82;
    static const int SLOT_BG_CONSUMABLE_INDEX = 83;

    void renderItem(const RPGItem *item, CameraRenderer *renderer, int row);
};


#endif //SEMESTRAL_WORK_EQUIPBAR_H
