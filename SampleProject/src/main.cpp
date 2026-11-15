// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#include "impl/io_file.hpp"
#include "impl/uii/core/renderer.hpp"
#include "impl/uii/core/text.hpp"
#include "impl/uii/infrastructure/geometry.hpp"
#include "uii/uii.h"

#include "tx/resource.h"

int main() {
	uii::init();
	{
		uii::Renderer rr(1600, 900);
		uii::Text::init(rr.getSDLRenderer());

		uii::Label l(uii::FRect(0, 0, 1600, 900), "Hello", { 255, 255, 255, 255 },
		             tx::getExeDir() / "assets/JetBrainsMono-Regular.ttf", 64);


		bool running = true;
		SDL_Event event;

		while (running) {
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_EVENT_QUIT) {
					running = false;
				}
			}

			rr.clear({ 0, 0, 0, 255 });

			l.render(rr);

			rr.swap();
		}
		uii::Text::quit();
	}
	uii::quit();
}