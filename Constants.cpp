#include "Constants.h"

float aspectRatio = 16.0f / 9.0f;

int windowWidth = 1280;
int windowHeight = (int(windowWidth / aspectRatio) < 1) ? 1 : int(windowWidth / aspectRatio);

double viewPortHeight = 2.0;
double viewPortWidth = viewPortHeight * aspectRatio;

Vec3 viewPort_U(viewPortWidth, 0, 0);
Vec3 viewPort_V(0, -viewPortHeight, 0);

Vec3 cameraCenter(0, 0, 0);

double viewPortDistanceFromCamera = 1.0;

Vec3 viewPortTopLeft = cameraCenter - (viewPort_U / 2) - (viewPort_V / 2) - Vec3(0, 0, viewPortDistanceFromCamera);

Vec3 pixel_X_Delta = viewPort_U / windowWidth;
Vec3 pixel_Y_Delta = viewPort_V / windowHeight;

Vec3 pixel_00_Location = viewPortTopLeft + (pixel_X_Delta / 2) + (pixel_Y_Delta / 2);

uint32_t MakeColor(uint8_t r, uint8_t g, uint8_t b)
{
    return (255 << 24) | (r << 16) | (g << 8) | b;
}