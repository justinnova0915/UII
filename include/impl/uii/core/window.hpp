// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "context.hpp"
#include "widget_base.hpp"
#include "text.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_mouse.h>


namespace uii {
class Window {
private:
	// dingle berry
	Context context;

	void populateContext() {
		SDL_PollEvent(&context.event);
		SDL_GetMouseState(&context.mousePos.x, &context.mousePos.y);
	}

	RootWidget root;

	Renderer renderer;
	Text::init(renderer.getSDLRenderer());

public:
	Window(float WINDOW_WIDTH_, float WINDOW_HEIGHT_)
	    : renderer(WINDOW_WIDTH_, WINDOW_HEIGHT_),
	{}

	void update() {
	}
};
} // namespace uii