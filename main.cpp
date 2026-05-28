#include <SDL3/SDL.h>
#include "Constants.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window;
	window = SDL_CreateWindow(NULL, WINDOW_WIDTH, WINDOW_HEIGHT, NULL);

	SDL_Renderer* renderer;
	renderer = SDL_CreateRenderer(window, SDL_SOFTWARE_RENDERER);

	uint32_t * colorBuffer = new uint32_t[WINDOW_WIDTH * WINDOW_HEIGHT];
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);

	while (true)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
				return 0;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		for (int y = 0; y < 480; y++)
		{
			for (int x = 0; x < 640; x++)
			{
				auto r = double(x) / (WINDOW_WIDTH);
				auto g = double(y) / (WINDOW_HEIGHT);
				auto b = 0.0;

				int ir = int(255.999 * r);
				int ig = int(255.999 * g);
				int ib = int(255.999 * b);


				colorBuffer[(y * WINDOW_WIDTH) + x] = MakeColor(ir, ig, ib);
			}
		}

		SDL_UpdateTexture(texture, NULL, colorBuffer, WINDOW_WIDTH * sizeof(uint32_t));
		SDL_RenderTexture(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	delete[] colorBuffer;
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}