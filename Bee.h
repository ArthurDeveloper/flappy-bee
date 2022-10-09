#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Bee {
public:
	SDL_Rect rect;

	bool has_just_jumped = false;

	int MAX_FALL_SPEED = 800;
	int y_velocity = 0;
	int y_acceleration = 1000;

	int jump_force = 500;
	float jump_cooldown = 0.3;
	float jump_timer = 0;

	void jump();

	void update(double delta);
	void draw(SDL_Renderer* renderer);

	Bee(int x, int y, int w, int h);
};
