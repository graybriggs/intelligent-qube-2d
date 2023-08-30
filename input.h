#pragma once

enum button {
	INPUT_KEY_LEFT = 0,
	INPUT_KEY_RIGHT = 1,
	INPUT_KEY_UP = 2,
	INPUT_KEY_DOWN = 3,
	INPUT_KEY_G = 4,
	INPUT_KEY_H = 5,
	INPUT_KEY_X = 6,
	INPUT_KEY_Z = 7,
	INPUT_KEY_SPACE = 8,

	INPUT_BUTTON_MAX = 9
};


void input_init();
void input_set_button_state(button button, float state);
void input_set_button_pressed(button button);
void input_set_button_released(button button);
bool input_state_button(button button);
void input_clear_all_inputs();
const char* input_button_name(button button);