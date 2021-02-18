//
// Created by michal on 3/26/20.
//

#ifndef SEMESTRAL_WORK_HUD_H
#define SEMESTRAL_WORK_HUD_H


#include "../../graphics/Renderable.h"
#include "../../rpg/RPGPlayer.h"
#include "inventory/EquipBar.h"
#include "inventory/ItemInfoText.h"

/**
 * Hud showing info about equiped items and player stats
 */
class Hud : public Renderable {
public:

    /**
     *
     * @param windowWidth Window width in pixels
     * @param windowHeight Window height in pixels
     * @param rpgPlayer Rpg player to draw info about
     * @param assets Assets instance for drawing
     */
    Hud(int windowWidth, int windowHeight, RPGPlayer *rpgPlayer, Assets *assets);

    ~Hud();

    void render(CameraRenderer *renderer) override;

    /**
     * @brief Make hud to handle click at X Y (Hud action is not guaranteed)
     * @param x X pixel coordinate
     * @param y Y pixel coordinate
     */
    void handleClick(int x, int y);

    /**
     * @brief Make hud to handle hover at X Y (Hud action is not guaranteed)
     * @param x X pixel coordinate
     * @param y Y pixel coordinate
     */
    void handleHover(int x, int y);

    /**
     * @brief Set item that player is standing on to later draw further info about it
     * @param item
     */
    void setItemUnderPlayer(const RPGItem *item);

private:
    void renderHealthBar(CameraRenderer *renderer);

    RPGPlayer *rpgPlayer;
    Assets *assets;
    EquipBar equipBar;
    ConsumablesBar consumablesBar;
    ItemInfoText info;
    ItemInfoText underPlayerItemInfo;

    int windowWidth;
    int windowHeight;
    int virtualHealth = 0;
};


#endif //SEMESTRAL_WORK_HUD_H
