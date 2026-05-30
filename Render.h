#pragma once

#include <SDL3/SDL.h>
#include "Constants.h"
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HittableList.h"

class Render
{

public:
	Render();
	~Render();
	
	void Initialize();
	void UpdateTexture();
	void RenderClear(int r, int g , int b);
	void PutPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);
	void Draw(int x, int y);
	void RenderScene();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	uint32_t* colorBuffer;
	
	shared_ptr<Hittable> sphere;
	shared_ptr<Hittable> ground;
	HittableList world;
};