#pragma once

#include <SDL2/SDL.h>

class Pipe {
public:
	SDL_Rect rect;

	int speed = 200;

	void update(double delta);
	void draw(SDL_Renderer* renderer);

	Pipe();
	Pipe(int x, int y, int w, int h);

};
