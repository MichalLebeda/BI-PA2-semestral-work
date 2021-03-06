//
// Created by michal on 4/27/20.
//

#ifndef SEMESTRAL_WORK_Ghost_H
#define SEMESTRAL_WORK_Ghost_H


#include "Enemy.h"

/**
 * Ghost enemy
 */
class Ghost : public Enemy {
public:

    /**
     *
     * @param assets Assets instance for obtaining texture region
     * @param x X coordinate in game units
     * @param y Y coordinate in game units
     * @param world PhysBody
     * @param player Player to follow/attack
     */
    Ghost(const Assets *assets,
         int x, int y,
         PhysWorld *world,
         Player *player);

    int getId() override;
protected:

    Animation<TextureRegion> *getApproachingAnim() override;

    Animation<TextureRegion> *getDyingAnim() override;

    Animation<TextureRegion> *getAttackingAnim() override;

    Animation<TextureRegion> *getShockedAnim() override;
};


#endif //SEMESTRAL_WORK_Ghost_H
