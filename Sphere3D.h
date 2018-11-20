#pragma once
#include "geometry3D.h"
#include "Ray.h"

class Material;

class Sphere3D :
	public Geometry3D
{
public:
	Sphere3D();
	Sphere3D(const vec3& center, float radius, Material* material);
	void setRadius(float radius);
	void setCenter(const vec3& center);
	float getRadius() const;
	vec3 getCenter() const;

	virtual bool intersects(const Ray& ray, Record& record, float t_min, float t_max) const;

	~Sphere3D();

private:
	vec3 center;
	float radius;
	Material* material;
};

