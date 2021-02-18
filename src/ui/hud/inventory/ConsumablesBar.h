//
// Created by michal on 3/28/20.
//

#ifndef SEMESTRAL_WORK_CONSUMABLESBAR_H
#define SEMESTRAL_WORK_CONSUMABLESBAR_H


#include "../../../rpg/RPGPlayer.h"
#include "../../../graphics/Renderable.h"
#include "../../../Assets.h"

/**
 * Class for drawing items player can consume
 */
class ConsumablesBar : public Renderable {
public:

    /**
     *
     * @param rpgPlayer RPGPlayer whose items should be shown
     * @param assets Assets instance for rendering
     */
    ConsumablesBar(RPGPlayer *rpgPlayer, Assets *assets);

    ~ConsumablesBar();

    void render(CameraRenderer *renderer) override;

    /**
     * @brief Set position
     * @param x X in window coordinates
     * @param y Y in window coordinates
     */
    void setPosition(int x, int y);

    /**
     * @brief Check if point is inside bounding box
     * @param x X in screen coordinates
     * @param y Y in screen coordinates
     * @return true if x y is in bounding box
     */
    bool hit(int x, int y);

    /**
     * @brief Handle click
     * @param x X in window coordinates
     * @param y Y in windo coordinates
     */
    void handleClick(int x, int y);

    /**
     * @brief Handle mouse hover
     * @param x X in screen coordinates
     * @param y Y in screen coordinates
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

    /**
     * @return Bar width
     */
    int getWidth();

    /**
     * @return Bar height
     */
    int getHeight();


private:
    RPGPlayer *rpgPlayer;
    RPGInventory *rpgInventory;
    Assets *assets;
    SDL_Rect boundingBox;
    RPGItem *hoveredItem = nullptr;

    static const int SLOT_SIZE = 64;
    static const int SPACE = 8;
    static const int CATEGORY_SPACE = 16;
    static const int TEXT_SPACE = 32;

    void updateBoundingBox();
};


#endif //SEMESTRAL_WORK_CONSUMABLESBAR_H
