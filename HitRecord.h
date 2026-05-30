#pragma once
#include "Vec3.h"
#include "Ray.h"

class HitRecord 
{
public:
	Vec3 hitPoint;
	Vec3 normal;
	double t;

	bool isFrontFace;

	void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal)
	{
		isFrontFace = dot(ray.GetDirection(), outwardNormal) < 0.0f;

		normal = isFrontFace ? outwardNormal : -outwardNormal;
	}
};