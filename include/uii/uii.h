// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "impl/uii/core/core.hpp"
#include "impl/uii/widgets/widgets.hpp"

namespace uii {
inline void init() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL Error: %s", SDL_GetError());
	}
}
} // namespace uii