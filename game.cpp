#include <SDL2/SDL.h>
#include "Bee.h"
#include "Pipe.h"
#include <cstdlib>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int amount_of_pipes = 0;
void addPipes(Pipe*& pipes, int amount_to_be_added) {
	amount_of_pipes += amount_to_be_added;
	pipes = (Pipe*) realloc(pipes, amount_of_pipes * sizeof(Pipe));

	for (int i = amount_of_pipes - amount_to_be_added; i < amount_of_pipes; i+=2) {
		int random_number = rand() % 320;

		Pipe pipe1(
			(SCREEN_WIDTH + 80 * (2 * i)),
			(300 + (rand() % 120)), 
			80,
			SCREEN_HEIGHT
		);

		Pipe pipe2(
			(SCREEN_WIDTH + 80 * (2 * i)),
			(300 + (rand() % 120)) * -1, 
			80,
			SCREEN_HEIGHT
		); 

		pipes[i] = pipe1;
		pipes[i+1] = pipe2;
	}	
}

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

	Pipe* pipes = (Pipe*) malloc(amount_of_pipes * sizeof(Pipe));
	addPipes(pipes, 20);

	float pipe_spawn_timer = 0;

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

		for (int i = 0; i < amount_of_pipes; i++) {
			Pipe* pipe = &pipes[i];
			pipe->update(delta);
			pipe->draw(renderer);
		}

		pipe_spawn_timer += delta;
		if (pipe_spawn_timer > 1) {
			addPipes(pipes, 20);
			pipe_spawn_timer = 0;
		}

		SDL_RenderPresent(renderer);
		
		SDL_SetRenderDrawColor(renderer, 0, 220, 255, 255);
		SDL_RenderClear(renderer);
	
		t = SDL_GetTicks() - t;
		if (t < 1000 / 60) {
			SDL_Delay(1000 / 60 - t);
		}
	}

	free(pipes);
	pipes = nullptr;

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
