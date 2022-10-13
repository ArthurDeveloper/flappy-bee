#include "Bee.h"

#define DEBUG_MODE true

Bee::Bee(int x, int y, int w, int h) {
	initial_x = x;
	initial_y = y;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	surface = IMG_Load("res/bee.png");
	if (surface == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return;
	}

	texture = NULL;
}

void Bee::jump() {
	if (has_just_jumped) return;
	y_velocity = -jump_force;
	has_just_jumped = true;
}

bool Bee::is_between_boundaries(int min, int max) {
	if (rect.y < min) {
		return false;
	}

	if (rect.y > max) {
		return false;
	}

	return true;
}

void Bee::die() {
	has_died = true;
	rect.x = initial_x;
	rect.y = initial_y;
	y_velocity = 0;
}

void Bee::update(double delta) {
	y_velocity += y_acceleration * delta;

	if (y_velocity > MAX_FALL_SPEED) { 
		y_velocity = MAX_FALL_SPEED;
	}
	rect.y += y_velocity * delta;

	if (has_just_jumped) {
		jump_timer += delta;
		if (jump_timer > jump_cooldown) {
			has_just_jumped = false;
			jump_timer = 0;
		}
	}
}

void Bee::draw(SDL_Renderer* renderer) {
	if (texture == NULL) {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
	// Might be useful as a visible hitbox when debugging
	#if DEBUG_MODE == true
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);
	#endif
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
