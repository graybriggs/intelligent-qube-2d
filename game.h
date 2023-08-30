#pragma once

#include <SDL.h>

#include "block.h"

void init_moving_blocks();
void update_moving_blocks(float dt);
void render_floor_blocks(SDL_Renderer* renderer);
void render_active_blocks(SDL_Renderer* renderer);

void set_capture_block();
void execute_capture();

/// 
void init_game();
void update_game(float dt);
void render_game(SDL_Renderer* renderer);