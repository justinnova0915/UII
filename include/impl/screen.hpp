// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.
#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <variant>
#include <vector>

#include "box.hpp"
#include "text.hpp"
#include "renderer.hpp"

namespace uii {
class Screen {
private:

    std::vector<element> m_elements;
    Renderer* m_renderer;
    
public:

    Screen(std::vector<element> elements_, Renderer* renderer_)
        : m_elements(elements_), m_renderer(renderer_) { }

    void addElement(element e) {
        m_elements.push_back(e);
    }

    void render() {
        for (element e: m_elements) {
        }
    }
};
}