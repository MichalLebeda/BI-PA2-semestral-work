//
// Created by michal on 3/10/20.
//

#ifndef SEMESTRAL_WORK_CAMERARENDERER_H
#define SEMESTRAL_WORK_CAMERARENDERER_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "../Util.h"
#include "TextureRegion.h"
#include "Renderable.h"

using namespace std;

/**
 * Wrapper around SDL_Renderer simulating basic camera
 */
class CameraRenderer {
public:

    /**
     *
     * @param renderer SDL_Renderer
     * @param originalRect SDL_Rect representing view area
     */
    CameraRenderer(SDL_Renderer *renderer, SDL_Rect originalRect);

    ~CameraRenderer();

    /**
     * Set zoom
     * @param zoom desired zoom level
     */
    void setZoom(double zoom);

    /**
     * @brief set target position to move to
     * @param worldX X target in game units
     * @param worldY y target in game units
     */
    void lookAt(int worldX, int worldY);

    /**
     * @brief immediately set center positions
     * @param worldX X in game units
     * @param worldY y in game units
     */
    void setPosition(int worldX, int worldY);

    /**
     * @brief Render part of the texture
     * @param texture Texture to draw
     * @param srcrect Source rectangle in texels units
     * @param dstrect Target rectangle in game units
     */
    void renderTextureImmediately(SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect);

    /**
     * @brief Render region in game units
     * @param textureRegion TextureRegion to be rendered
     * @param dstRect Area to be rendered to in screen units
     */
    void renderRegionImmediately(TextureRegion *textureRegion, const SDL_Rect *dstRect);

    /**
     * @brief Render region with tint in game units
     * @param textureRegion TextureRegion to be rendered
     * @param dstRect Area to be rendered to in screen units
     * @param color Tint color
     */
    void renderRegionImmediately(TextureRegion *textureRegion, const SDL_Rect *dstRect, const SDL_Color *color);

    /**
     * @brief Render region with tint in game units
     * @param textureRegion TextureRegion to be rendered
     * @param dstRect Area to be rendered to in screen units
     * @param r Red component of color tint
     * @param g Green component of color tint
     * @param b Blue component of color Tint
     */
    void renderRegionImmediately(TextureRegion *textureRegion, const SDL_Rect *dstRect, int r, int g, int b);

    /**
     * @brief Render region in game units
     * @param textureRegion TextureRegion to be rendered
     * @param rectX X position in game units
     * @param rectY Y position in game units
     * @param rectW Width in game units
     * @param rectH Height in game units
     */
    void renderRegionImmediately(TextureRegion *textureRegion,
                                 const int &rectX,
                                 const int &rectY,
                                 const int &rectW,
                                 const int &rectH);

    /**
     * @brief Render region in screen units
     * @param textureRegion TextureRegion to be rendered
     * @param dstRect Area to be rendered to in screen units
     */
    void renderRegionImmediatelyAbsolutePos(TextureRegion *textureRegion, const SDL_Rect *dstRect);

    /**
     * @brief Render region with tint in screen units
     * @param textureRegion TextureRegion to be rendered
     * @param dstRect Area to be rendered to in screen units
     * @param color Tint color
     */
    void renderRegionImmediatelyAbsolutePos(TextureRegion *textureRegion,
                                            const SDL_Rect *dstRect,
                                            const SDL_Color *color);


    /**
     * @brief Render region with tint in screen units
     * @param textureRegion TextureRegion to be rendered
     * @param dstRect Area to be rendered to in screen units
     * @param r Red component of color tint
     * @param g Green component of color tint
     * @param b Blue component of color Tint
     */
    void renderRegionImmediatelyAbsolutePos(TextureRegion *textureRegion, const SDL_Rect *dstRect, int r, int g, int b);

    /**
     * @brief Schedule region to be rendered Z ordered later
     * @param textureRegion TextureRegion to be rendered
     * @param dstRect Area to be rendered to in game units
     */
    void renderLaterDepthSorted(TextureRegion *textureRegion, const SDL_Rect &dstRect);

