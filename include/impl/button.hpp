// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include <functional>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "renderer.hpp"
#include "box.hpp"
#include "text.hpp"

namespace uii {
class Button {
private:
    Box m_box;
    Text m_text;

    std::function<void()> m_callBack;
public:
    Button(Box box_, Text text_)
        : m_box(box_), m_text(text_) { }

    void onPressed() {
        m_callBack();
    }

    void hookCallback(std::function<void()> callback) {
        m_callBack = callback;
    }

    void render() {
        renderer
    }

};
}