#pragma once

#include "Ray.h"
#include "HitRecord.h"
#include "Interval.h"


class Hittable
{
public:
    virtual bool Hit(const Ray& ray, interval rayInterval, HitRecord& hitRecord) const = 0;
};


