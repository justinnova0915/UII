// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "element.hpp"
#include "renderer.hpp"

namespace uii {
class Box : public BaseElement{
private:
    SDL_FRect m_rect = {};
    SDL_Color m_color = {};
public:
    Box(SDL_FRect rect_, SDL_Color color_) 
        : m_rect(rect_), m_color(color_) {}

    void setRect(SDL_FRect r) { m_rect = r; }
    SDL_FRect getRect() const { return m_rect; }

    void render(Renderer& renderer) override {
        renderer.renderRect(m_rect, m_color);
    }
};
} 