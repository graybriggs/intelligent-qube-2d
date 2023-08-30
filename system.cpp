

#include "system.h"

#include "game.h"


void System::system_init() {

	init_game();

}

void System::timer_setup() {

	delta = 1.0f / fps; // fixed timestep of 1/60th of a second
	accumulator = 0.0f;
	frame_start = get_time();
}

float System::get_time() {
	return static_cast<float>(SDL_GetTicks());
}


bool System::pump_events() {
	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {
			//done = true;
			return true;
		}
	}

	return false;
}


void System::update() {

	float current_time = get_time();
	delta =  current_time - frame_start;
	frame_start = current_time;

	if (accumulator > 0.2f)
		accumulator = 0.2f;

	//while (accumulator > delta) {

		update_game(delta);

		accumulator -= delta;

	//}

}


void System::render(SDL_Renderer* renderer) {

	//clear_screen(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	render_game(renderer);

	SDL_RenderPresent(renderer);
}