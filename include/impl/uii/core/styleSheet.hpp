// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include <optional>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>

namespace uii {

struct Style {

	// base
	std::optional<SDL_Color> baseColor;

	// Text
	std::optional<std::string> textFontPath;
	std::optional<float> textFontSize;
	std::optional<SDL_Color> textColor;
};

struct StyleSheet {
	SDL_Color color;
};
} // namespace uii