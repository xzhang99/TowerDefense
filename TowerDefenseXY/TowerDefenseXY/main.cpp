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
}