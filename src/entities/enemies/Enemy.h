//
// Created by michal on 4/26/20.
//

#ifndef SEMESTRAL_WORK_ENEMY_H
#define SEMESTRAL_WORK_ENEMY_H


#include "../PhysicalEntity.h"
#include "../Player.h"

/**
 * Base class for enemies
 */
class Enemy : public PhysicalEntity {
public:

    /**
     *
     * @param asset Assets instance for obtaining resources
     * @param anim Initial animation
     * @param x X position coordinate in game units
     * @param y Y position coordinate in game units
     * @param bodyWidth Body width in game units
     * @param bodyHeight Body with in game units
     * @param health Amount of enemy health
     * @param healthMax Amount of maximum enemy health
     * @param defense Amount of defense points
     * @param attack Amount of attack points
     * @param world PhysWorld body is located in
     * @param player Player
     */
    Enemy(const Assets *asset, Animation<TextureRegion> *anim,
          int x, int y,
          int bodyWidth, int bodyHeight,
          int health,
          int healthMax,
          int defense,
          int attack,
          PhysWorld *world,
          Player *player);

    ~Enemy();

    void render(CameraRenderer *renderer) override;

    /**
     * Get RPG representation
     * @return RPG component of enemy
     */
    RPGCharacter *getRpgComponent();

    /**
     * Make enemy handle damage caused by character
     * @param character Character to cause damage
     */
    void handleDamage(RPGCharacter *character);

    /**
     * Indicate whatever enemy should be completely removed
     * @return true if should be removed false othervise
     */
    bool toBeRemoved();

    /**
     * Get id of type for serialization
     * @return Id of the enemy type
     */
    virtual int getId() = 0;

protected:
    /**
     * @brief Virtual method for obtaining approaching anim
     * @return Animation representing approaching state
     */
    virtual Animation<TextureRegion> *getApproachingAnim() = 0;

    /**
     * @brief Virtual method for obtaining dying anim
     * @return Animation representing dying state
     */
    virtual Animation<TextureRegion> *getDyingAnim() = 0;

    /**
     * @brief Virtual method for obtaining attacking anim
     * @return Animation representing attacking state
     */
    virtual Animation<TextureRegion> *getAttackingAnim() = 0;

    /**
     * @brief Virtual method for obtaining shocked anim
     * @return Animation representing shocked state
     */
    virtual Animation<TextureRegion> *getShockedAnim() = 0;

    /**
     * Enum representing Enemy states
     */
    enum State {
        APPROACHING, ATTACKING, SHOCKED, DYING, WAITING
    };

    /**
     * @brief Set state if current state allows it
     * @param nextState State to be set
     */
    void setState(State nextState);

    State state = WAITING;
    TextureRegion *shadowRegion;
    Animation<TextureRegion> *anim;
    Player *player;
    Uint32 time = 0;
    int timeUntilNextAttack;
    const Assets *assets;
    RPGCharacter *rpgCharacter;

    /**
     * @brief move towards player
     */
    void approachPlayer();

    /**
     * @brief Draw health bar above enemy
     * @param renderer Renderer to be drawn with
     */
    void drawHealthBar(CameraRenderer *renderer);

    /**
     * @brief Get vector pointing to the player center
     * @return SDL_Point representing vector pointing to the player body center
     */
    SDL_Point getVecToPlayer();

    /**
     * @brief get Distance to the player based on body centers
     * @return Distance to the player in game units
     */
    float toPlayerDistance();

    /**
     * @brief Reset timer for next attack
     */
    void prepareNextAttack();

    /**
     * @brief Try to attack player
     */
    void attack();
};


#endif //SEMESTRAL_WORK_ENEMY_H
