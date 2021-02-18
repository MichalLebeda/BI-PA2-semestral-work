//
// Created by michal on 3/11/20.
//

#ifndef SEMESTRAL_WORK_PLAYER_H
#define SEMESTRAL_WORK_PLAYER_H


#include "PhysicalEntity.h"
#include "../Assets.h"
#include "../rpg/RPGPlayer.h"
#include <iostream>

using namespace std;

/**
 * Graphical representation of RPGPlayer with PhysBody attached
 */
class Player : public PhysicalEntity {
public:

    /**
     *
     * @param assets Assets instance for rendering
     * @param x Player body center x in game units
     * @param y Player body center x in game units
     * @param player RPGPlayer
     * @param world PhysWorld player is gonna live in
     */
    Player(const Assets *assets, int x, int y, RPGPlayer *player, PhysWorld *world);

    ~Player();

    void render(CameraRenderer *renderer) override;

    /**
     * Set position of the PhysBody center in PhysWorld coordinates (same as game units)
     * @param worldX X world position
     * @param worldY Y world position
     */
    void setPosition(int worldX, int worldY);

    /**
     * @brief Get RPG component assigned to the player
     * @return RPGPlayer component
     */
    RPGPlayer *getRpgComponent();

    /**
     * @brief Go to left direction
     */
    void goLeft();

    /**
     * @brief Go to right direction
     */
    void goRight();

    /**
     * @brief Go to up direction
     */
    void goUp();

    /**
     * @brief Go to down direction
     */
    void goDown();

    /**
     * @brief Attack left
     */
    void attackLeft();

    /**
     * @brief Attack right
     */
    void attackRight();

    /**
     * @brief Attack up
     */
    void attackUp();

    /**
     * @brief Attack down
     */
    void attackDown();

private:
    /**
     * @brief Create attack hitbox at the player position
     * @return PhysBody representing attack hitbox
     */
    PhysBody *createAttackHitbox();

    enum State {
        IDLE, RUNNING, ATTACKING
    };

    enum Direction {
        LEFT, RIGHT, UP, DOWN
    };

    /**
     * Set state (if possible)
     * @param nextState Next State to be set
     */
    void setState(State nextState);

    State state = IDLE;
    Direction direction = DOWN;

    Uint32 time = 0;
    Animation<PlayerAnimFrame> *animation;
    Sprite weaponSprite;
    const Assets *assets;
    PhysWorld *world;

    RPGPlayer *rpgPlayer;
};


#endif //SEMESTRAL_WORK_PLAYER_H
