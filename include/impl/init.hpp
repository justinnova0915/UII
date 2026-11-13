// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "renderer.hpp"
#include "box.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

namespace uii {

inline void init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL Error: %s", SDL_GetError());
    }
}
}

