#pragma once
#include "Ray.h"

class Material;

struct Record {
	vec3 point;
	vec3 normal;
	vec3 color;
	Material* material;
	float t;
};


class Geometry3D
{
public:
	virtual bool intersects(const Ray& ray, Record& record, float t_min, float t_max) const = 0;
};


