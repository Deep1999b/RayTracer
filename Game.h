#pragma once
#include "Render.h"

class Game
{
public:
	void Run();

private:
	SDL_Event event;
	Render render;
	bool IS_APP_RUNNING = true;
	
	void Initialize();
	void ProcessInput();
	void Update();
	void Render();
};