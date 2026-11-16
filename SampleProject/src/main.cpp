// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#include "uii/uii.h"

#include "tx/resource.h"
#include <utility>
#include <string>

int main() {
	uii::init();
	{
		uii::Renderer renderer(1600, 900);
		uii::Text::init(renderer.getSDLRenderer());

		std::string FONT_PATH_JETBRAINS_MONO = tx::getExeDir() / "assets/JetBrainsMono-Regular.ttf";

		uii::LabelWidget label(uii::FRect(0, 0, 1600, 900), "Hello", { 255, 255, 255, 255 },
		                       FONT_PATH_JETBRAINS_MONO, 64);

		bool running = true;
		uii::Context context;

		int counter = 0;
		while (running) {
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_EVENT_QUIT) {
					running = false;
				}
			}

			renderer.clear({ 0, 0, 0, 255 });

			label.render(renderer);
			label.setTextString(std::to_string(counter));
			counter++;

			renderer.swap();
		}
		uii::Text::quit();
	}
	uii::quit();
}