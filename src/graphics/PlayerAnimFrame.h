//
// Created by michal on 3/20/20.
//

#ifndef SEMESTRAL_WORK_PLAYERANIMFRAME_H
#define SEMESTRAL_WORK_PLAYERANIMFRAME_H


#include "TextureRegion.h"

/**
 * Struct representing player animation frames.
 * It is impossible to use one texture region for whole player because of multiple parts being rendered for tinting.
 */
struct PlayerAnimFrame {
    TextureRegion *bodyRegion;
    TextureRegion *shirtRegion;
    TextureRegion *pantsRegion;

    ~PlayerAnimFrame() {
        delete bodyRegion;
        delete shirtRegion;
        delete pantsRegion;
    }
};


#endif //SEMESTRAL_WORK_PLAYERANIMFRAME_H
