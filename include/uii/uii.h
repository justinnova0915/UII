// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "impl/uii/core/core.hpp"
#include "impl/uii/widgets/widgets.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <stdexcept>

namespace uii {
inline void init() {
	if (!SDL_Init(SDL_INIT_VIDEO)) throw std::runtime_error("Failed to init SDL.");
	if (!TTF_Init()) throw std::runtime_error("Failed to init TTF.");
}
inline void quit() {
	SDL_Quit();
}
} // namespace uii