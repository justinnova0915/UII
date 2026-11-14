// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdexcept>

namespace uii {
class Renderer {
private:
    SDL_Renderer* m_renderer;
    SDL_Window* m_window;

    float WINDOW_WIDTH;
    float WINDOW_HEIGHT;

public:
    Renderer(float WINDOW_WIDTH_, float WINDOW_HEIGHT_) 
        : WINDOW_WIDTH(WINDOW_WIDTH_), WINDOW_HEIGHT(WINDOW_HEIGHT_)
    {   
        if (!SDL_CreateWindowAndRenderer("game", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &m_window, &m_renderer)) {
            //SDL_Log("SDL Window Creation Error: %s", SDL_GetError());
            throw std::runtime_error("Failed to create window! oops");
        }

        SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderVSync(m_renderer, 1);
    }

    SDL_Renderer* getSDLRenderer() {
        return m_renderer;
    }

    void renderRect(SDL_FRect rect, SDL_Color c) {
        setRenderDrawColor(c);
        SDL_RenderRect(m_renderer, &rect);
    }

    void setRenderDrawColor(SDL_Color c) {
        SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
    }

    void renderText(TTF_Text* text, SDL_FPoint pos) {
        TTF_DrawRendererText(text, pos.x, pos.y);
    }
};
}