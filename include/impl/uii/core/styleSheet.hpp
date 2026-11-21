// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include <optional>
#include <stdexcept>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <unordered_map>

namespace uii {

// one Style to rule them all >:)
struct MasterStyle {

	// Base
	std::optional<SDL_Color> baseColor;

	// Button
	std::optional<SDL_Color> hoverColor;

	// Text
	std::optional<std::string> textFontPath;
	std::optional<float> textFontSize;
	std::optional<SDL_Color> textColor;
};

class StyleSheet {
private:
	std::unordered_map<std::string, MasterStyle> masterStyle;

public:
	void setStyle(std::string styleName, MasterStyle style) {
		masterStyle.insert({ styleName, style });
	}

	MasterStyle getStyle(std::string handle) {
		if (masterStyle.find(handle) == masterStyle.end()) {
			throw std::runtime_error("Specified style \"" + handle + "\" doesn't exist!");
		}

		return masterStyle.find(handle)->second;
	}
};
} // namespace uii