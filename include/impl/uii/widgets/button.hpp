// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include "impl/uii/core/core.hpp"

#include <SDL3/SDL_rect.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <functional>


namespace uii {
class ButtonWidgetBase : public WidgetBase {
private:
	std::function<void()> m_callBack;

public:
	ButtonWidgetBase(SDL_FRect rect_, std::function<void()> callback_)
	    : WidgetBase(rect_), m_callBack(callback_) {}

	void onPressed() {
		m_callBack();
	}

	void setCallback(std::function<void()> callback) {
		m_callBack = callback;
	}
};

class ButtonWidget : public ButtonWidgetBase {};

class TextButtonWidget : public ButtonWidgetBase {};

} // namespace uii