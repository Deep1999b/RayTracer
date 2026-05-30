#include "HittableList.h"


void HittableList::Clear()
{ 
    objects.clear();
}

void HittableList::Add(shared_ptr<Hittable> object)
{
    objects.push_back(object);
}

bool HittableList::Hit(const Ray& r, interval rayInterval, HitRecord& rec) const 
{
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = rayInterval.max;

    for (const auto& object : objects) {
        if (object->Hit(r, interval(rayInterval.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
