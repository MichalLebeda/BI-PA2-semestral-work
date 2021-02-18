//
// Created by michal on 3/11/20.
//

#ifndef SEMESTRAL_WORK_PHYSICALENTITY_H
#define SEMESTRAL_WORK_PHYSICALENTITY_H


#include "../graphics/Renderable.h"
#include "../graphics/Sprite.h"
#include "../physics/PhysBody.h"
#include "../physics/PhysWorld.h"

/**
 * Sprite attached to body and drawn based on its position
 */
class PhysicalEntity : public Renderable {
public:

    /**
     * @brief This constructor creates new body and attaches entity to it
     * @param region Region to be drawn later
     * @param x X center coordinate in game units of newly created body
     * @param y Y center coordinate in game units of newly created body
     * @param bodyWidth Body width in game units of newly created body
     * @param bodyHeight Body Height in game units of newly created body
     * @param dynamic True if body should move, false otherwise
     * @param world PhysWorld this entity belongs to
     */
    PhysicalEntity(TextureRegion *region, int x, int y, int bodyWidth, int bodyHeight, bool dynamic, PhysWorld *world);

    /**
     *
     * @param region Region to be drawn later
     * @param body PhysBody to attach entity to
     */
    PhysicalEntity(TextureRegion *region, PhysBody *body);

    /**
     * Constructor without PhysBody, must set body later
     * @param region Region to be drawn later
     */
    PhysicalEntity(TextureRegion *region);

    ~PhysicalEntity();

    /**
     * Get PhysBody this sprite is attached to
     * @return PhysBody
     */
    PhysBody *getBody();

    void render(CameraRenderer *renderer) override;

    /**
     * @brief Set top left corner offset from body center
     * @param xOffset X offset to be set
     * @param yOffset Y offset to be set
     */
    void setSpriteOffset(int xOffset, int yOffset);

    /**
     * @brief Set top left corner X coor offset from body center
     * @param xOffset X offset to be set
     */
    void setSpriteOffsetX(int xOffset);

    /**
     * @brief Set top left corner Y coor offset from body center
     * @param yOffset Y offset to be set
     */
    void setSpriteOffsetY(int yOffset);

    /**
     * @brief Align sprite center to body center
     */
    void alignSpriteCenter();

    /**
     * @brief Align sprite on top of the center of the body
     */
    void alignSpriteTopCenter();

    /**
     * @brief Sync sprite position to PhysBody position
     */
    void updateSpritePosition();

protected:

    /**
     * @brief Create and correctly configure body
     * @param x X center coordinate in game units of newly created body
     * @param y Y center coordinate in game units of newly created body
     * @param width Body width in game units of newly created body
     * @param height Body Height in game units of newly created body
     * @param dynamic True if body should move, false otherwise
     */
    void createBody(int x, int y, int width, int height, bool dynamic);

    Sprite *sprite;

    PhysBody *body;

    bool positionDirty = true;

    int spriteOffsetX = 0;

    int spriteOffsetY = 0;
};


#endif //SEMESTRAL_WORK_PHYSICALENTITY_H
