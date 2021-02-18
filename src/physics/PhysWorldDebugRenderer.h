//
// Created by michal on 3/16/20.
//

#ifndef SEMESTRAL_WORK_PHYSWORLDDEBUGRENDERER_H
#define SEMESTRAL_WORK_PHYSWORLDDEBUGRENDERER_H


#include "PhysWorld.h"

/**
 * Simple debug renderer for PhysWorld
 */
class PhysWorldDebugRenderer : public Renderable {
public:
    PhysWorldDebugRenderer();

    void render(CameraRenderer *renderer) override;

    /**
     * Get rendered world
     * @return Rendered PhysWorld
     */
    PhysWorld *getWorld() const;

    /**
     * Set PhysWorld to Render
     * @param world PhysWorld to render
     */
    void setWorld(PhysWorld *world);

private:
    PhysWorld *world;
};


#endif //SEMESTRAL_WORK_PHYSWORLDDEBUGRENDERER_H
