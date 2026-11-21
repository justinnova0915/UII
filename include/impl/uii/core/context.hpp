// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include "impl/uii/core/styleSheet.hpp"
#include "renderer.hpp"
#include "text.hpp"
#include "input.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

namespace uii {
struct WindowContext {
	std::optional<Renderer> renderer;

	std::optional<FontManager> fontManager;

	std::optional<InputManager> input;

	StyleSheet styleSheet;
};
} // namespace uii