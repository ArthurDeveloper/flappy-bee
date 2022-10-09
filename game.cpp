#include <SDL2/SDL.h>
#include "Bee.h"
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Something went wrong. Try again later.";	
	}

	std::cout << "All working fine!";

	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Renderer* renderer = nullptr;

	window = SDL_CreateWindow("Flappy bee", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, 0, 0);

	Bee bee(50, SCREEN_HEIGHT/2-60, 10, 10);

	double delta = 0;
	Uint32 now = SDL_GetPerformanceCounter();
	Uint32 last = 0;
	
	bool quit = false;
	Uint32 t;
	SDL_Event event;
	while (!quit) {
		t = SDL_GetTicks();

		
		last = now;
		now = SDL_GetPerformanceCounter();

		delta = (double)((now - last) * 1000 / (double) SDL_GetPerformanceFrequency()) / 1000;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_UP) {
					bee.jump();
				}
			}
		}
		
		bee.update(delta);
		bee.draw(renderer);
		if (!bee.is_between_boundaries(0, SCREEN_HEIGHT)) {
			bee.die();
		}

		SDL_RenderPresent(renderer);
		
		SDL_SetRenderDrawColor(renderer, 0, 220, 255, 255);
		SDL_RenderClear(renderer);
	
		t = SDL_GetTicks() - t;
		if (t < 1000 / 60) {
			SDL_Delay(1000 / 60 - t);
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
