#pragma once

#include "Hittable.h"
#include "HitRecord.h"
#include "Interval.h"

class Sphere : public Hittable
{
private:
	Vec3 center;
	double radius;

public:
	Sphere(){}
	Sphere(Vec3 o, double r) : center(o), radius(std::fmax(0, r)){}

	bool Hit(const Ray& ray, interval rayInterval, HitRecord& hitRecord) const override;
};