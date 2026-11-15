// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.
#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <vector>

#include "widget_base.hpp"
#include "renderer.hpp"

namespace uii {
class Screen {
private:
	std::vector<WidgetBase*> m_elements;

public:
	Screen(std::vector<WidgetBase*> elements_)
	    : m_elements(elements_) {}

	void addElement(WidgetBase* e) {
		m_elements.push_back(e);
	}

	void render(Renderer& renderer) {
		for (WidgetBase* e : m_elements) {
			e->render(renderer);
		}
	}
	/**
     * @brief hello twin
     */
	void update() {
		for (WidgetBase* e : m_elements) {
			e->update();
		}
	}
};
} // namespace uii