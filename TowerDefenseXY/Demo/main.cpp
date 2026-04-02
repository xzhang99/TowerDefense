#define SDL_MAIN_HANDLED
#include <iostream>
#include <fstream>
#include <sstream>
#include <cJSON.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>

void test_json () {
	std::ifstream file ("../data/test.json");
	if (!file.good ()) {
		std::cerr << "Failed to open file: " << "../data/test.json" << std::endl;
		return;
	}

	std::stringstream str_stream;
	str_stream << file.rdbuf ();
	file.close ();

	cJSON* json_root = cJSON_Parse (str_stream.str ().c_str ());
	cJSON* json_name = cJSON_GetObjectItem (json_root, "name");
	cJSON* json_age = cJSON_GetObjectItem (json_root, "age");
	cJSON* json_pets = cJSON_GetObjectItem (json_root, "pets");

	std::cout << json_name->string << ": " << json_name->valuestring << std::endl;
	std::cout << json_age->string << ": " << json_age->valueint << std::endl;

	std::cout << json_pets->string << ": " << std::endl;
	cJSON* json_item = nullptr;
	cJSON_ArrayForEach (json_item, json_pets) {
		std::cout << "  - " << json_item->valuestring << std::endl;
	}
}

void test_csv () {
	std::ifstream file ("../data/test.csv");
	if (!file.good ()) {
		std::cerr << "Failed to open file: " << "../data/test.csv" << std::endl;
		return;
	}
	std::string str_line;
	while (std::getline (file, str_line)) {
		std::string str_cell;
		std::stringstream str_stream (str_line);
		while (std::getline (str_stream, str_cell, ',')) {
			std::cout << str_cell << " ";
		}
		std::cout << std::endl;
		
	}
	file.close ();
}
int main () {
	test_json ();
	std::cout << "==============================" << std::endl;
	test_csv ();

	SDL_Init (SDL_INIT_EVERYTHING);
	IMG_Init (IMG_INIT_PNG);
	Mix_Init (MIX_INIT_MP3);
	TTF_Init ();

	Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_Window* window = SDL_CreateWindow ("Hello SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* suf_img = IMG_Load ("../images/1.jpg");
	SDL_Texture* tex_img = SDL_CreateTextureFromSurface (renderer, suf_img);
	TTF_Font* font = TTF_OpenFont ("../images/Sunny Script.otf", 24);
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Surface* suf_text = TTF_RenderUTF8_Blended (font, "Hello SDL2!", color);
	SDL_Texture* tex_text = SDL_CreateTextureFromSurface (renderer, suf_text);

	Mix_Music* music = Mix_LoadMUS ("../sounds/MainTheme.wav");
	Mix_FadeInMusic (music, -1, 1000);
	SDL_Event event;
	SDL_Point pos_cursor = { 0, 0 };
	SDL_Rect rect_img, rect_text;
	Uint64 last_counter = SDL_GetPerformanceCounter ();
	Uint64 counter_freq = SDL_GetPerformanceFrequency ();

	rect_img.w = suf_img->w;
	rect_img.h = suf_img->h;
	rect_text.w = suf_text->w;
	rect_text.h = suf_text->h;

	bool is_quit = false;
	int fps = 60;
	while (!is_quit) {
		while (SDL_PollEvent (&event)) {
			if (event.type == SDL_QUIT) {
				is_quit = true;
			}
			else if (event.type == SDL_MOUSEMOTION) {
				pos_cursor.x = event.motion.x;
				pos_cursor.y = event.motion.y;
			}
		}
		Uint64 current_counter = SDL_GetPerformanceCounter ();
		double delta = (double)(current_counter - last_counter) / counter_freq;
		last_counter = current_counter;
		if (delta * 1000 < 1000 / fps) {
			SDL_Delay (1000 / fps - delta * 1000);
		}

		rect_img.x = pos_cursor.x;
		rect_img.y = pos_cursor.y;
		rect_text.x = pos_cursor.x;
		rect_text.y = pos_cursor.y;
		SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
		SDL_RenderClear (renderer);
		SDL_RenderCopy (renderer, tex_img, NULL, &rect_img);
		filledCircleColor (renderer, pos_cursor.x, pos_cursor.y, 10, 0xFFFF0000);
		SDL_RenderCopy (renderer, tex_text, NULL, &rect_text);

		SDL_RenderPresent (renderer);
	}
	return 0;

}