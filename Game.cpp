#include "Game.h"

void Game::Run()
{
	Initialize();
	while (IS_APP_RUNNING)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Game::Initialize()
{
	render.Initialize();
}

void Game::ProcessInput()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			IS_APP_RUNNING = false;
			return;
		}
		if (event.type == SDL_EVENT_KEY_DOWN)
		{
			IS_APP_RUNNING = !(event.key.key == SDLK_ESCAPE);
			return;
		}
	}
}

void Game::Update()
{
}

void Game::Render()
{
	render.RenderClear(0, 0, 0);
	render.RenderScene();
}


