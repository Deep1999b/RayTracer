#include "Render.h"
#include "Ray.h"

Render::Render()
{
	SDL_Init(SDL_INIT_VIDEO);

	window = nullptr;
	renderer = nullptr;
	texture = nullptr;
	colorBuffer = nullptr;
}

Render::~Render()
{
	delete[] colorBuffer;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Render::Initialize()
{
	window = SDL_CreateWindow(NULL, windowWidth, windowHeight, NULL);
	renderer = SDL_CreateRenderer(window, SDL_SOFTWARE_RENDERER);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
	colorBuffer = new uint32_t[windowWidth * windowHeight];

	sphere = make_shared<Sphere>(Vec3(0, 0, -1), 0.5);
	// Center at y = -100.5 with a radius of 100. 
// This keeps the top of the ground exactly at y = -0.5 (perfectly below your center sphere)
	ground = make_shared<Sphere>(Vec3(0, -100.5, -1), 100.0);

	world = HittableList();
	world.Add(sphere);
	world.Add(ground);
}

void Render::UpdateTexture()
{
	SDL_UpdateTexture(texture, NULL, colorBuffer, windowWidth * sizeof(uint32_t));
	SDL_RenderTexture(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Render::RenderClear(int r, int g, int b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void Render::PutPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	colorBuffer[(y * windowWidth) + x] = MakeColor(r, g, b);
}

void Render::Draw(int x, int y)
{
	Vec3 color ;

	auto pixelCenter = pixel_00_Location + (x * pixel_X_Delta) + (y * pixel_Y_Delta);

	auto rayDirection = pixelCenter - cameraCenter;

	Ray ray(cameraCenter, rayDirection);

	HitRecord localRecord;

	if (world.Hit(ray, interval(0, INFINITY), localRecord))
	{
		//Draw Normal Shaded sphere.
		color = 0.5f * Vec3(localRecord.normal.x() + 1, localRecord.normal.y() + 1, localRecord.normal.z() + 1);
	}
	else
	{
		//Draw Skybox.
		auto unit_direction = unit_vector(ray.GetDirection());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		color = (1.0 - a) * Vec3(1.0, 1.0, 1.0) + a * Vec3(0.5, 0.7, 1.0);
	}

	static const interval intensity(0.000, 0.999);
	PutPixel(x, y, intensity.clamp(color.x()) * 255, intensity.clamp(color.y()) * 255, intensity.clamp(color.z()) * 255);
}

void Render::RenderScene()
{
	for (int y = 0; y < windowHeight; y++)
	{
		for (int x = 0; x < windowWidth; x++)
		{
			Draw(x, y);
		}

		// Update Texture/Render every 10 lines to speed up displaying rendering progress
		UpdateTexture();
	}
}
