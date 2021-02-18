//
// Created by michal on 3/10/20.
//

#ifndef SEMESTRAL_WORK_ASSETS_H
#define SEMESTRAL_WORK_ASSETS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "graphics/TextureRegion.h"
#include "graphics/Animation.h"
#include "graphics/PlayerAnimFrame.h"


using namespace std;

/**
 * Class for storing texture, texture regions and animations
 */
class Assets {
public:

    /**
     *
     * @param renderer SDL renderer necessary for texture creation
     */
    Assets(SDL_Renderer *renderer);

    ~Assets();

    TextureRegion *shadowRegion;
    TextureRegion *healthBarRegion;
    TextureRegion *healthBarEmptyRegion;
    TextureRegion *darkRegion;
    TextureRegion *button;
    TextureRegion *menuBg;

    vector<TextureRegion *> tileRegions;
    vector<TextureRegion *> wallRegions;
    vector<TextureRegion *> itemRegions;

    vector<TextureRegion *> tile215Regions;
    vector<TextureRegion *> tile222Regions;
    vector<TextureRegion *> tile237Regions;

    Animation<TextureRegion> *tile103Anim;
    Animation<TextureRegion> *tile222Anim;
    Animation<TextureRegion> *tile237Anim;

    vector<PlayerAnimFrame *> playerAttackingLeftFrames;
    vector<PlayerAnimFrame *> playerAttackingRightFrames;
    vector<PlayerAnimFrame *> playerAttackingUpFrames;
    vector<PlayerAnimFrame *> playerAttackingDownFrames;
    vector<PlayerAnimFrame *> playerIdleUpFrames;
    vector<PlayerAnimFrame *> playerIdleDownFrames;
    vector<PlayerAnimFrame *> playerRunningUpFrames;
    vector<PlayerAnimFrame *> playerRunningDownFrames;

    Animation<PlayerAnimFrame> *playerAttackLeftAnim;
    Animation<PlayerAnimFrame> *playerAttackRightAnim;
    Animation<PlayerAnimFrame> *playerAttackUpAnim;
    Animation<PlayerAnimFrame> *playerAttackDownAnim;
    Animation<PlayerAnimFrame> *playerIdleUpAnim;
    Animation<PlayerAnimFrame> *playerIdleDownAnim;
    Animation<PlayerAnimFrame> *playerRunningUpAnim;
    Animation<PlayerAnimFrame> *playerRunningDownAnim;

    vector<TextureRegion *> birdApproachingFrames;
    vector<TextureRegion *> birdDyingFrames;
    vector<TextureRegion *> birdAttackingFrames;
    vector<TextureRegion *> birdShockedFrames;

    Animation<TextureRegion> *birdApproachingAnim;
    Animation<TextureRegion> *birdDyingAnim;
    Animation<TextureRegion> *birdShockedAnim;
    Animation<TextureRegion> *birdAttackingAnim;

    vector<TextureRegion *> ghostApproachingFrames;
    vector<TextureRegion *> ghostDyingFrames;
    vector<TextureRegion *> ghostAttackingFrames;
    vector<TextureRegion *> ghostShockedFrames;

    Animation<TextureRegion> *ghostApproachingAnim;
    Animation<TextureRegion> *ghostDyingAnim;
    Animation<TextureRegion> *ghostShockedAnim;
    Animation<TextureRegion> *ghostAttackingAnim;
private:

    /**
     * @brief Properly destroy texture
     * @param texture Texture to destroy
     */
    static void destroyTex(SDL_Texture *texture);

    /**
     * @brief Properly delete regions
     * @param regions Regions to destroy
     */
    static void destroyRegions(vector<TextureRegion *> &regions);

    /**
     * @brief Properly delete player regions
     * @param regions Regions to destroy
     */
    static void destroyRegions(vector<PlayerAnimFrame *> &regions);

    /**
     * @brief Load texture from file
     * @param filename Texture source filename
     * @param texture Pointer to load texture to
     */
    void loadTexture(const char *filename, SDL_Texture *&texture);

    /**
     * @brief Cut texture into smaller regions
     * @param regionWidth Width of regions
     * @param regionHeight Height of regions
     * @param startIndex First index of region to be included in vector
     * @param amount Number of elements in final vector
     * @param texture Texture to create regions from
     * @return Vector of created regions
     */
    vector<TextureRegion *> createRegions(int regionWidth, int regionHeight, int startIndex,
                                          int amount,
                                          SDL_Texture *texture);

    /**
     * @brief Create animation frames for player
     * @param frameWidth Width of regions
     * @param frameHeight Height of regions
     * @param startIndex First index of region to be included in vector
     * @param amount Number of elements in final vector
     * @param texture Texture to create regions from
     * @return Vector of created PlayerAnimFrames
     */
    vector<PlayerAnimFrame *> createPlayerFrames(int frameWidth, int frameHeight, int startIndex,
                                                 int amount,
                                                 SDL_Texture *texture);

    SDL_Renderer *renderer;
    SDL_Texture *atlasTexture = nullptr;
};


#endif //SEMESTRAL_WORK_ASSETS_H
