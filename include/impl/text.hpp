// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include "renderer.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace uii {

struct Text {
    TTF_Text* m_text;

    SDL_FPoint m_pos;
    SDL_Color m_color;
};

//Wrapper for SDL3_ttf
class TextHandler {
private:
    TTF_TextEngine* m_engine = nullptr;
    std::unordered_map<std::string, TTF_Font*> m_fonts;
    std::vector<Text> m_texts;

    Renderer& m_renderer;
public:

    // Constructor
    TextHandler(Renderer& renderer_)
        : m_renderer(renderer_)
    {
        if (!TTF_Init()) {
            //TODO: Daddy Jerry please teach exceptions
        }

        m_engine = TTF_CreateRendererTextEngine(m_renderer.getSDLRenderer());
    }


    void createFont(std::string handle, std::string path, float size) {

        if (!std::filesystem::exists(path)) {
            //TODO: Daddy Jerry please teach exceptions
        }

        m_fonts[handle] = TTF_OpenFont(path.c_str(), size);
    }

    void changeFontSize(std::string handle, float size) {
        
        if (m_fonts.find(handle) == m_fonts.end()) {
            //TODO: Daddy Jerry please teach exceptions
        }

        TTF_SetFontSize(m_fonts[handle], size);
    }

    int createText(std::string handle, std::string text, SDL_FPoint pos, SDL_Color color) {
        if (m_fonts.find(handle) == m_fonts.end()) {
            //TODO: Daddy Jerry please teach exceptions
        }

        Text t = Text{
            .m_text = TTF_CreateText(m_engine, m_fonts[handle], text.c_str(), 0),
            .m_pos = pos,
            .m_color = color
        };

        m_texts.push_back(t);
        return m_texts.size()-1;
    }

    void render() {
        for (Text t: m_texts) {
            m_renderer.renderText(t.m_text, t.m_pos);
        }
    }
};
}