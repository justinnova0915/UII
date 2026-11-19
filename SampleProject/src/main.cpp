// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

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

		uii::LabelWidget label(uii::FRect(0, 0, 1600, 900), window.getContext(), "Hello", { 255, 255, 255, 255 },
		                       FONT_PATH_JETBRAINS_MONO, 64);
		int counter = 0;

		uii::ButtonWidget button(uii::FRect(200, 500, 400, 200), { 255, 255, 255, 255 }, [&]() { counter++; });

		window.getRootWidget().addChild("label", &label);
		window.getRootWidget().addChild("button", &button);

		bool running = true;

		while (running) {
			window.update();
			window.render();
			label.setTextString(std::to_string(counter));
		}
	}
	uii::quit();
}