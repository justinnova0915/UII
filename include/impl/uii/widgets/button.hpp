// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include "impl/uii/core/context.hpp"
#include "impl/uii/core/core.hpp"
#include "impl/uii/core/input.hpp"
#include "impl/uii/core/text.hpp"

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
	ButtonWidgetBase(FRect rect_, SDL_Color color_, std::function<void()> callback_)
	    : WidgetBase(rect_, StyleSheet{ .color = color_ }), m_callBack(callback_) {}

	void update(WindowContext& context) override {
		if (context.input->isMouseDown(InputManager::MouseButtons::LEFT)) {
			onPressed();
		}
	}

	void onPressed() {
		m_callBack();
	}

	void setCallback(std::function<void()> callback) {
		m_callBack = callback;
	}
};

class ButtonWidget : public ButtonWidgetBase {
public:
	ButtonWidget(FRect rect_, SDL_Color color_, std::function<void()> callback_)
	    : ButtonWidgetBase(rect_, color_, callback_) {}
};

class TextButtonWidget : public ButtonWidgetBase {
private:
	Text text;

public:
	TextButtonWidget(FontManager& fontManager_, FRect rect_, SDL_Color color_, std::function<void()> callback_, std::string text_, std::string fontFile_, float textSize_)
	    : ButtonWidgetBase(rect_, color_, callback_), text(fontManager_, fontFile_, textSize_, text_) {}

	void render(WindowContext& context) override {
		WidgetBase::render(context);
		text.render(m_rect.topLeft());
	}
};

} // namespace uii