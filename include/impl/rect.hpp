// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include "tx/math.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>



class Box {
private:
    SDL_FRect rect = {};
    SDL_Color color = {};

    SDL_Renderer* renderer;

public:
    Box(SDL_FRect rect_, SDL_Color color_, SDL_Renderer* renderer_) 
        : rect(rect_), color(color_), renderer(renderer_) {}

    void render() {
        SDL_SetRenderDrawColor(renderer, &color.r, &colot.g, &colot.b, & color.a);
        SDL_RenderRect(renderer, rect)
    }
};

namespace uii {

}