// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.
#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <vector>

#include "element.hpp"
#include "renderer.hpp"

namespace uii {
class Screen {
private:
    std::vector<BaseElement*> m_elements;

public:

    Screen(std::vector<BaseElement*> elements_)
        : m_elements(elements_) { }

    void addElement(BaseElement* e) {
        m_elements.push_back(e);
    }

    void render(Renderer& renderer) {
        for (BaseElement* e: m_elements) {
            e->render(renderer);
        }
    }

    void update() {
        for (BaseElement* e: m_elements) {
            e->update();
        }
    }
};
}