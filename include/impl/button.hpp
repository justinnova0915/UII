// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <functional>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

#include "renderer.hpp"
#include "box.hpp"
#include "text.hpp"
#include "element.hpp"

namespace uii {
class Button: public BaseElement {
private:
    Box m_box;
    Label m_text;

    FontManager& m_textEngine;
    std::function<void()> m_callBack;
public:
    Button(Box box_, std::string text_, FontManager& textEngine_, std::string fontHandle_)
        : m_box(box_), m_textEngine(textEngine_) {
            m_textEngine.createText(fontHandle_, text_, (box_..x, , SDL_Color color)
        }

    void onPressed() {
        m_callBack();
    }

    void hookCallback(std::function<void()> callback) {
        m_callBack = callback;
    }

    void update(SDL_FPoint mouse) override {

    }



    void render() override {
        m_box.render();
        m_textEngine.render()
    }

};
}