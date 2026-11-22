// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "impl/uii/core/core.hpp"
#include "impl/uii/core/styleSheet.hpp"
#include "impl/uii/core/text.hpp"
#include "impl/uii/core/widget_base.hpp"
#include "impl/uii/core/window.hpp"

namespace uii {
class LabelWidget : public WidgetBase {
private:
	Text m_text;
	std::string m_styleHandle;

public:
	LabelWidget(FRect rect_, WindowContext& context_, std::string text_, std::string styleHandle_)
	    : WidgetBase(rect_, styleHandle_),
	      m_text(context_.fontManager.value(),
		         context_.styleSheet.getStyle(styleHandle_).textFontPath.value(),
		         context_.styleSheet.getStyle(styleHandle_).textFontSize.value(),
		         text_) {
		m_text.setColor(context_.styleSheet.getStyle(styleHandle_).textColor.value());
	}

	void render(WindowContext& context) override {
		m_text.render(m_rect.pos());
	}

	// ================ Text Associated Interface Exposure ================

	void setTextColor(SDL_Color color) { m_text.setColor(color); }
	SDL_Color getTextColor() { return m_text.getColor(); }

	void setTextString(std::string_view text) { m_text.setText(text); }
	std::string_view getTextString() { return m_text.getText(); }

	void setTextFont(std::string_view fileName, float size) { m_text.setFont(fileName, size); }

	SDL_FPoint getTextSize() { return m_text.getSize(); }

public:
	struct LabelStyle : WidgetBase::BaseStyle {
		std::optional<std::string> textFontPath;
		std::optional<float> textFontSize;
		std::optional<SDL_Color> textColor;

		MasterStyle toMaster() {
			MasterStyle baseStyle = WidgetBase::BaseStyle::toMaster();
			baseStyle.textFontPath = textFontPath;
			baseStyle.textFontSize = textFontSize;
			baseStyle.textColor = textColor;

			return baseStyle;
		}
	};

	static void validate(MasterStyle style) {
		WidgetBase::validate(style);

		if (!style.textFontPath) throw std::runtime_error("textFontPath not defined!");
		if (!style.textFontSize) throw std::runtime_error("textFontSize not defined!");
		if (!style.textColor) throw std::runtime_error("textColor not defined!");
	}


	static void registerStyle(StyleSheet& sheet, std::string parentHandle, std::string handle, LabelStyle style) {
		validate(sheet.setStyle(handle, parentHandle, style.toMaster()));
	}
};
} // namespace uii