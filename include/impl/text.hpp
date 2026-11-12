// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "renderer.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace uii {

//Wrapper for SDL3_ttf
class Text {
private:
    TTF_TextEngine* m_engine = nullptr;
    TTF_Font* m_font = nullptr;

    Renderer& m_renderer;
public:

    // Constructor
    Text(Renderer& renderer_)
        : m_renderer(renderer_)
    {
        if (!TTF_Init()) {
            //TODO: Daddy Jerry please teach exceptions
        }

        m_engine = TTF_CreateRendererTextEngine(m_renderer.getSDLRenderer());
    }


    void Create font
}

}