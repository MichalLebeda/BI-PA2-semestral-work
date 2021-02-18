//
// Created by michal on 3/10/20.
//

#include "CameraRenderer.h"
#include "../Util.h"
#include <iostream>
#include <algorithm>

using namespace std;

CameraRenderer::CameraRenderer(SDL_Renderer *renderer, SDL_Rect originalRect) {
    this->renderer = renderer;
    this->originalRect = originalRect;

    SDL_RenderSetScale(renderer, currentZoom, currentZoom);

    font = TTF_OpenFont("examples/font.ttf", 32);
}

CameraRenderer::~CameraRenderer() {
    TTF_CloseFont(font);
    font = nullptr;
}


void CameraRenderer::setZoom(double zoom) {
    if (!zooming) {
        if (zoom > 0.5) {
            zoom = 0.5;
        }
        if (zoom < 0.09) {
            zoom = 0.09;
        }
        time = SDL_GetTicks();
        zooming = true;
        this->easeFromZoom = this->currentZoom;
        this->easeToZoom = zoom;
    }
}

void CameraRenderer::updateRect() {
    x += (targetX - x) / 20;
    y += (targetY - y) / 20;

    if (zooming) {
        uint32_t newTime = SDL_GetTicks();
        if (newTime - time > zoomLength * 1000) {
            zooming = false;
        } else {
            currentZoom = lerp(easeFromZoom, easeToZoom, ((float) (newTime - time)) / (zoomLength * 1000));
            SDL_RenderSetScale(renderer, currentZoom, currentZoom);
        }
    }
}

void CameraRenderer::setPosition(int worldX, int worldY) {
    x = worldX;
    y = worldY;
    targetX = x;
    targetY = y;
    updateRect();
}

void CameraRenderer::lookAt(int worldX, int worldY) {
    targetX = worldX;
    targetY = worldY;
    updateRect();
}

void CameraRenderer::renderTextureImmediately(SDL_Texture *texture, const SDL_Rect *srcRect, const SDL_Rect *dstRect) {
    tmpRec = *dstRect;

    tmpRec.x += originalRect.w / currentZoom / 2 - x;
    tmpRec.y += originalRect.h / currentZoom / 2 - y;

    SDL_RenderCopy(renderer, texture, srcRect, &tmpRec);
}

void CameraRenderer::renderRegionImmediately(TextureRegion *textureRegion, const SDL_Rect *dstRect) {
    tmpRec = *dstRect;

    tmpRec.x += originalRect.w / currentZoom / 2 - x;
    tmpRec.y += originalRect.h / currentZoom / 2 - y;

    SDL_RenderCopy(renderer, textureRegion->getTexture(), textureRegion->getRect(), &tmpRec);
}

void
CameraRenderer::renderRegionImmediately(TextureRegion *textureRegion, const SDL_Rect *dstRect, const SDL_Color *color) {
    SDL_SetTextureColorMod(textureRegion->getTexture(), color->r, color->g, color->b);

    tmpRec = *dstRect;

    tmpRec.x += originalRect.w / currentZoom / 2 - x;
    tmpRec.y += originalRect.h / currentZoom / 2 - y;

    SDL_RenderCopy(renderer, textureRegion->getTexture(), textureRegion->getRect(), &tmpRec);

    SDL_SetTextureColorMod(textureRegion->getTexture(), 255, 255, 255);
}

void
CameraRenderer::renderRegionImmediately(TextureRegion *textureRegion, const SDL_Rect *dstRect, int r, int g, int b) {
    SDL_SetTextureColorMod(textureRegion->getTexture(), r, g, b);

    tmpRec = *dstRect;

    tmpRec.x += originalRect.w / currentZoom / 2 - x;
    tmpRec.y += originalRect.h / currentZoom / 2 - y;

    SDL_RenderCopy(renderer, textureRegion->getTexture(), textureRegion->getRect(), &tmpRec);

    SDL_SetTextureColorMod(textureRegion->getTexture(), 255, 255, 255);
}

void CameraRenderer::renderRegionImmediately(TextureRegion *textureRegion, const int &rectX, const int &rectY,
                                             const int &rectW,
                                             const int &rectH) {
    tmpRec.x = rectX;
    tmpRec.y = rectY;
    tmpRec.w = rectW;
    tmpRec.h = rectH;

    tmpRec.x += originalRect.w / currentZoom / 2 - x;
    tmpRec.y += originalRect.h / currentZoom / 2 - y;

    SDL_RenderCopy(renderer, textureRegion->getTexture(), textureRegion->getRect(), &tmpRec);
}


void CameraRenderer::renderRegionImmediatelyAbsolutePos(TextureRegion *textureRegion, const SDL_Rect *dstRect) {
    SDL_RenderSetScale(renderer, 1, 1);
    SDL_RenderCopy(renderer, textureRegion->getTexture(), textureRegion->getRect(), dstRect);
    SDL_RenderSetScale(renderer, currentZoom, currentZoom);
}

void CameraRenderer::renderRegionImmediatelyAbsolutePos(TextureRegion *textureRegion,
                                                        const SDL_Rect *dstRect,
                                                        const SDL_Color *color) {
    SDL_RenderSetScale(renderer, 1, 1);
    SDL_SetTextureColorMod(textureRegion->getTexture(), color->r, color->g, color->b);

    SDL_RenderCopy(renderer, textureRegion->getTexture(), textureRegion->getRect(), dstRect);

    SDL_SetTextureColorMod(textureRegion->getTexture(), 255, 255, 255);
    SDL_RenderSetScale(renderer, currentZoom, currentZoom);
}

