//
// Created by michal on 4/27/20.
//

#ifndef SEMESTRAL_WORK_ENEMIES_H
#define SEMESTRAL_WORK_ENEMIES_H


#include "../../physics/PhysBody.h"
#include "Enemy.h"

/**
 * Class taking care of Enemies vector providing wrappers for adding and removing plus rendering.
 * This class is also able to save and load enemies
 */
class Enemies : public Renderable, Serializable {
public:

    /**
     *
     * @param assets Assets instance for enemies
     * @param world PhysWorld enemy bodies are located in
     * @param player Player
     */
    Enemies(const Assets *assets, PhysWorld *world, Player *player);

    ~Enemies() override;

    void render(CameraRenderer *renderer) override;

    /**
     * Add enemy to Enemy system
     * @param enemy Enemy to be added
     */
    void addEnemy(Enemy *enemy);

    /**
     * @brief Add enemy with non default health
     * @param id Type id of enemy
     * @param x Enemy body x
     * @param y Enemy body Y
     * @return Added enemy
     */
    Enemy *addEnemy(int id, int x, int y);

    /**
     * @brief Add enemy with non default health
     * @param id Type id of enemy
     * @param x Enemy body x
     * @param y Enemy body Y
     * @param health Health
     * @return Added enemy
     */
    Enemy *addEnemy(int id, int x, int y, int health);

    /**
     * @brief Search for enemy by passing body
     * @param body Body of the Enemy we are looking for
     * @return Enemy we are looking for based on passed PhysBody
     */
    Enemy *getByBody(PhysBody *body);

    void serialize(std::ostream &os) const override;

    void deserialize(std::istream &is) override;

    /**
     * enum representing enemy type identifiers
     */
    enum Id {
        BIRD, GHOST
    };

private:
    const Assets *assets;
    PhysWorld *world;
    Player *player;
    map<PhysBody *, Enemy *> enemies;
};


#endif //SEMESTRAL_WORK_ENEMIES_H
