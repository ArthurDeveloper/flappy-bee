#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Bee {
public:
	SDL_Rect rect;

	bool has_just_jumped = false;

	int initial_x = 0;
	int initial_y = 0;

	int MAX_FALL_SPEED = 800;
	int y_velocity = 0;
	int y_acceleration = 1000;

	int jump_force = 500;
	float jump_cooldown = 0.3;
	float jump_timer = 0;
	
	void jump();

	bool is_between_boundaries(int min, int max);

	void die();

	void update(double delta);
	void draw(SDL_Renderer* renderer);

	Bee(int x, int y, int w, int h);
};
