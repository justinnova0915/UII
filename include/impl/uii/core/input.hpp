// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_rect.h>

namespace uii {

class InputManager {
private:
	SDL_Event event;

public:
	InputManager() = default;

	enum class MouseButtons {
		LEFT,
		RIGHT,
		MIDDLE,
		COUNT
	};


	void populate() {
		SDL_PollEvent(&event);
	}

	SDL_FPoint getMousePos() {
		float x, y;
		SDL_GetMouseState(&x, &y);
		return { x, y };
	}

	bool isMouseDown(MouseButtons button) {
		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			switch (button) {
			case MouseButtons::LEFT:
				if (event.button.button == SDL_BUTTON_LEFT) return true;
			case MouseButtons::MIDDLE:
				if (event.button.button == SDL_BUTTON_MIDDLE) return true;
			case MouseButtons::RIGHT:
				if (event.button.button == SDL_BUTTON_RIGHT) return true;
			case MouseButtons::COUNT:
				SDL_Log("Count is not a button twin...");
			}
		}

		return false;
	}
};
} // namespace uii