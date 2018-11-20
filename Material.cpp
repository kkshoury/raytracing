#pragma once
#include "geometry3D.h"
#include "GeometryList.h"
#include "Ray.h"
#include <stdlib.h>

#ifndef uniform()
#define uniform() ((float)rand()/(float)(RAND_MAX))
#endif

class Material {
public:
	virtual bool scatter(const Ray& ray, vec3& attenutation, Ray& scattered, Record& record) const = 0;

};

class Lambert : public Material {

public:	
	
	virtual bool scatter(const Ray&ray, vec3& attenutation, Ray& scattered, Record& record) const {
		vec3 unitN = record.normal;
		Ray randomRay = Ray(record.point, unitN + Lambert::randomPointInUnitSphere());
		scattered = randomRay;
		attenutation = color;
		return true;
	}
	Lambert(const vec3& col) : color(col) {}

private:
	vec3 color;
	static vec3 randomPointInUnitSphere() {
		while (true) {
			float x = 2.0f * (uniform() - 0.5f);
			float y = 2.0f * (uniform() - 0.5f);
			float z = 2.0f * (uniform() - 0.5f);
			vec3 v = vec3(x, y, z);
			if (v.length2() <= 1.0) {
				return v;
			}
		}


	}
};

class Metal : public Material {
	// Inherited via Material
public:
	Metal(vec3 color, float f) : reflectance(color) { fuzz = f; if (fuzz > 1) fuzz = 1; }
	virtual bool scatter(const Ray & ray, vec3 & attenutation, Ray & scattered, Record & record) const override
	{
		vec3 dir = ray.direction();
		dir.normalize();
		vec3 normal = record.normal;

		scattered = Ray(record.point, reflect(dir, normal) + fuzz * Metal::randomPointInUnitSphere());
		attenutation = reflectance;
		return (dot(normal, scattered.direction()) > 0.0f);
	}

private:
	vec3 reflectance;
	float fuzz;

	vec3 reflect(const vec3& u_dir, const vec3& u_normal) const {
		return u_dir - 2 * dot(u_dir, u_normal) * u_normal;
	}

	static vec3 randomPointInUnitSphere() {
		while (true) {
			float x = 2.0f * (uniform() - 0.5f);
			float y = 2.0f * (uniform() - 0.5f);
			float z = 2.0f * (uniform() - 0.5f);
			vec3 v = vec3(x, y, z);
			if (v.length2() <= 1.0) {
				return v;
			}
		}
	}
};