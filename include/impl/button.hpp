// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include "helper.hpp"
#include "renderer.hpp"
#include "text.hpp"
#include "widget_base.hpp"

#include <SDL3/SDL_rect.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <functional>
#include <string>


namespace uii {
class ButtonWidgetBase : public WidgetBase {
private:
	std::function<void()> m_callBack;

public:
	ButtonWidgetBase(Rect rect_, std::function<void()> callback_)
	    : WidgetBase(rect_), m_callBack(callback_) {}

	void onPressed() {
		m_callBack();
	}

	void setCallback(std::function<void()> callback) {
		m_callBack = callback;
	}
};

class ButtonWidget : public ButtonWidgetBase {};

class TextButtonWidget : public ButtonWidgetBase {
private:
	Text text;

public:
	TextButtonWidget(Rect rect_, std::function<void()> callback_, std::string text_, std::string fontFile_, float textSize_)
	    : ButtonWidgetBase(rect_, callback_), text(fontFile_, textSize_, text_) {}

	void render(Renderer& renderer) override {
		WidgetBase::render(renderer);
		renderer.renderText(text., m_rect)
	}
};

} // namespace uii