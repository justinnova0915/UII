// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_rect.h>
#include <vector>

namespace uii {

class InputManager {
private:
	std::vector<SDL_Event> m_events;

public:
	InputManager() = default;

	enum class MouseButtons {
		LEFT,
		RIGHT,
		MIDDLE,
		COUNT
	};


	void populate() {
		m_events.clear();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			m_events.push_back(event);
		}
	}

	SDL_FPoint getMousePos() {
		float x, y;
		SDL_GetMouseState(&x, &y);
		return { x, y };
	}

	bool isMouseDown(MouseButtons button) {
		// Gets a bitmask of all the input buttons,
		// then AND them to get the exact queried button state.
		SDL_MouseButtonFlags inputMask = SDL_GetMouseState(nullptr, nullptr);
		switch (button) {
		case MouseButtons::LEFT:
			return (inputMask & SDL_BUTTON_LMASK);
		case MouseButtons::MIDDLE:
			return (inputMask & SDL_BUTTON_MMASK);
		case MouseButtons::RIGHT:
			return (inputMask & SDL_BUTTON_RMASK);
		case MouseButtons::COUNT:
			SDL_Log("Count is not a button twin...");
		}

		return false;
	}

	bool isMousePressed(MouseButtons button) {
		int targetButton = 0;
		switch (button) {
		case MouseButtons::LEFT:
			targetButton = SDL_BUTTON_LEFT;
			break;
		case MouseButtons::MIDDLE:
			targetButton = SDL_BUTTON_MIDDLE;
			break;
		case MouseButtons::RIGHT:
			targetButton = SDL_BUTTON_RIGHT;
			break;
		case MouseButtons::COUNT:
			SDL_Log("Count is not a button twin...");
			break;
		}

		for (SDL_Event event : m_events) {
			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == targetButton) {
				return true;
			}
		}

		return false;
	}
};
} // namespace uii