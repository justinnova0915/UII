// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "impl/uii/core/core.hpp"
#include "impl/uii/core/text.hpp"
#include "impl/uii/core/window.hpp"

namespace uii {
class LabelWidget : public WidgetBase {
private:
	Text m_text;

public:
	LabelWidget(FRect rect_, WindowContext& context, std::string text_, SDL_Color color_, std::string fontFile_, float size_)
	    : WidgetBase(rect_, context), m_text(context.fontManager.value(), fontFile_, size_, text_) {
		m_text.setColor(color_);
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
};
} // namespace uii