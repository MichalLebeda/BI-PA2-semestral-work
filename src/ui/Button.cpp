//
// Created by michal on 5/27/20.
//

#include "Button.h"

Button::Button(int x, int y, int width, int height, string text, const Assets *assets, TTF_Font *font)
        : boundingRect{x, y, width, height},
          text(text),
          assets(assets) {

    TTF_SizeUTF8(font, text.c_str(), &textWidth, &textHeight);
}

void Button::render(CameraRenderer *renderer) {
    if (hovered) {
        renderer->renderRegionImmediatelyAbsolutePos(assets->button, &boundingRect);
    } else {
        renderer->renderRegionImmediatelyAbsolutePos(assets->button, &boundingRect, &nonHoveredColor);
    }
    renderer->renderText(text.c_str(), boundingRect.x + boundingRect.w / 2 - textWidth / 2,
                         boundingRect.y + boundingRect.h / 2 - textHeight / 2);
}

bool Button::hit(int x, int y) {
    SDL_Point point;
    point.x = x;
    point.y = y;
    return SDL_PointInRect(&point, &boundingRect);
}

void Button::handleHover(int x, int y) {
    hovered = hit(x, y);
}
