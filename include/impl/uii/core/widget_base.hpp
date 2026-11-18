// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "impl/uii/core/renderer.hpp"
#include "context.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

#include <stdexcept>
#include <unordered_map>
#include <vector>


namespace uii {

class RootWidget;

class WidgetBase {
protected:
	std::string m_handle;

	FRect m_rect;

	WindowContext* context;

	WidgetBase* m_parent = nullptr;
	std::unordered_map<std::string, WidgetBase*> m_childs;

public:
	WidgetBase(FRect rect_, WindowContext& context_)
	    : m_rect(rect_), context(&context_) {}

	virtual void render(WindowContext& context) {
		context.renderer->renderRect(m_rect, styleSheet.color);
		for (auto i : m_childs) {
			i.second->render(context);
		}
	}

	virtual void update(WindowContext& context) {
		for (auto i : m_childs) {
			i.second->update(context);
		}
	}

	WidgetBase* getParent() {
		return m_parent;
	}

	void removeParent() {
		if (m_parent == nullptr) {
			throw std::runtime_error("Dawg there is no parent what are you doing");
		}

		m_parent->removeChild(m_handle);
		m_parent = nullptr;
	}

	void addChild(std::string handle, WidgetBase* child) {
		if (!child) {
			SDL_Log("Warning: Child is null!");
			return;
		}

		if (child == this) {
			SDL_Log("Warning: Trying to parent to self!");
			return;
		}

		if (child->m_parent != nullptr) {
			child->removeParent();
		}

		child->m_handle = handle;
		m_childs.insert({ handle, child });
		child->m_parent = this;
	}

	void addChild(std::string handle, RootWidget* child) = delete;

	void removeChild(std::string handle) {
		if (m_childs.find(handle) == m_childs.end()) {
			SDL_Log("Warning: Child with handle %s not found!", handle.c_str());
			return;
		}

		m_childs.find(handle)->second->m_parent = nullptr;
		m_childs.erase(handle);
	}

public:
	struct StyleSheet {
		SDL_Color color;
	} styleSheet;
};
class RootWidget : public WidgetBase {
public:
	using WidgetBase::WidgetBase;
	void removeParent() = delete;
};
} // namespace uii