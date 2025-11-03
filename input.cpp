
#include <array>
#include <cstring>
#include <string>

#include "input.h"

//static const char* button_names[] = {
//
//	[0] = "UP",
//	[INPUT_KEY_DOWN] = "DOWN",
//	[INPUT_KEY_LEFT] = "LEFT",
//	[INPUT_KEY_RIGHT] = "RIGHT",
//	[INPUT_KEY_G] = "G",
//	[INPUT_KEY_X] = "X",
//	[INPUT_KEY_Z] = "Y"
//};


static std::array<int, button::INPUT_BUTTON_MAX> key_bindings;

//static bool key_bindings[button::INPUT_BUTTON_MAX];


void input_init() {
	input_clear_all_inputs();
}

void input_set_button_state(button button, float state) {
	key_bindings[button] = state;
}

void input_set_button_pressed(button button) {

	/*
	if (button < 0 || button > INPUT_BUTTON_MAX) {
		printf("Invaid button press\n");
		return;
	}
	*/

	key_bindings[button] = true;
}

void input_set_button_released(button button) {

	//if (button < 0 || button > INPUT_BUTTON_MAX) {
	//	return;
	//}

	key_bindings[button] = false;
}

bool input_state_button(button state) {
	return key_bindings[state];
}

void input_clear_all_inputs() {
	memset(&key_bindings[0], 0, sizeof(key_bindings));
}

const char* input_button_name(button button) {
	//return button_names[button];
	return nullptr;
}