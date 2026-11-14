// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "renderer.hpp"

namespace uii {
class BaseElement {
private:

public:
    virtual void render(Renderer& renderer)=0;
    virtual void update() {
        return;
    }
};
}