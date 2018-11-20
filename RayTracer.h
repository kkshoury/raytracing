#pragma once
#include "Ray.h"
#include "GeometryList.h"

class RayTracer
{
public:
	RayTracer();

	vec3 trace(const Ray& ray, const GeometryList& list, int depth);

	~RayTracer();


};

