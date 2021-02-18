//
// Created by michal on 3/10/20.
//

#include "Assets.h"
#include "graphics/PlayerAnimFrame.h"
#include <iostream>

using namespace std;

Assets::Assets(SDL_Renderer *renderer) {
    this->renderer = renderer;
    loadTexture("assets/atlas.png", atlasTexture);

    tileRegions = createRegions(16, 16, 0, 16 * 32, atlasTexture);

    wallRegions = createRegions(16, 32, 0, 16 * 12, atlasTexture);

    shadowRegion = tileRegions.at(80);
    healthBarRegion = tileRegions.at(84);
    healthBarEmptyRegion = tileRegions.at(85);
    darkRegion = tileRegions.at(16 * 23);
    button = new TextureRegion(32, 336, 32, 16, atlasTexture);
    menuBg = new TextureRegion(0, 384, 208, 128, atlasTexture);

    itemRegions.push_back(new TextureRegion(0, 101, 3, 11, atlasTexture));
    itemRegions.push_back(new TextureRegion(3, 101, 3, 11, atlasTexture));
    itemRegions.push_back(new TextureRegion(6, 101, 3, 11, atlasTexture));
    itemRegions.push_back(new TextureRegion(9, 101, 3, 11, atlasTexture));
    itemRegions.push_back(new TextureRegion(12, 108, 10, 4, atlasTexture));
    itemRegions.push_back(new TextureRegion(22, 105, 6, 7, atlasTexture));
    itemRegions.push_back(new TextureRegion(28, 108, 4, 4, atlasTexture));
    itemRegions.push_back(new TextureRegion(28, 104, 4, 4, atlasTexture));

    tile215Regions = createRegions(16, 16, 214, 7, atlasTexture);
    tile222Regions = createRegions(16, 16, 221, 3, atlasTexture);
    tile237Regions = createRegions(16, 16, 236, 4, atlasTexture);

    playerAttackingLeftFrames = createPlayerFrames(16, 16, 128, 4, atlasTexture);
    playerAttackingRightFrames = createPlayerFrames(16, 16, 144, 4, atlasTexture);
    playerAttackingUpFrames = createPlayerFrames(16, 16, 176, 4, atlasTexture);
    playerAttackingDownFrames = createPlayerFrames(16, 16, 160, 4, atlasTexture);
    playerIdleDownFrames = createPlayerFrames(16, 16, 208, 2, atlasTexture);
    playerIdleUpFrames = createPlayerFrames(16, 16, 192, 2, atlasTexture);
    playerRunningUpFrames = createPlayerFrames(16, 16, 240, 4, atlasTexture);
    playerRunningDownFrames = createPlayerFrames(16, 16, 224, 4, atlasTexture);

    birdApproachingFrames = createRegions(16, 16, 115, 4, atlasTexture);
    birdDyingFrames = createRegions(16, 16, 120, 3, atlasTexture);
    birdShockedFrames = createRegions(16, 16, 123, 2, atlasTexture);
    birdAttackingFrames = createRegions(16, 16, 112, 3, atlasTexture);

    ghostApproachingFrames = createRegions(16, 16, 291, 3, atlasTexture);
    ghostDyingFrames = createRegions(16, 16, 295, 3, atlasTexture);
    ghostShockedFrames = createRegions(16, 16, 299, 2, atlasTexture);
    ghostAttackingFrames = createRegions(16, 16, 288, 3, atlasTexture);

    //ANIMATIONS
    playerAttackLeftAnim = new Animation<PlayerAnimFrame>(&playerAttackingLeftFrames, 70, 1);
    playerAttackRightAnim = new Animation<PlayerAnimFrame>(&playerAttackingRightFrames, 70, 1);
    playerAttackUpAnim = new Animation<PlayerAnimFrame>(&playerAttackingUpFrames, 70, 1);
    playerAttackDownAnim = new Animation<PlayerAnimFrame>(&playerAttackingDownFrames, 70, 1);
    playerIdleUpAnim = new Animation<PlayerAnimFrame>(&playerIdleUpFrames, 1800, 0);
    playerIdleDownAnim = new Animation<PlayerAnimFrame>(&playerIdleDownFrames, 1800, 0);
    playerRunningUpAnim = new Animation<PlayerAnimFrame>(&playerRunningUpFrames, 80, 0);
    playerRunningDownAnim = new Animation<PlayerAnimFrame>(&playerRunningDownFrames, 80, 0);

    birdApproachingAnim = new Animation<TextureRegion>(&birdApproachingFrames, 80, 0);
    birdDyingAnim = new Animation<TextureRegion>(&birdDyingFrames, 200, 1);
    birdShockedAnim = new Animation<TextureRegion>(&birdShockedFrames, 140, 4);
    birdAttackingAnim = new Animation<TextureRegion>(&birdAttackingFrames, 80, 1);

    ghostApproachingAnim = new Animation<TextureRegion>(&ghostApproachingFrames, 80, 0);
    ghostDyingAnim = new Animation<TextureRegion>(&ghostDyingFrames, 200, 1);
    ghostShockedAnim = new Animation<TextureRegion>(&ghostShockedFrames, 140, 4);
    ghostAttackingAnim = new Animation<TextureRegion>(&ghostAttackingFrames, 80, 1);

    tile103Anim = new Animation<TextureRegion>(&tile215Regions, 100, 0);
    tile222Anim = new Animation<TextureRegion>(&tile222Regions, 140, 0);
    tile237Anim = new Animation<TextureRegion>(&tile237Regions, 140, 0);
}

