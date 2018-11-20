#pragma once
#include "vec3.h"


class Ray
{
public:
	Ray();
	Ray(const vec3& p0, const vec3& d);
	vec3 origin() const;
	vec3 direction() const;
	vec3 pointAt(float t) const;

	vec3 p0;
	vec3 dir;

	~Ray();
};

