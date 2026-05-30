#include "Sphere.h"

bool Sphere::Hit(const Ray& ray, interval rayInterval, HitRecord& hitRecord) const
{

	Vec3 oc = ray.GetOrigin() - center;
	auto a = dot(ray.GetDirection(), ray.GetDirection());
	auto b = 2.0 * dot(ray.GetDirection(), oc);
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return false;
	}

	auto sqrt_discriminant = std::sqrt(discriminant);
	auto root = (-b - sqrt_discriminant) / (2 * a);

	if (!rayInterval.surrounds(root))
	{
		root = (-b + sqrt_discriminant) / (2 * a);
		if (!rayInterval.surrounds(root))
		{
			return false;
		}
	}

	hitRecord.t = root;
	hitRecord.hitPoint = ray.At(hitRecord.t);
	hitRecord.normal = unit_vector(hitRecord.hitPoint - center);

	return true;
}
