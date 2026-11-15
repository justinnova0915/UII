// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <cstdint>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <utility>

namespace uii {

// ======================================================
// **************** Text & Font Managing ****************
// ======================================================

class Text {
private:
	class FontManager {
	private:
		struct FontKeyHash {
			using is_transparent = void;
			std::size_t operator()(const std::pair<std::string, float>& k) const noexcept {
				std::size_t h1 = std::hash<std::string>{}(k.first);
				std::size_t h2 = std::hash<float>{}(k.second);
				// Standard hash combining technique (from Boost)
				return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
			}
			std::size_t operator()(const std::pair<std::string_view, float>& k) const noexcept {
				std::size_t h1 = std::hash<std::string_view>{}(k.first);
				std::size_t h2 = std::hash<float>{}(k.second);
				// Standard hash combining technique (from Boost)
				return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
			}
		};

		TTF_TextEngine* m_engine = nullptr;
		std::unordered_map<
		    std::pair<std::string, float>, TTF_Font*,
		    FontKeyHash, std::equal_to<>>
		    m_fonts;

	public:
		FontManager(SDL_Renderer* renderer)
		    : m_engine(TTF_CreateRendererTextEngine(renderer)) {}

		~FontManager() {
			for (auto font : m_fonts) {
				TTF_CloseFont(font.second);
			}

			TTF_DestroyRendererTextEngine(m_engine);
		}

		TTF_Font* font(std::string_view fileName, float size) {
			if (!std::filesystem::exists(fileName)) {
				throw std::runtime_error("Text: Specified path does not exist!");
			}

			auto it = m_fonts.find(std::pair<std::string_view, float>(fileName, size));

			if (it == m_fonts.end()) { // not found; lazy caching
				return m_fonts.insert({ { std::string(fileName), size },
				                        TTF_OpenFont(fileName.data(), size) })
				    .first->second;
			} else {
				return it->second;
			}
		}

		TTF_Text* text(std::string_view fileName, float size, std::string_view text) {
			return TTF_CreateText(m_engine, font(fileName, size), text.data(), 0);
		}
	};

private:
	inline static std::optional<FontManager> fontManager;
	TTF_Text* m_text;

public:
	static void init(SDL_Renderer* renderer) {
		if (!TTF_Init()) throw std::runtime_error("Failed to init TTF.");
		// FontManager contructor
		fontManager.emplace(renderer);
	}
	static void quit() {
		fontManager.reset();
		TTF_Quit();
	}

public:
	Text(std::string_view fileName, float size, std::string_view text)
	    : m_text(fontManager->text(fileName, size, text)) {}

	~Text() {
		TTF_DestroyText(m_text);
	}

	void setColor(SDL_Color color) {
		TTF_SetTextColor(m_text, color.r, color.g, color.b, color.a);
	}

	SDL_Color getColor() {
		uint8_t r, g, b, a;
		TTF_GetTextColor(m_text, &r, &g, &b, &a);
		return { r, g, b, a };
	}

	void setText(std::string_view text) {
		TTF_SetTextString(m_text, text.data(), 0);
	}

	std::string_view getText() {
		return std::string_view(m_text->text);
	}

	void setFont(std::string_view fileName, float size) {
		TTF_SetTextFont(m_text, fontManager->font(fileName, size));
	}

	SDL_FPoint getSize() {
		int w, h;
		TTF_GetTextSize(m_text, &w, &h);
		return { static_cast<float>(w), static_cast<float>(h) };
	}

	void render(SDL_FPoint pos) {
		TTF_DrawRendererText(m_text, pos.x, pos.y);
	}
};
} // namespace uii