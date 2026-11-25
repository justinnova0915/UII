// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "impl/uii/core/styleSheet.hpp"
#include "widget_base.hpp"
#include "text.hpp"
#include "renderer.hpp"
#include "input.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_mouse.h>
#include <iostream>
#include <optional>
#include <stdexcept>

namespace uii {
class Window {
private:
	// dingle berry
	WindowContext context;

	std::optional<RootWidget> root;

public:
	Window(float WINDOW_WIDTH_, float WINDOW_HEIGHT_) {
		StyleID rootStyleID = WidgetBase::registerStyle(context.styleSheet, { SDL_Color{ 0, 0, 0, 255 } });
		root.emplace(FRect{ 0, 0, WINDOW_WIDTH_, WINDOW_HEIGHT_ }, rootStyleID);
		context.renderer.emplace(WINDOW_WIDTH_, WINDOW_HEIGHT_);
		if (!context.renderer.has_value()) throw std::runtime_error("Renderer did NOT init 😭😭😭");
		context.fontManager.emplace(context.renderer->getSDLRenderer());
		if (!context.fontManager.has_value()) throw std::runtime_error("FontManager crashed :(");
		context.input.emplace();
		if (!context.input.has_value()) throw std::runtime_error("input crashed nooooooooo");
	}

	WindowContext& getContext() {
		return context;
	}

	RootWidget& getRootWidget() {
		return root.value();
	}

	void render() {
		context.renderer->clear({ 0, 0, 0, 255 });
		root->render(context);
		context.renderer->swap();
	}

	void update() {
		context.input->populate();
		root->update(context);
	}
};
} // namespace uii