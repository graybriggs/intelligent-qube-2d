
#include "block.h"

block::block(int x, int y):
	pos({x, y, 64, 64}),
	active(true)
{}

block::~block() {}

void block::init() {

}
void block::set_vel(float x, float y) {
	xvel = x;
	yvel = y;
}

void block::update_position(int x, int y) {
	pos.x += x;
	pos.y += y;
}

SDL_Rect block::get_position() {
	return pos;
}

void block::block_active(bool b) {
	active = b;
}

bool block::is_active() {
	return active;
}

void block::set_block_type(block::block_type t) {
	type = t;
}

block::block_type block::get_type() {
	return type;
}

void block::update(float dt) {

}