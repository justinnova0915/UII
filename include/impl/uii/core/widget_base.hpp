// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "impl/uii/core/renderer.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

#include <stdexcept>
#include <unordered_map>
#include <vector>


namespace uii {
class ContainerWidgetBase;

class WidgetBase {
protected:
	FRect m_rect;

	ContainerWidgetBase* m_parent;

public:
	WidgetBase(FRect rect_)
	    : m_rect(rect_) {}

	virtual void render(Renderer& renderer) {
		renderer.renderRect(m_rect, styleSheet.color);
	}

	virtual void update() {
		return;
	}

	WidgetBase* getParent() {
		return m_parent;
	}

	void removeParent() {
		if (m_parent == nullptr) {
			throw std::runtime_error("Dawg there is no parent what are you doing");
		}

		m_parent->m_childs.erase(handle);
		m_parent = nullptr;
	}

	void setParent(ContainerWidgetBase* parent) {
		m_parent->addChild(handle, WidgetBase * child)
		    m_parent = parent;
	}

public:
	struct StyleSheet {
		SDL_Color color;
	} styleSheet;
};

class ContainerWidgetBase : WidgetBase {
private:
	std::string handle;

	ContainerWidgetBase* m_parent;
	std::unordered_map<std::string, WidgetBase*> m_childs;

public:
	void addChild(std::string handle, WidgetBase* child) {
		m_childs.insert({ handle, child });
	}

	void removeChild(std::string handle) {
		m_childs.erase(handle);
	}
};

class Widget : public WidgetBase {};
} // namespace uii