Assets::~Assets() {
    destroyRegions(tileRegions);
    destroyRegions(wallRegions);
    destroyRegions(itemRegions);

    destroyRegions(tile215Regions);
    destroyRegions(tile222Regions);
    destroyRegions(tile237Regions);

    destroyRegions(birdApproachingFrames);
    destroyRegions(birdAttackingFrames);
    destroyRegions(birdDyingFrames);
    destroyRegions(birdShockedFrames);

    destroyRegions(ghostApproachingFrames);
    destroyRegions(ghostAttackingFrames);
    destroyRegions(ghostDyingFrames);
    destroyRegions(ghostShockedFrames);

    destroyRegions(playerIdleUpFrames);
    destroyRegions(playerIdleDownFrames);
    destroyRegions(playerRunningUpFrames);
    destroyRegions(playerRunningDownFrames);
    destroyRegions(playerAttackingLeftFrames);
    destroyRegions(playerAttackingRightFrames);
    destroyRegions(playerAttackingUpFrames);
    destroyRegions(playerAttackingDownFrames);

    delete playerIdleUpAnim;
    delete playerIdleDownAnim;
    delete playerRunningDownAnim;
    delete playerRunningUpAnim;
    delete playerAttackLeftAnim;
    delete playerAttackRightAnim;
    delete playerAttackUpAnim;
    delete playerAttackDownAnim;

    delete birdApproachingAnim;
    delete birdAttackingAnim;
    delete birdDyingAnim;
    delete birdShockedAnim;

    delete ghostApproachingAnim;
    delete ghostAttackingAnim;
    delete ghostDyingAnim;
    delete ghostShockedAnim;

    delete tile103Anim;
    delete tile222Anim;
    delete tile237Anim;

    delete button;
    delete menuBg;

    destroyTex(atlasTexture);
}

void Assets::loadTexture(const char *filename, SDL_Texture *&texture) {
    texture = IMG_LoadTexture(renderer, filename);

    if (texture == nullptr) {
        throw runtime_error(string("could not load texture: ").append(filename).c_str());
    } else {
        cout << "successfully loaded texture: " << filename << endl;
    }
}

void Assets::destroyTex(SDL_Texture *texture) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

vector<TextureRegion *>
Assets::createRegions(int regionWidth, int regionHeight, int startIndex, int amount, SDL_Texture *texture) {
    vector<TextureRegion *> regions;

    int textureWidth;
    int textureHeight;
    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);

    int framesHorizontal = textureWidth / regionWidth;
    int framesVertical = textureHeight / regionHeight;

    int startXIndex = startIndex % framesHorizontal;
    int startYIndex = startIndex / framesHorizontal;

    for (int y = startYIndex, i = 0; y < framesVertical; y++) {
        for (int x = startXIndex; x < framesHorizontal && i < amount; x++, i++) {
            auto *region = new TextureRegion(x * regionWidth, y * regionHeight, regionWidth, regionHeight,
                                             atlasTexture);
            regions.push_back(region);
        }
    }

    return regions;
}

vector<PlayerAnimFrame *>
Assets::createPlayerFrames(int frameWidth, int frameHeight, int startIndex, int amount,
                           SDL_Texture *texture) {
    vector<PlayerAnimFrame *> frames;

    vector<TextureRegion *> bodyFrames = createRegions(frameWidth,
                                                       frameHeight,
                                                       startIndex,
                                                       amount,
                                                       texture);
    vector<TextureRegion *> shirtFrames = createRegions(frameWidth,
                                                        frameHeight,
                                                        startIndex + amount,
                                                        amount,
                                                        texture);
    vector<TextureRegion *> pantsFrames = createRegions(frameWidth,
                                                        frameHeight,
                                                        startIndex + 2 * amount,
                                                        amount,
                                                        texture);

    for (int i = 0; i < amount; i++) {
        auto *frame = new PlayerAnimFrame();
        frame->bodyRegion = bodyFrames.at(i);
        frame->shirtRegion = shirtFrames.at(i);
        frame->pantsRegion = pantsFrames.at(i);
        frames.push_back(frame);
    }

    return frames;
}

void Assets::destroyRegions(vector<TextureRegion *> &regions) {
    for (auto it:regions) {
        delete it;
    }
}

void Assets::destroyRegions(vector<PlayerAnimFrame *> &regions) {
    for (auto it:regions) {
        delete it;
    }
}
