// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "impl/uii/core/renderer.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>


namespace uii {
class WidgetBase {
protected:
	SDL_FRect m_rect;

public:
	WidgetBase(SDL_FRect rect_)
	    : m_rect(rect_) {}

	virtual void render(Renderer& renderer) {
		renderer.renderRect(m_rect, styleSheet.color);
	}

	virtual void update() {
		return;
	}

public:
	struct StyleSheet {
		SDL_Color color;
	} styleSheet;
};

class Widget : public WidgetBase {};
} // namespace uii