void CameraRenderer::renderRegionImmediatelyAbsolutePos(TextureRegion *textureRegion,
                                                        const SDL_Rect *dstRect,
                                                        int r,
                                                        int g,
                                                        int b) {
    SDL_RenderSetScale(renderer, 1, 1);
    SDL_SetTextureColorMod(textureRegion->getTexture(), r, g, b);

    SDL_RenderCopy(renderer, textureRegion->getTexture(), textureRegion->getRect(), dstRect);

    SDL_SetTextureColorMod(textureRegion->getTexture(), 255, 255, 255);
    SDL_RenderSetScale(renderer, currentZoom, currentZoom);
}

void CameraRenderer::renderRect(const SDL_Rect *rect) {
    tmpRec = (*rect);

    tmpRec.x += originalRect.w / currentZoom / 2 - x;
    tmpRec.y += originalRect.h / currentZoom / 2 - y;

    SDL_RenderFillRect(renderer, &tmpRec);
}

void CameraRenderer::renderRectLines(const SDL_Rect *rect) {
    int width = 2;
    tmpRec = (*rect);

    tmpRec.x += originalRect.w / currentZoom / 2 - x;
    tmpRec.y += originalRect.h / currentZoom / 2 - y;

    tmpRec.h = width / currentZoom;

    SDL_RenderFillRect(renderer, &tmpRec);

    tmpRec.y += rect->h - width / currentZoom;
    SDL_RenderFillRect(renderer, &tmpRec);

    tmpRec.h = rect->h;
    tmpRec.w = width / currentZoom;
    tmpRec.y = rect->y;
    tmpRec.y += originalRect.h / currentZoom / 2 - y;
    SDL_RenderFillRect(renderer, &tmpRec);

    tmpRec.x += rect->w - width / currentZoom;
    SDL_RenderFillRect(renderer, &tmpRec);
}

void CameraRenderer::setShapeColor(const SDL_Color &color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void CameraRenderer::setShapeColor(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void CameraRenderer::renderLaterDepthSorted(TextureRegion *textureRegion, const SDL_Rect &dstRect) {
    ZOrderedDraw zOrderedDraw;
    zOrderedDraw.region = textureRegion;
    zOrderedDraw.rect = dstRect;
    zOrderedDraw.zIndex = dstRect.y + dstRect.h;

    zOrder.push_back(zOrderedDraw);
}

void
CameraRenderer::renderLaterDepthSorted(TextureRegion *textureRegion, const SDL_Rect &dstRect, const SDL_Color &color) {
    renderLaterDepthSorted(textureRegion, dstRect, color.r, color.g, color.b);
}

void CameraRenderer::renderLaterDepthSorted(TextureRegion *textureRegion,
                                            const SDL_Rect &dstRect,
                                            const uint8_t &r,
                                            const uint8_t &g,
                                            const uint8_t &b) {
    ZOrderedDraw zOrderedDraw;
    zOrderedDraw.region = textureRegion;
    zOrderedDraw.rect = dstRect;
    zOrderedDraw.zIndex = dstRect.y + dstRect.h;
    zOrderedDraw.r = r;
    zOrderedDraw.g = g;
    zOrderedDraw.b = b;

    zOrder.push_back(zOrderedDraw);
}

void CameraRenderer::renderLaterDepthSorted(TextureRegion *textureRegion, const SDL_Rect &dstRect, int zIndex) {
    ZOrderedDraw zOrderedDraw;
    zOrderedDraw.region = textureRegion;
    zOrderedDraw.rect = dstRect;
    zOrderedDraw.zIndex = zIndex;

    zOrder.push_back(zOrderedDraw);
}


void CameraRenderer::renderLaterDepthSorted(TextureRegion *textureRegion,
                                            const int &rectX,
                                            const int &rectY,
                                            const int &rectW,
                                            const int &rectH,
                                            const int &zIndex) {
    SDL_Rect rect;
    rect.x = rectX;
    rect.y = rectY;
    rect.w = rectW;
    rect.h = rectH;

    ZOrderedDraw zOrderedDraw;
    zOrderedDraw.region = textureRegion;
    zOrderedDraw.rect = rect;
    zOrderedDraw.zIndex = zIndex;

    zOrder.push_back(zOrderedDraw);
}

void CameraRenderer::renderZOrdered() {
    sort(zOrder.begin(), zOrder.end());
    for (auto it = zOrder.begin(); it != zOrder.end(); it++) {
        SDL_SetTextureColorMod(it->region->getTexture(), it->r, it->g, it->b);
        renderRegionImmediately(it->region, &it->rect);
    }

    zOrder.clear();
}

void CameraRenderer::renderText(const char *text, int textX, int textY) {
    SDL_RenderSetScale(renderer, 1, 1);

    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int texW = 0;
    int texH = 0;

    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {textX, textY, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    SDL_RenderSetScale(renderer, currentZoom, currentZoom);
}

void CameraRenderer::renderText(const char *text, int textX, int textY, Uint8 r, Uint8 g, Uint8 b) {
    SDL_RenderSetScale(renderer, 1, 1);

    SDL_Color color = {r, g, b, 255};

    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int texW = 0;
    int texH = 0;

    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {textX, textY, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    SDL_RenderSetScale(renderer, currentZoom, currentZoom);
}

TTF_Font *CameraRenderer::getFont() {
    return font;
}
