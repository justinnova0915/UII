// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include <format>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <vector>

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

	void mergeWith(MasterStyle& override) {
		if (override.baseColor) baseColor = override.baseColor;
		if (override.hoverColor) hoverColor = override.hoverColor;
		if (override.textFontPath) textFontPath = override.textFontPath;
		if (override.textFontSize) textFontSize = override.textFontSize;
		if (override.textColor) textColor = override.textColor;
	}
};

enum class StyleID : int { Invalid = -1 };

class StyleSheet {
private:
	struct StyleEntry {
		StyleID parentHandle;
		MasterStyle masterStyle;
	};

	std::vector<MasterStyle> masterStyle;


public:
	StyleID setStyle(StyleID parentID, MasterStyle style) {
		MasterStyle result = this->getStyle(parentID);
		result.mergeWith(style);

		masterStyle.push_back(result);
		return StyleID{ static_cast<StyleID>(masterStyle.size() - 1) };
	}

	MasterStyle getStyle(StyleID handle) {
		if (handle == StyleID::Invalid) {
			return MasterStyle{};
		}

		int handleInt = static_cast<int>(handle);

		if (handleInt > masterStyle.size()) {
			throw std::runtime_error(std::format("Specified style \"{}\" doesn't exist!", handleInt));
		}

		return masterStyle[handleInt];
	}
};
} // namespace uii