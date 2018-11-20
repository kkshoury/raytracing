#include "GeometryList.h"

GeometryList::GeometryList() {
	list = new std::vector<Geometry3D*>();

}

bool GeometryList::intersects(const Ray& ray, Record& record, float min_t, float max_t) const {
	Record tmp;
	float closest_t = max_t;
	bool intersects = false;
	for (auto itr = std::begin(*list); itr != std::end(*list); itr++) {
		bool hit = (*itr)->intersects(ray, tmp, min_t, closest_t);
		if (true == hit) {
			intersects = true;
			closest_t = tmp.t;
			record = tmp;
		}
	}

	if (intersects) {
		return true;
	}
	
	return false;
}

void GeometryList::push(Geometry3D* geometry) {
	list->push_back(geometry);
}

GeometryList::~GeometryList() {
	delete list;
}