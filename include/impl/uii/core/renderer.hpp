// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include "impl/uii/infrastructure/infrastructure.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdexcept>

// ==================================================
// **************** Renderer Wrapper ****************
// ==================================================
/**
 * The core rendering encapsulation layer directly above SDL's raw rendering
 * instructions.
 * According to the architecture, Renderer should be globally singular.
 */

namespace uii {
class Renderer {
private:
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;

	float WINDOW_WIDTH;
	float WINDOW_HEIGHT;

private:
	void setRenderDrawColor_impl(SDL_Color c) {
		SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
	}

public:
	Renderer(float WINDOW_WIDTH_, float WINDOW_HEIGHT_)
	    : WINDOW_WIDTH(WINDOW_WIDTH_), WINDOW_HEIGHT(WINDOW_HEIGHT_) {
		if (!SDL_CreateWindowAndRenderer(
		        "game", WINDOW_WIDTH_, WINDOW_HEIGHT_, 0, &m_window, &m_renderer)) {
			throw std::runtime_error("Failed to create window! oops");
		}

		SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderVSync(m_renderer, 1);
	}
	~Renderer() {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
	}

	SDL_Renderer* getSDLRenderer() {
		return m_renderer;
	}

public:
	// ================ Main Loop ================

	void clear(SDL_Color c) {
		setRenderDrawColor_impl(c);
		SDL_RenderClear(m_renderer);
	}

	void swap() {
		SDL_RenderPresent(m_renderer);
	}

public:
	// ================ Public Interface ================

	void renderRect(FRect rect_, SDL_Color c) {
		setRenderDrawColor_impl(c);
		SDL_FRect rect = rect_.rect();
		SDL_RenderRect(m_renderer, &rect);
	}
};
} // namespace uii