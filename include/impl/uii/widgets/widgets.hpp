// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include <SDL3/SDL_rect.h>
namespace uii {
struct Rect {
	float x = 0.0f, y = 0.0f, w = 0.0f, h = 0.0f;

	// xywh contructor
	constexpr Rect(float x_, float y_, float w_, float h_)
	    : x(x_), y(y_), w(w_), h(h_) {}

	// pos-dim constructor
	constexpr Rect(SDL_FPoint pos_, SDL_FPoint dim_)
	    : x(pos_.x), y(pos_.y), w(dim_.x), h(dim_.y) {}

	[[nodiscard]]
	constexpr SDL_FPoint getPos() const { return { x, y }; }

	[[nodiscard]]
	//Using SDL_FPoint, but represents dimensions in this context
	constexpr SDL_FPoint getDim() const { return { w, h }; }

	[[nodiscard]]
	constexpr SDL_FRect getRect() const { return { x, y, w, h }; }

	[[nodiscard]]
	constexpr SDL_FPoint getCenter() const { return { x + w / 2, y + h / 2 }; }
};
} // namespace uii