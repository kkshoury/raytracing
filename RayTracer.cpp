#include "RayTracer.h"
#include "vec3.h"
#include "GeometryList.h"
#include "Material.cpp"



RayTracer::RayTracer()
{
}

vec3 RayTracer::trace(const Ray& ray, const GeometryList& list, int depth) {
	Record record;
	vec3 col = vec3(0.0f, 0.0f, 0.0f);
	if (list.intersects(ray, record, 0.001f, FLT_MAX)) {
		Material* material = record.material;
		vec3 attenuataion = vec3();
		Ray scatteredRay = Ray();
		if (depth < 50 && material->scatter(ray, attenuataion, scatteredRay, record)) {
			return  attenuataion * trace(scatteredRay, list, depth + 1);
		}

		return vec3(0.0f, 0.0f, 0.0f);
	}
	else {
		vec3 unit = ray.direction();
		unit.normalize();
		float t = 0.5f * (unit.y() + 1.0f);
		return (1.0 - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

RayTracer::~RayTracer()
{
}
