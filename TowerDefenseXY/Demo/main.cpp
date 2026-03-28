#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
int main () {
	SDL_Init (SDL_INIT_EVERYTHING);
	IMG_Init (IMG_INIT_PNG);
	Mix_Init (MIX_INIT_MP3);
	TTF_Init ();

	Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_Window* window = SDL_CreateWindow ("Hello SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);

	bool is_quit = false;

	SDL_Event event;

	while (!is_quit) {
		while (SDL_PollEvent (&event)) {
			if (event.type == SDL_QUIT) {
				is_quit = true;
			}
		}
		
	}

	return 0;
}