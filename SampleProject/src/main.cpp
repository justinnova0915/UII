// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#include "impl/uii/core/window.hpp"
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

		window.getRootWidget().addChild("label", &label);

		bool running = true;

		SDL_Event event;

		int counter = 0;
		SDL_Log("Video driver: %s", SDL_GetCurrentVideoDriver());
		while (running) {
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_EVENT_QUIT) {
					running = false;
				}
			}

			window.render();
			window.update();
			label.setTextString(std::to_string(counter));
			counter++;
		}
	}
	uii::quit();
}