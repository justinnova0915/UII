// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "renderer.hpp"

namespace uii {
class Box {
private:
    SDL_FRect m_rect = {};
    SDL_Color m_color = {};

    Renderer& m_renderer;

public:
    Box(SDL_FRect rect_, SDL_Color color_, Renderer& r) 
        : m_rect(rect_), m_color(color_), m_renderer(r) {}

    void setRect(SDL_FRect r) { m_rect = r; }
    SDL_FRect getRect() const { return m_rect; }

    void render() {
        m_renderer.renderRect(m_rect, m_color);
    }
};
} 