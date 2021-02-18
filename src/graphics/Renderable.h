//
// Created by michal on 3/10/20.
//

#ifndef SEMESTRAL_WORK_RENDERABLE_H
#define SEMESTRAL_WORK_RENDERABLE_H


#include <SDL2/SDL_render.h>
#include "CameraRenderer.h"

class CameraRenderer;

/**
 * Basic Renderable interface
 */
class Renderable {
public:

    Renderable() = default;

    virtual ~Renderable() = default;

    /**
     * @brief renders object
     * @param renderer
     */
    virtual void render(CameraRenderer *renderer) = 0;

};

#endif //SEMESTRAL_WORK_RENDERABLE_H
