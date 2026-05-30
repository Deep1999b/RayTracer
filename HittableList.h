#pragma once

#include "Hittable.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable
{
public:
    std::vector<shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(shared_ptr<Hittable> object) { Add(object); }

    void Clear();

    void Add(shared_ptr<Hittable> object);

    bool Hit(const Ray& ray, interval rayInterval, HitRecord& hitRecord) const override;

};