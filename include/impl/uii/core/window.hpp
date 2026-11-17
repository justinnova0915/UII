// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "widget_base.hpp"
#include "text.hpp"
#include "renderer.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_mouse.h>
#include <iostream>
#include <optional>

namespace uii {
class Window {
private:
	// dingle berry
	WindowContext context;

	RootWidget root;

public:
	Window(float WINDOW_WIDTH_, float WINDOW_HEIGHT_)
	    : root({ 0, 0, WINDOW_WIDTH_, WINDOW_HEIGHT_ }, context) {
		context.renderer.emplace(WINDOW_WIDTH_, WINDOW_HEIGHT_);
		if (!context.renderer.has_value()) std::cout << "AHHH\n";
		context.fontManager.emplace(context.renderer->getSDLRenderer());
		if (!context.fontManager.has_value()) std::cout << "AHHH\n";
	}

	WindowContext& getContext() {
		return context;
	}

	RootWidget& getRootWidget() {
		return root;
	}

	void render() {
		context.renderer->clear({ 0, 0, 0, 255 });
		root.render(context);
		context.renderer->swap();
	}

	void update() {
		root.update(context);
	}
};
} // namespace uii