    /**
     * @brief Schedule region to be rendered Z ordered later
     * @param textureRegion TextureRegion to be rendered
     * @param dstRect Area to be rendered to in game units
     * @param color Tint color
     */
    void renderLaterDepthSorted(TextureRegion *textureRegion, const SDL_Rect &dstRect, const SDL_Color &color);

    /**
     * @brief Schedule region to be rendered Z ordered later
     * @param textureRegion TextureRegion to be rendered
     * @param dstRect Area to be rendered to in game units
     * @param r Red component of color tint
     * @param g Green component of color tint
     * @param b Blue component of color Tint
     */
    void renderLaterDepthSorted(TextureRegion *textureRegion,
                                const SDL_Rect &dstRect,
                                const uint8_t &r,
                                const uint8_t &g,
                                const uint8_t &b);

    /**
     * @brief Schedule region to be rendered Z ordered later
     * @param textureRegion TextureRegion to be rendered
     * @param dstRect Area to be rendered to in game units
     * @param zIndex Depth index to be used for sorting
     */
    void renderLaterDepthSorted(TextureRegion *textureRegion, const SDL_Rect &dstRect, int zIndex);

    /**
     * @brief Schedule region to be rendered Z ordered later
     * @param textureRegion TextureRegion to be rendered
     * @param rectX X position in game units
     * @param rectY Y position in game units
     * @param rectW Width in game units
     * @param rectH Height in game units
     * @param zIndex Depth index to be used for sorting
     */
    void renderLaterDepthSorted(TextureRegion *textureRegion,
                                const int &rectX,
                                const int &rectY,
                                const int &rectW,
                                const int &rectH,
                                const int &zIndex);

    /**
     * @brief Render everything for Z order rendering
     */
    void renderZOrdered();

    /**
     * @brief Render filled rectangle
     * @param rect Rectangle to be rendered
     */
    void renderRect(const SDL_Rect *rect);

    /**
     * @brief Render non filled rectangle
     * @param rect Rectangle to be rendered
     */
    void renderRectLines(const SDL_Rect *rect);

    /**
     * @brief update bounding rect and apply movement animation
     */
    void updateRect();

    /**
     * @brief Set color for future rendered shapes
     * @param color Desired color
     */
    void setShapeColor(const SDL_Color &color);

    /**
     * Set color for future rendered shapes
     * @param r Red color component
     * @param g Green color component
     * @param b Blue color component
     * @param a Alpha color component
     */
    void setShapeColor(int r, int g, int b, int a);

    /**
     * @brief Render text at specific coordinates
     * @param text Text char array
     * @param textX Screen X position
     * @param textY Screeen Y position
     */
    void renderText(const char *text, int textX, int textY);

    /**
     * @brief Render text at specific coordinates
     * @param text Text char array
     * @param textX Screen X position
     * @param textY Screeen Y position
     * @param r Red component of the desired color
     * @param g Green component of the desired color
     * @param b Blue component of the desired color
     */
    void renderText(const char *text, int textX, int textY, Uint8 r, Uint8 g, Uint8 b);

    /**
     * @brief Get font instance
     */
    TTF_Font *getFont();

    SDL_Rect originalRect = {0, 0, 0, 0};
    SDL_Rect tmpRec = {0, 0, 0, 0};
    int x, y;
    int targetX, targetY;
    float currentZoom = DEFAULT_ZOOM;
    float easeFromZoom = DEFAULT_ZOOM;
    float easeToZoom = DEFAULT_ZOOM;
    float zoomLength = 0.1;
    bool zooming = false;
    uint32_t time;
    SDL_Renderer *renderer;

private:
    TTF_Font *font;

    struct ZOrderedDraw {
        TextureRegion *region;
        SDL_Rect rect;
        int zIndex;
        uint8_t r = 255;
        uint8_t g = 255;
        uint8_t b = 255;

        bool operator<(const ZOrderedDraw &zOrderDraw) {
            return this->zIndex + this->zIndex < zOrderDraw.zIndex + zOrderDraw.zIndex;
        }
    };

    vector<ZOrderedDraw> zOrder;
};


#endif //SEMESTRAL_WORK_CAMERARENDERER_H
