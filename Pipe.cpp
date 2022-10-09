#include "Pipe.h"

Pipe::Pipe() {}

Pipe::Pipe(int x, int y, int w, int h) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void Pipe::update(double delta) {
	rect.x -= speed * delta;
}

void Pipe::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}
