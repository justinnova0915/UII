// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>

namespace uii {
struct Context {
	SDL_FPoint mousePos;

	SDL_Event event;
};
} // namespace uii