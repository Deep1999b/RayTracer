#pragma once

#include <cstdint>
#include "Vec3.h"

extern float aspectRatio;
extern int windowWidth;
extern int windowHeight;

extern double viewPortHeight;
extern double viewPortWidth;

extern Vec3 viewPort_U;
extern Vec3 viewPort_V;

extern Vec3 cameraCenter;

extern double viewPortDistanceFromCamera;

extern Vec3 viewPortTopLeft;
extern Vec3 pixel_X_Delta;
extern Vec3 pixel_Y_Delta;

extern Vec3 pixel_00_Location;

uint32_t MakeColor(uint8_t r, uint8_t g, uint8_t b);