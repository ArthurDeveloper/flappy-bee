#include <SDL2/SDL.h>
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


	bool quit = false;
	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_Rect rect;
		rect.x = 50;
		rect.y = 60;
		rect.w = 100;
		rect.h = 100;

		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);
		
		SDL_SetRenderDrawColor(renderer, 0, 220, 255, 255);
		SDL_RenderClear(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
