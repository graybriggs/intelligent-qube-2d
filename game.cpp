

#include "block.h"
#include "input.h"

#include <vector>

int block_scale = 0;
float next_move = 1000.0f;

static std::vector<block> blocks;
static std::vector<block> active_blocks;

constexpr int GRID_SIZE_WIDTH = 4;
constexpr int GRID_SIZE_LENGTH = 15;

constexpr int BLOCK_SIZE_W = 64;
constexpr int BLOCK_SIZE_H = 64;

constexpr int PLAY_AREA_OFFSET_X = 100;
constexpr int PLAY_AREA_OFFSET_Y = 200;

bool run = true;


SDL_Rect player = { 100, 100, 16, 16 };


Uint32 move_blocks_forward(Uint32 interval, void* param) {

	std::vector<block>* vec = static_cast<std::vector<block>*>(param);

	//SDL_Rect* pos = static_cast<SDL_Rect*>(param);

	for (auto& b : *vec) {
		b.update_position(-BLOCK_SIZE_W, 0);
	}

	return interval;
}


void init_blocks() {

	int x = 0;
	int y = 0;

	for (int i = 0; i < 4 * 15 + 4; ++i) {
		block b(x, y);
		b.set_block_type(block::block_type::STANDARD);
		blocks.emplace_back(b);

		x += BLOCK_SIZE_W;
		if (x > 15 * BLOCK_SIZE_W) {
			x = 0;
			y += BLOCK_SIZE_H;
		}
	}

	blocks[25].set_block_type(block::block_type::ADVANTAGE);
	blocks[16].set_block_type(block::block_type::CAPTURE);

}


void init_moving_blocks() {

	constexpr int START_OFFSET = 12 * BLOCK_SIZE_W;

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			block b(START_OFFSET + BLOCK_SIZE_W * x, y * BLOCK_SIZE_H);
			b.set_vel(-0.0001f, 0.0001f);
			b.set_block_type(block::block_type::STANDARD);
			active_blocks.emplace_back(b);
		}
	}
}

void update_time_logic(float dt) {
	if (run) {
		next_move = dt + 1000.0f;
		run = false;
	}
}

void update_moving_blocks(float dt) {

	if (dt >= next_move) {

		for (auto& b : active_blocks) {

			b.update_position(-BLOCK_SIZE_W, 0);

			if (b.get_position().x < 0) {
				b.block_active(false);

				// increment block_scale by how many cubes fell
			}
		}
		next_move = dt + 1000.0f;
	}
}

void update_player(float dt) {

	if (input_state_button(INPUT_KEY_RIGHT)) {
		player.x += 1;
	}
	if (input_state_button(INPUT_KEY_LEFT)) {
		player.x -= 1;
	}
	if (input_state_button(INPUT_KEY_UP)) {
		player.y -= 1;
	}
	if (input_state_button(INPUT_KEY_DOWN)) {
		player.y += 1;
	}
	if (input_state_button(INPUT_KEY_SPACE)) {
		// if capture_flag is set then
		//   execute capture
		// else
		//   set capture_flag = 1;
	}
}

void render_floor_blocks(SDL_Renderer* renderer) {

	for (auto& b : blocks) {
		SDL_Rect r = b.get_position();
		r.x += PLAY_AREA_OFFSET_X;
		r.y += PLAY_AREA_OFFSET_Y;

		if (b.get_type() == block::block_type::STANDARD) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &r);
		}
		else if (b.get_type() == block::block_type::CAPTURE) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
			SDL_RenderFillRect(renderer, &r);
		}
		else if (b.get_type() == block::block_type::ADVANTAGE) {

			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
			SDL_RenderFillRect(renderer, &r);
		}
	}
}

void render_active_blocks(SDL_Renderer* renderer) {

	for (auto& b : active_blocks) {

		if (b.is_active()) {
			SDL_Rect r = b.get_position();
			r.x += PLAY_AREA_OFFSET_X;
			r.y += PLAY_AREA_OFFSET_Y;

			if (b.get_type() == block::block_type::STANDARD) {
				SDL_SetRenderDrawColor(renderer, 128, 128, 128, 128);
				SDL_RenderFillRect(renderer, &r);
			}
		}
	}
}

void render_player(SDL_Renderer* renderer) {
	SDL_Rect r = player;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &r);
}

void init_game() {
	init_blocks();
	init_moving_blocks();
}

void update_game(float dt) {
	float t = (float)SDL_GetTicks();

	update_player(t);
	update_time_logic(t);
	update_moving_blocks(t);
}


void render_game(SDL_Renderer* renderer) {
	render_floor_blocks(renderer);
	render_active_blocks(renderer);
	render_player(renderer);
}