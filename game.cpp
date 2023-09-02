

#include "block.h"
#include "input.h"

#include <vector>

namespace {

int fallen_blocks = 0;

float next_move = 1000.0f;
float block_move_delay = 2000.0f;

std::vector<block> blocks;
std::vector<block> active_blocks;

constexpr int GRID_SIZE_WIDTH = 5;
constexpr int GRID_SIZE_LENGTH = 16;

constexpr int BLOCK_SIZE_W = 64;
constexpr int BLOCK_SIZE_H = 64;

constexpr int PLAY_AREA_OFFSET_X = 100;
constexpr int PLAY_AREA_OFFSET_Y = 200;

bool run = true;
bool capture_flag = false;
int block_scale = BLOCK_SIZE_W;


SDL_Rect player = { 100, 100, 16, 16 };


void init_blocks() {

	int x = 0;
	int y = 0;

	for (int i = 0; i < 5 * 16; ++i) {
		block b(x, y);
		b.set_block_type(block::block_type::STANDARD);
		b.block_active(true);
		blocks.emplace_back(b);

		x += BLOCK_SIZE_W;
		if (x > 15 * BLOCK_SIZE_W) {
			x = 0;
			y += BLOCK_SIZE_H;
		}
	}
}


void init_moving_blocks() {

	constexpr int START_OFFSET = 12 * BLOCK_SIZE_W;

	for (int y = 0; y < 5; ++y) {
		for (int x = 0; x < 4; ++x) {
			block b(x * BLOCK_SIZE_W + START_OFFSET, y * BLOCK_SIZE_H);
			b.set_vel(-0.0001f, 0.0001f);
			b.set_block_type(block::block_type::STANDARD);
			active_blocks.emplace_back(b);
		}
	}

	active_blocks[5].set_block_type(block::block_type::FORBIDDEN);
	active_blocks[19].set_block_type(block::block_type::FORBIDDEN);
	active_blocks[6].set_block_type(block::block_type::ADVANTAGE);
	active_blocks[16].set_block_type(block::block_type::ADVANTAGE);
}

void update_time_logic(float dt) {
	if (run) {
		next_move = SDL_GetTicks() + block_move_delay;
		run = false;
	}
}

void update_moving_blocks(float dt) {

	dt = SDL_GetTicks();

	if (dt >= next_move) {

		for (auto& b : active_blocks) {

			b.update_position(-BLOCK_SIZE_W, 0);

			if (b.get_position().x < 0) {
				b.block_active(false);

				// increment block_scale by how many cubes fell
			}
		}
		next_move = SDL_GetTicks() + block_move_delay;
	}
}

void set_capture_block() {
	SDL_Rect pp = { player.x, player.y };
	for (int i = 0; i < blocks.size(); ++i) {
		int bposx = blocks[i].get_position().x;
		int bposy = blocks[i].get_position().y;
		if (pp.x >= bposx + PLAY_AREA_OFFSET_X && pp.x < bposx + BLOCK_SIZE_W + PLAY_AREA_OFFSET_X
			&& pp.y >= bposy + PLAY_AREA_OFFSET_Y && pp.y < bposy + BLOCK_SIZE_H + PLAY_AREA_OFFSET_Y) {
			blocks[i].set_block_type(block::block_type::CAPTURE);
			break;
		}
	};
}

void check_set_advantage(block& b, int pos) {

	std::vector<int> adv;

	for (auto& ab : active_blocks) {
		if (b.get_position().x == ab.get_position().x && b.get_position().y == ab.get_position().y) {

			adv.push_back(pos);
			adv.push_back(pos - 1);
			adv.push_back(pos + 1);

			if (pos - GRID_SIZE_LENGTH > 0) {
				adv.push_back(pos - GRID_SIZE_LENGTH);
				adv.push_back(pos - GRID_SIZE_LENGTH + 1);
				adv.push_back(pos - GRID_SIZE_LENGTH - 1);
			}
			if (pos + GRID_SIZE_LENGTH < GRID_SIZE_WIDTH * GRID_SIZE_LENGTH) {
				adv.push_back(pos + GRID_SIZE_LENGTH);
				adv.push_back(pos + GRID_SIZE_LENGTH + 1);
				adv.push_back(pos + GRID_SIZE_LENGTH - 1);
			}
		}
	}

	if (adv.size() > 0) {
		for (int a : adv) {
			blocks[a].set_block_type(block::block_type::ADVANTAGE);
		}
	}
}

void execute_capture() {

	for (int i = 0; i < blocks.size(); ++i) {
		block b = blocks[i];
		if (b.get_type() == block::block_type::CAPTURE) {
			blocks[i].set_block_type(block::block_type::STANDARD);

			for (auto& ab : active_blocks) {
				int bx = b.get_position().x;
				int by = b.get_position().y;
				if (bx == ab.get_position().x && by == ab.get_position().y) {
					if (ab.is_active()) {
						ab.block_active(false);

						if (ab.get_type() == block::block_type::ADVANTAGE) {
							check_set_advantage(b, i);
							break;
						}
						else if (ab.get_type() == block::block_type::FORBIDDEN) {

							for (auto& b : blocks) {
								if (b.get_position().x <= block_scale) {
									b.block_active(false);
								}
							}
							block_scale += BLOCK_SIZE_W;
						}
					}
				}
			}
		}
	}
}

void execute_advantage_capture() {

	for (auto& b : blocks) {
		if (b.get_type() == block::block_type::ADVANTAGE) {
			b.set_block_type(block::block_type::STANDARD);
			int bx = b.get_position().x;
			int by = b.get_position().y;

			for (auto& ab : active_blocks) {
				if (bx == ab.get_position().x && by == ab.get_position().y) {
					ab.block_active(false);
				}
			}
		}
	}
}

void update_player(float dt) {

	if (input_state_button(INPUT_KEY_RIGHT)) {
		player.x += 1 * dt;
	}
	if (input_state_button(INPUT_KEY_LEFT)) {
		player.x -= 1 * dt;
	}
	if (input_state_button(INPUT_KEY_UP)) {
		player.y -= 1 * dt;
	}
	if (input_state_button(INPUT_KEY_DOWN)) {
		player.y += 1 * dt;
	}
	if (input_state_button(INPUT_KEY_X)) {
		execute_advantage_capture();
	}
	if (input_state_button(INPUT_KEY_SPACE)) {

		if (capture_flag) {
			execute_capture();
			capture_flag = false;
		}
		else {
			capture_flag = true;
			set_capture_block();
		}
		input_clear_all_inputs();
	}
}

void render_floor_blocks(SDL_Renderer* renderer) {

	for (auto& b : blocks) {

		if (b.is_active()) {
			SDL_Rect r = b.get_position();
			r.x += PLAY_AREA_OFFSET_X;
			r.y += PLAY_AREA_OFFSET_Y;

			if (b.get_type() == block::block_type::STANDARD) {
				SDL_SetRenderDrawColor(renderer, 255, 216, 255, 255);
				SDL_RenderFillRect(renderer, &r);
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &r);
			}
			else if (b.get_type() == block::block_type::CAPTURE) {
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
				SDL_RenderFillRect(renderer, &r);
			}
			else if (b.get_type() == block::block_type::ADVANTAGE) {

				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 160);
				SDL_RenderFillRect(renderer, &r);
			}
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
				SDL_SetRenderDrawColor(renderer, 96, 96, 96, 160);
				SDL_RenderFillRect(renderer, &r);
			}
			else if (b.get_type() == block::block_type::ADVANTAGE) {

				SDL_SetRenderDrawColor(renderer, 0, 200, 0, 160);
				SDL_RenderFillRect(renderer, &r);
			}
			else if (b.get_type() == block::block_type::FORBIDDEN) {

				SDL_SetRenderDrawColor(renderer, 8, 8, 8, 200);
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

} // namespace


void init_game() {
	init_blocks();
	init_moving_blocks();
}

void update_game(float dt) {
	//float t = (float)SDL_GetTicks();

	update_player(dt);
	update_time_logic(dt);
	update_moving_blocks(dt);
}


void render_game(SDL_Renderer* renderer) {
	render_floor_blocks(renderer);
	render_active_blocks(renderer);
	render_player(renderer);
}

