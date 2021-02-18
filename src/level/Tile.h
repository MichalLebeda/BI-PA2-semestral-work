//
// Created by michal on 3/9/20.
//

#ifndef SEMESTRAL_WORK_TILE_H
#define SEMESTRAL_WORK_TILE_H


#include "../graphics/Sprite.h"
#include "../entities/PhysicalEntity.h"

/**
 * Tile used in conjunction with a Level which draws it
 */
class Tile : Renderable {
public:
    /**
     *
     * @param region Desired tile region
     * @param x Top left corner X coordinate in game units
     * @param y Top left corner Y coordinate in game units
     */
    Tile(TextureRegion *region, int x, int y);

    ~Tile();

    void render(CameraRenderer *renderer);

    /**
     * @brief Assign Renderable to be drawn on top of this tile depth sorted
     * @param item Renderable to be set
     */
    void setWall(Renderable *item);

protected:
    Sprite *floorSprite = nullptr;
    Renderable *item = nullptr;
};


#endif //SEMESTRAL_WORK_TILE_H
