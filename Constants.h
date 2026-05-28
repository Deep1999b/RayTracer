#pragma once

#include <cstdint>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

uint32_t MakeColor(uint8_t r, uint8_t g, uint8_t b)
{
	return (255 << 24) | (r << 16) | (g << 8) | b;
}
