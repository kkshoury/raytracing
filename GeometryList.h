#pragma once
#include <vector>
#include "geometry3D.h"

class GeometryList :
	public Geometry3D
{
public:
	GeometryList();
	void push(Geometry3D* geometry);
	virtual bool intersects(const Ray& ray, Record& record, float t_min, float t_max) const;

	~GeometryList();

private:
	std::vector<Geometry3D*>* list;
};

