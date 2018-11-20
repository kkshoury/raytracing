#include "Sphere3D.h"


Sphere3D::Sphere3D() {

}

Sphere3D::Sphere3D(const vec3& center, float radius, Material* material) {
	this->material = material;
	this->center = center;
	this->radius = radius;
}

bool Sphere3D::intersects(const Ray& ray, Record& record, float t_min, float t_max) const{
	vec3 ca = ray.origin() - this->center;
	float a = dot(ray.direction(), ray.direction());
	float b = 2 * dot(ray.direction(), ca);
	float c = dot(ca, ca) - this->radius * this->radius;

	float delta = b * b - 4 * a*c;

	if (delta > 0) {
		float t1 = (-b - sqrt(delta)) / (2.0f * a);

		if (t1 > t_min && t1 < t_max) {
			record.t = t1;
			record.point = ray.pointAt(t1);
			record.normal = (record.point - center)/radius;
			record.material = material;
			return true;
		}

		float t2 = (-b + sqrt(delta)) / (2.0f * a);
		if (t2 > t_min && t2 < t_max) {
			record.t = t2;
			record.point = ray.pointAt(t2);
			record.normal = (record.point - center) / radius;
			record.material = material;
			return true;
		}

		return false;
	}
	else {
		return false;
	}
}

void Sphere3D::setRadius(float radius) {
	this->radius = radius;
}

void Sphere3D::setCenter(const vec3& center) {
	this->center = center;
}

float Sphere3D::getRadius() const{
	return this->radius;
}

vec3 Sphere3D::getCenter() const{
	return this->center;
}

Sphere3D::~Sphere3D(){

}
