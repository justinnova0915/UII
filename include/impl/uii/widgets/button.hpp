// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once

#include "impl/uii/core/context.hpp"
#include "impl/uii/core/core.hpp"
#include "impl/uii/core/input.hpp"
#include "impl/uii/core/styleSheet.hpp"
#include "impl/uii/core/text.hpp"
#include "impl/uii/core/widget_base.hpp"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <functional>


namespace uii {
class ButtonWidgetBase : public WidgetBase {
private:
	std::function<void()> m_callBack;

public:
	ButtonWidgetBase(FRect rect_, std::string styleHandle_, std::function<void()> callback_)
	    : WidgetBase(rect_, styleHandle_), m_callBack(callback_) {}

	void update(WindowContext& context) override {
		if (isHovered(context)) {

			if (context.input->isMousePressed(InputManager::MouseButtons::LEFT)) {
				onPressed();
			}
		}
	}

	void render(WindowContext& context) override {
		if (isHovered(context)) {
			context.renderer->renderRect(m_rect, context.styleSheet.getStyle(m_styleHandle).hoverColor.value());
		} else {
			context.renderer->renderRect(m_rect, context.styleSheet.getStyle(m_styleHandle).baseColor.value());
		}
	}

	void onPressed() {
		m_callBack();
	}

	void setCallback(std::function<void()> callback) {
		m_callBack = callback;
	}

public:
	struct ButtonWidgetStyle : WidgetBase::BaseStyle {
		std::optional<SDL_Color> hoverColor;

		MasterStyle toMaster() {
			MasterStyle baseStyle = BaseStyle::toMaster();
			baseStyle.hoverColor = hoverColor;

			return baseStyle;
		}
	};
};

class ButtonWidget : public ButtonWidgetBase {
public:
	ButtonWidget(FRect rect_, std::string styleHandle_, std::function<void()> callback_)
	    : ButtonWidgetBase(rect_, styleHandle_, callback_) {}

public:
	static void validate(MasterStyle style) {
		WidgetBase::validate(style);
		if (!style.hoverColor) throw std::runtime_error("hoverColor not defined!");
	}

	static void registerStyle(StyleSheet& sheet, std::string handle, std::string parentHandle, ButtonWidgetStyle style) {
		MasterStyle resolved = style.toMaster();
		validate(sheet.setStyle(handle, parentHandle, resolved));
	}
};

class TextButtonWidget : public ButtonWidgetBase {
private:
	Text m_text;

public:
	TextButtonWidget(WindowContext& context_, std::string styleHandle_, std::string text_, FRect rect_, std::function<void()> callback_)
	    : ButtonWidgetBase(rect_, styleHandle_, callback_),
	      m_text(context_.fontManager.value(),
		         context_.styleSheet.getStyle(styleHandle_).textFontPath.value(),
		         context_.styleSheet.getStyle(styleHandle_).textFontSize.value(),
		         text_) {
		m_text.setColor(context_.styleSheet.getStyle(styleHandle_).textColor.value());
	}

	void render(WindowContext& context) override {
		ButtonWidgetBase::render(context);
		m_text.render(m_rect.topLeft());
	}

public:
	struct TextButtonStyle : ButtonWidgetBase::ButtonWidgetStyle {
		std::optional<std::string> textFontPath;
		std::optional<float> textFontSize;
		std::optional<SDL_Color> textColor;

		MasterStyle toMaster() {
			MasterStyle baseStyle = ButtonWidgetBase::ButtonWidgetStyle::toMaster();
			baseStyle.textFontPath = textFontPath;
			baseStyle.textFontSize = textFontSize;
			baseStyle.textColor = textColor;

			return baseStyle;
		}
	};

	static void validate(MasterStyle style) {
		ButtonWidget::validate(style);

		if (!style.textFontPath) throw std::runtime_error("textFontPath not defined!");
		if (!style.textFontSize) throw std::runtime_error("textFontSize not defined!");
		if (!style.textColor) throw std::runtime_error("textColor not defined!");
	}

	static void registerStyle(StyleSheet& sheet, std::string handle, std::string parentHandle, TextButtonStyle style) {
		validate(sheet.setStyle(handle, parentHandle, style.toMaster()));
	}
};

} // namespace uii