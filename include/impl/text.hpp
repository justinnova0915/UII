// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include "renderer.hpp"
#include "element.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <filesystem>

namespace uii {

// ======================================================
// **************** Text & Font Managing ****************
// ======================================================

class Text {
public:
private:
	class FontManager {
	public:
		FontManager(SDL_Renderer* renderer)
		    : m_engine(TTF_CreateRendererTextEngine(renderer)) {}



	private:
		TTF_TextEngine* m_engine = nullptr;
	};

private:
	static std::optional<FontManager> fontManager;

public:
	static void init(SDL_Renderer* renderer) {
		if (!TTF_Init()) throw std::runtime_error("Failed to init TTF.");
		fontManager.emplace(renderer);
	}
};

// Wrapper for SDL3_ttf
class FontManager {
private:
	TTF_TextEngine* m_engine = nullptr;
	std::unordered_map<std::string, TTF_Font*> m_fonts;

	Renderer& m_renderer;

public:
	// Constructor
	FontManager(Renderer& renderer_)
	    : m_renderer(renderer_) {
		if (!TTF_Init()) throw std::runtime_error("Failed to init TTF.");



		m_engine = TTF_CreateRendererTextEngine(m_renderer.getSDLRenderer());
	}


	void createFont(std::string handle, std::string path, float size) {
		if (!std::filesystem::exists(path)) {
			throw std::runtime_error("Text: Specified path does not exist!");
		}

		m_fonts[handle] = TTF_OpenFont(path.c_str(), size);
	}

	void changeFontSize(std::string handle, float size) {
		if (m_fonts.find(handle) == m_fonts.end()) {
			throw std::runtime_error("Text: Specified font does not exist!");
		}

		TTF_SetFontSize(m_fonts[handle], size);
	}

	TTF_Text* createText(std::string fontHandle, std::string text) {
		if (m_fonts.find(fontHandle) == m_fonts.end()) {
			throw std::runtime_error("Text: Specified font does not exist!");
		}

		return TTF_CreateText(m_engine, m_fonts[fontHandle], text.c_str(), 0);
	}
};

class Label : public BaseElement {
private:
	TTF_Text* m_text;
	SDL_FPoint m_pos;

public:
	Label(std::string text_, SDL_Color color_, SDL_FPoint pos_, std::string fontHandle_, FontManager& fontManager_)
	    : m_pos(pos_) {
		m_text = fontManager_.createText(fontHandle_, text_);
	}

	void changeColor(SDL_Color color) {
		TTF_SetTextColor(m_text, color.r, color.g, color.b, color.a);
	}

	void update() override {
	}

	void render(Renderer& renderer) override {
		renderer.renderText(m_text, m_pos);
	}
};
} // namespace uii