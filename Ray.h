#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray() {}
	Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d) {}

	const Vec3& GetOrigin() const { return origin; }
	const Vec3& GetDirection() const { return direction; }

	Vec3 At(double t) const
	{
		return origin + t * direction;
	}

private:
	Vec3 origin;
	Vec3 direction;
};