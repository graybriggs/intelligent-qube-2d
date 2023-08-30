#pragma once

#include "base.h"

// For every forbidden cube captured, the player will lose
// the final row of the stage

// When a player captures the advantage cube the surrounding
// area will be marked in green. All the cubes in the marked
// area will be captured

class block {
public:

	enum class block_type {
		STANDARD,
		CAPTURE,
		FORBIDDEN,  // black color
		ADVANTAGE   // green color
	};

	block(int x, int y);
	~block();
	void init();
	void set_vel(float x, float y);
	void update_position(int x, int y);
	void block_active(bool b);
	bool is_active();
	void set_block_type(block_type t);
	block_type get_type();
	SDL_Rect get_position();
	void update(float dt);

private:

	SDL_Rect pos;
	float xvel;
	float yvel;

	bool active;
	block_type type;

};