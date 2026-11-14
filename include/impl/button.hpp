// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include <SDL3/SDL_rect.h>
#include <functional>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "renderer.hpp"
#include "box.hpp"
#include "text.hpp"
#include "element.hpp"

namespace uii {
class Button: public BaseElement{
private:
    Box m_box;
    int m_textID;

    FontManager& m_textEngine;
    std::function<void()> m_callBack;
public:
    Button(Box box_, std::string text_, FontManager& textEngine_)
        : m_box(box_), m_textEngine(textEngine_) {
            m_textEngine.createText( fontHandle, std::string text, SDL_FPoint pos, SDL_Color color)
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