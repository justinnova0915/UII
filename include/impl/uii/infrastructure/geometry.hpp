// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include <SDL3/SDL_rect.h>
#include <cmath>

// ========================================================
// **************** Basic Geometry Utility ****************
// ========================================================
namespace uii {

// ################ Rect ################

struct FRect;
struct DRect {
	int x = 0, y = 0, w = 0, h = 0;

	constexpr DRect() = default;

	// xywh constructor
	constexpr DRect(int x_, int y_, int w_, int h_)
	    : x(x_), y(y_), w(w_), h(h_) {}

	// pos-dim constructor
	constexpr DRect(SDL_Point pos_, SDL_Point dim_)
	    : x(pos_.x), y(pos_.y), w(dim_.x), h(dim_.y) {}

	// SDL_Rect constructor
	constexpr DRect(const SDL_Rect& r)
	    : x(r.x), y(r.y), w(r.w), h(r.h) {}

	[[nodiscard]] constexpr SDL_Rect rect() const { return { x, y, w, h }; }

	[[nodiscard]] constexpr SDL_Point pos() const { return { x, y }; }
	[[nodiscard]] constexpr SDL_Point dim() const { return { w, h }; }
	[[nodiscard]] constexpr SDL_Point center() const { return { x + w / 2, y + h / 2 }; }

	[[nodiscard]] constexpr SDL_Point topLeft() const { return { x, y }; }
	[[nodiscard]] constexpr SDL_Point topRight() const { return { x + w, y }; }
	[[nodiscard]] constexpr SDL_Point bottomLeft() const { return { x, y + h }; }
	[[nodiscard]] constexpr SDL_Point bottomRight() const { return { x + w, y + h }; }

	[[nodiscard]] constexpr FRect toRect() const;
};

struct FRect {
	float x = 0.0f, y = 0.0f, w = 0.0f, h = 0.0f;

	constexpr FRect() = default;

	// xywh constructor
	constexpr FRect(float x_, float y_, float w_, float h_)
	    : x(x_), y(y_), w(w_), h(h_) {}

	// pos-dim constructor
	constexpr FRect(SDL_FPoint pos_, SDL_FPoint dim_)
	    : x(pos_.x), y(pos_.y), w(dim_.x), h(dim_.y) {}

	constexpr FRect(const SDL_FRect& r)
	    : x(r.x), y(r.y), w(r.w), h(r.h) {}

	[[nodiscard]] constexpr SDL_FRect rect() const { return { x, y, w, h }; }

	[[nodiscard]] constexpr SDL_FPoint pos() const { return { x, y }; }
	[[nodiscard]] constexpr SDL_FPoint dim() const { return { w, h }; }
	[[nodiscard]] constexpr SDL_FPoint center() const { return { x + w / 2.0f, y + h / 2.0f }; }

	[[nodiscard]] constexpr SDL_FPoint topLeft() const { return { x, y }; }
	[[nodiscard]] constexpr SDL_FPoint topRight() const { return { x + w, y }; }
	[[nodiscard]] constexpr SDL_FPoint bottomLeft() const { return { x, y + h }; }
	[[nodiscard]] constexpr SDL_FPoint bottomRight() const { return { x + w, y + h }; }

	[[nodiscard]] DRect toDRect() const {
		return DRect(
		    static_cast<int>(std::floor(x)),
		    static_cast<int>(std::floor(y)),
		    static_cast<int>(std::floor(w)),
		    static_cast<int>(std::floor(h)));
	}
};

inline constexpr FRect DRect::toRect() const {
	return FRect(
	    static_cast<float>(x),
	    static_cast<float>(y),
	    static_cast<float>(w),
	    static_cast<float>(h));
}
} // namespace uii