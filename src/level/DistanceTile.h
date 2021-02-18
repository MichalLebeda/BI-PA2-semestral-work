//
// Created by michal on 3/20/20.
//

#ifndef SEMESTRAL_WORK_DISTANCETILE_H
#define SEMESTRAL_WORK_DISTANCETILE_H


#include "Tile.h"
#include "../graphics/Animation.h"
#include "../entities/Player.h"

/**
 * Tile with animation based on players distance
 */
class DistanceTile : public Tile {
public:

    /**
     *
     * @param animation Animation to be shown
     * @param x Top left x coordinate in game units
     * @param y Top right y coordinate in game units
     * @param player Player animation is based on
     */
    DistanceTile(Animation<TextureRegion> *animation, int x, int y, Player *player);

    ~DistanceTile();

    void render(CameraRenderer *renderer) override;

private:
    Animation<TextureRegion> *animation;

    Player *player;
};


#endif //SEMESTRAL_WORK_DISTANCETILE_H
