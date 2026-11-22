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

	void mergeWith(MasterStyle& override) {
		if (override.baseColor) baseColor = override.baseColor;
		if (override.hoverColor) hoverColor = override.hoverColor;
		if (override.textFontPath) textFontPath = override.textFontPath;
		if (override.textFontSize) textFontSize = override.textFontSize;
		if (override.textColor) textColor = override.textColor;
	}
};

class StyleSheet {
private:
	struct StyleEntry {
		std::string parentHandle;
		MasterStyle masterStyle;
	};

	std::unordered_map<std::string, StyleEntry> masterStyle;


public:
	StyleSheet(const StyleSheet&) = delete;
	StyleSheet() {
		std::cout << "aa\n";
	};
	MasterStyle setStyle(std::string styleName, std::string parentHandle_, MasterStyle style) {
		MasterStyle result = this->getStyle(parentHandle_);
		result.mergeWith(style);

		masterStyle.insert({ styleName, { parentHandle_, result } });
		return result;
	}

	MasterStyle getStyle(std::string handle) {
		if (handle == "fkfkdshglfu") {
			return MasterStyle{};
		}

		if (masterStyle.find(handle) == masterStyle.end()) {
			throw std::runtime_error(std::format("Specified style \"{}\" doesn't exist!", handle));
		}

		return masterStyle.find(handle)->second.masterStyle;
	}
};
} // namespace uii