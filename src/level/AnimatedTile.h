//
// Created by michal on 3/18/20.
//

#ifndef SEMESTRAL_WORK_ANIMATEDTILE_H
#define SEMESTRAL_WORK_ANIMATEDTILE_H


#include "Tile.h"
#include "../graphics/Animation.h"

/**
 * Basic animated tile
 */
class AnimatedTile : public Tile {
public:

    /**
     *
     * @param animation Animation to be shown
     * @param x Top left x coordinate in game units
     * @param y Top right y coordinate in game units
     */
    AnimatedTile(Animation<TextureRegion> *animation, int x, int y);

    ~AnimatedTile();

    void render(CameraRenderer *renderer) override;

    /**
     * @brief Set random animation offset
     */
    void setRandomOffset();

private:
    Animation<TextureRegion> *animation;

    uint32_t time = 0;
};


#endif //SEMESTRAL_WORK_ANIMATEDTILE_H
