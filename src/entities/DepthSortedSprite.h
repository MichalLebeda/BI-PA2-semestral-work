//
// Created by michal on 3/11/20.
//

#ifndef SEMESTRAL_WORK_DEPTHSORTEDSPRITE_H
#define SEMESTRAL_WORK_DEPTHSORTEDSPRITE_H


#include "../Assets.h"
#include "../graphics/Sprite.h"

/**
 * Sprite drawn sorted based on its y coordinate (to fake depth)
 */
class DepthSortedSprite : public Sprite {
public:

    /**
     *
     * @param textureRegion desired region of the sprite
     * @param x X coordinate in game units
     * @param y Y coordinate in game units
     */
    DepthSortedSprite(TextureRegion *textureRegion, int x, int y);

    void render(CameraRenderer *renderer) override;
};


#endif //SEMESTRAL_WORK_DEPTHSORTEDSPRITE_H
