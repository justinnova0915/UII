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

		int counter = 0;

		uii::WidgetBase::registerStyle(
		    window.getContext().styleSheet,
		    "base",
		    uii::WidgetBase::BaseStyle{
		        .baseColor = { { 255, 255, 255, 255 } } });
		uii::LabelWidget::registerStyle(
		    window.getContext().styleSheet,
		    "base", "label",
		    uii::LabelWidget::LabelStyle{
		        {},
		        FONT_PATH_JETBRAINS_MONO,
		        64,
		        { { 255, 255, 255, 255 } } });
		uii::TextButtonWidget::registerStyle(
		    window.getContext().styleSheet,
		    "button", "base",
		    uii::TextButtonWidget::TextButtonStyle{
		        uii::ButtonWidget::ButtonWidgetStyle{
		            uii::WidgetBase::BaseStyle{
		                { { 0, 255, 255, 255 } } },
		            { { 255, 0, 0, 255 } } },
		        FONT_PATH_JETBRAINS_MONO,
		        64,
		        { { 255, 255, 255, 255 } } });
		uii::TextButtonWidget::registerStyle(
		    window.getContext().styleSheet,
		    "idkbutton", "base",
		    uii::TextButtonWidget::TextButtonStyle{
		        uii::ButtonWidget::ButtonWidgetStyle{
		            uii::WidgetBase::BaseStyle{
		                { { 255, 0, 255, 255 } } },
		            { { 255, 0, 0, 255 } } },
		        FONT_PATH_JETBRAINS_MONO,
		        64,
		        { { 255, 255, 255, 255 } } });

		uii::LabelWidget label(uii::FRect(200, 100, 1600, 900), window.getContext(), "Hello", "label");


		uii::TextButtonWidget clickButton(window.getContext(), "button", "Button 1", uii::FRect(200, 500, 400, 200), [&]() { counter++; });
		uii::TextButtonWidget holdButton(window.getContext(), "button", "Button 2", uii::FRect(800, 500, 400, 200), [&]() { counter++; });

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