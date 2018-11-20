#include "Ray.h"

Ray::Ray(const vec3& p0, const vec3& d) {
	this->p0 = p0;
	this->dir = d;
}
vec3 Ray::origin() const {
	return p0;
}

vec3 Ray::direction() const {
	return dir;
}

vec3 Ray::pointAt(float t) const {
	return p0 + (t * dir);
}

Ray::Ray()
{

}


Ray::~Ray()
{

}
