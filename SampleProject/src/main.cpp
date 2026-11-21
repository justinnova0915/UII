// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#include "impl/uii/core/styleSheet.hpp"
#include "impl/uii/core/widget_base.hpp"
#include "impl/uii/core/window.hpp"
#include "impl/uii/widgets/button.hpp"
#include "impl/uii/widgets/label.hpp"
#include "uii/uii.h"

#include "tx/resource.h"
#include <SDL3/SDL_log.h>
#include <utility>
#include <string>

int main() {
	uii::init();
	{
		uii::Window window(1600, 900);
		std::string FONT_PATH_JETBRAINS_MONO = tx::getExeDir() / "assets/JetBrainsMono-Regular.ttf";
		window.getContext().fontManager->font(FONT_PATH_JETBRAINS_MONO, 64);



		uii::LabelWidget label(uii::FRect(200, 100, 1600, 900), window.getContext(), "Hello", "label");
		int counter = 0;

		uii::WidgetBase::registerStyle(window.getContext().styleSheet, "base", uii::WidgetBase::BaseStyle{ .baseColor = { { 255, 255, 255, 255 } } });
		uii::LabelWidget::registerStyle(window.getContext().styleSheet, "label", uii::LabelWidget::LabelStyle{ .textColor = { { 255, 255, 255, 255 } }, .textFontPath = FONT_PATH_JETBRAINS_MONO, .textFontSize = 64 });
		uii::TextButtonWidget::registerStyle(window.getContext().styleSheet, "button", uii::TextButtonWidget::TextButtonStyle{ uii::ButtonWidget::ButtonWidgetStyle{ .hoverColor = { { 255, 255, 255, 255 } } }, .textColor = { { 255, 255, 255, 255 } }, .textFontPath = FONT_PATH_JETBRAINS_MONO, .textFontSize = 64 });
		uii::TextButtonWidget::registerStyle(window.getContext().styleSheet, "button", uii::TextButtonWidget::TextButtonStyle{ .textColor = { { 255, 255, 255, 255 } }, .textFontPath = FONT_PATH_JETBRAINS_MONO, .textFontSize = 64 });

		uii::TextButtonWidget clickButton(window.getContext(), uii::FRect(200, 500, 400, 200), { 0, 255, 255, 255 }, [&]() { counter++; }, "Hello", FONT_PATH_JETBRAINS_MONO, 64);
		uii::TextButtonWidget holdButton(window.getContext(), uii::FRect(800, 500, 400, 200), { 255, 0, 255, 255 }, [&]() { counter++; }, "Hello", FONT_PATH_JETBRAINS_MONO, 64);

		window.getRootWidget().addChild("label", &label);
		window.getRootWidget().addChild("button", &clickButton);
		window.getRootWidget().addChild("holdbutton", &holdButton);


		bool running = true;

		while (running) {
			window.update();
			window.render();
			label.setTextString(std::to_string(counter));
		}
	}
	uii::quit();
}