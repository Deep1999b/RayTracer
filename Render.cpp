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
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Render::Initialize()
{
	window = SDL_CreateWindow(NULL, windowWidth, windowHeight, NULL);
	renderer = SDL_CreateRenderer(window, SDL_SOFTWARE_RENDERER);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
	colorBuffer = new uint32_t[windowWidth * windowHeight];
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
	Vec3 color = {0, 0, 0};

	auto pixelCenter = pixel_00_Location + (x * pixel_X_Delta) + (y * pixel_Y_Delta);

	auto rayDirection = pixelCenter - cameraCenter;

	Ray ray(cameraCenter, rayDirection);

	auto t = HitSphere(point3(0, 0, -1), 0.5, ray);
	if (t > 0.0) {
		Vec3 N = unit_vector(ray.At(t) - Vec3(0, 0, -1));
		color = 0.5f * Vec3(N.x() + 1, N.y() + 1, N.z() + 1);

	}
	else
	{
		auto unit_direction = unit_vector(ray.GetDirection());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		color = (1.0 - a) * Vec3(1.0, 1.0, 1.0) + a * Vec3(0.5, 0.7, 1.0);
	}

	PutPixel(x, y, color.x() * 255, color.y() * 255, color.z() * 255);
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
		if(y % 10) UpdateTexture();
	}
}

double Render::HitSphere(const Vec3& center, const double& radius, const Ray& ray)
{
	Vec3 oc = ray.GetOrigin() - center;
	auto a = dot(ray.GetDirection(), ray.GetDirection());
	auto b = 2.0 * dot(ray.GetDirection(), oc);
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return -1;
	}
	else {
		return (-b - std::sqrt(discriminant)) / (2.0 * a);
	}
}
