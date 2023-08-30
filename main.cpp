



#include <SDL.h>
//#include <SDL_ttf.h>

#include <ctime>
#include <memory>

#include "input.h"
#include "system.h"

constexpr int SCREEN_WIDTH = 1200;
constexpr int SCREEN_HEIGHT = 750;

SDL_Renderer* setup_platform() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	//TTF_Init();
	SDL_Window* window = window = SDL_CreateWindow(
		"Intelligent Qube (2D ver.)",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	return renderer;
}

bool input_pump_events() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			//app_done = true;
			return true;
		}

		if (event.type == SDL_KEYDOWN) {
			//int code = event.key.keysym.scancode;
			int code = event.key.keysym.sym;

			int internal_code = code;
			//printf("%X | %d\n", code, internal_code);
			switch (code) {
			case SDLK_SPACE:
				input_set_button_pressed(INPUT_KEY_SPACE);
				break;
			case SDLK_LEFT:
				input_set_button_pressed(INPUT_KEY_LEFT);
				break;
			case SDLK_RIGHT:
				input_set_button_pressed(INPUT_KEY_RIGHT);
				break;
			case SDLK_UP:
				input_set_button_pressed(INPUT_KEY_UP);
				break;
			case SDLK_DOWN:
				input_set_button_pressed(INPUT_KEY_DOWN);
				break;
			case SDLK_g:
				input_set_button_pressed(INPUT_KEY_G);
				break;
			case SDLK_h:
				input_set_button_pressed(INPUT_KEY_H);
				break;
			case SDLK_x:
				input_set_button_pressed(INPUT_KEY_X);
				break;
			case SDLK_z:
				input_set_button_pressed(INPUT_KEY_Z);
				break;

			}
		}
		else if (event.type == SDL_KEYUP) {
			//int code = event.key.keysym.scancode;
			int code = event.key.keysym.sym;
			int internal_code = code;
			//printf("%X | %d\n", code, internal_code);
			//input_set_button_released(internal_code);
			switch (code) {
			case SDLK_SPACE:
				input_set_button_released(INPUT_KEY_SPACE);
				break;
			case SDLK_LEFT:
				input_set_button_released(INPUT_KEY_LEFT);
				break;
			case SDLK_RIGHT:
				input_set_button_released(INPUT_KEY_RIGHT);
				break;
			case SDLK_UP:
				input_set_button_released(INPUT_KEY_UP);
				break;
			case SDLK_DOWN:
				input_set_button_released(INPUT_KEY_DOWN);
				break;
			case SDLK_g:
				input_set_button_released(INPUT_KEY_G);
				break;
			case SDLK_h:
				input_set_button_released(INPUT_KEY_H);
				break;
			case SDLK_x:
				input_set_button_released(INPUT_KEY_X);
				break;
			case SDLK_z:
				input_set_button_released(INPUT_KEY_Z);
				break;

			}
		}
	}
}


int main(int argc, char* argv[]) {

	srand((unsigned int)time(nullptr));

	SDL_Renderer* renderer = setup_platform();

	auto system = std::make_unique<System>();
	system->system_init();
	system->timer_setup();

	bool done = false;

	while (!done) {
		//done = system->pump_events();
		done = input_pump_events();
		system->update();
		system->render(renderer);

	}
	SDL_Quit();

	return 0;
}
