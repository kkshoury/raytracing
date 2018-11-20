#pragma once
#include <iostream>
#include <fstream>
#include <math.h>

class vec3
{
public:
	vec3();
	vec3(float x, float y, float z);
	inline float x() const;
	inline float y() const;
	inline float z() const;
	inline float r() const;
	inline float g() const;
	inline float b() const;

	inline const vec3& operator+() const;
	inline vec3 operator-() const;
	inline float operator[](int i) const;
	inline float& operator[](int i);

	inline vec3& operator+=(const vec3 &v);
	inline vec3& operator-=(const vec3 &v);
	inline vec3& operator*=(const vec3 &v);
	inline vec3& operator/=(const vec3 &v);
	inline vec3& operator*=(float c);
	inline vec3& operator/=(float c);

	float length() const;
	float length2() const;
	void normalize();


	~vec3() {};

	float e[3];
};

std::istream& operator>>(std::istream &is, vec3 &t);
std::ostream& operator>>(std::ostream &os, const vec3 &t);
std::ofstream& operator<<(std::ofstream &os, const vec3 &t);

vec3 operator+(const vec3& a, const vec3& b);
vec3 operator-(const vec3& a, const vec3& b);
vec3 operator*(const vec3& a, const vec3& b);
vec3 operator/(const vec3& a, const vec3& b);
vec3 operator*(float c, const vec3& b);
vec3 operator*(const vec3& b, float c);
vec3 operator/(const vec3& b, float c);
float dot(const vec3& a, const vec3& b);
vec3 cross(const vec3& a, const vec3& b);


