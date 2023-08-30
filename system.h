#pragma once


#include <SDL.h>

#include <memory>


class System {
public:
	//System();
	void system_init();
	void timer_setup();
	static float get_time();
	bool pump_events();
	void update();
	void render(SDL_Renderer*);

private:

	SDL_Event event;
	const float fps = 60.0f;
	float frame_start;
	float delta;
	float accumulator;


};