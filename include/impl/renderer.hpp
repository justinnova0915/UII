// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

namespace uii {

class Renderer {
private:
    SDL_Renderer* renderer;
    SDL_Window* window;

    float WINDOW_WIDTH;
    float WINDOW_HEIGHT;

public:
    Renderer(float WINDOW_WIDTH_, float WINDOW_HEIGHT_) 
        : WINDOW_WIDTH(WINDOW_WIDTH_), WINDOW_HEIGHT(WINDOW_HEIGHT_)
    {   
        if (!SDL_CreateWindowAndRenderer("game", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
            SDL_Log("SDL Window Creation Error: %s", SDL_GetError());
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderVSync(renderer, 1);
    }

    void renderRect(SDL_FRect rect, SDL_Color c) {
        setRenderDrawColor(c);
        SDL_RenderRect(renderer, &rect);
    }

    void setRenderDrawColor(SDL_Color c) {
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    }
};
}