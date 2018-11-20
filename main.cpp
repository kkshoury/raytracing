#include <iostream>
#include <fstream>
#include <math.h>
#include <float.h>
#include <time.h>

#include "vec3.h"
#include "Ray.h"
#include "Sphere3D.h"
#include "GeometryList.h"
#include "Material.cpp"
//#include "image.cpp"


void drawBMP(std::string fname, int w, int h, float** red, float** green, float** blue);

typedef vec3 rgb;
typedef vec3 pos3;

#define uniform() (rand()/(RAND_MAX + 1.0f))

vec3 randomPointInUnitSphere() {
	while (true) {
		float x = 2.0f * (uniform() - 0.5f);
		float y = 2.0f * (uniform() - 0.5f);
		float z = 2.0f * (uniform() - 0.5f);
		vec3 v = vec3(x, y, z);
		if (v.length2()<= 1.0) {
			return v;
		}
	}
	

}

vec3 trace(const Ray& ray, const GeometryList& list, int depth ) {
	Record record;
	vec3 col = vec3(0.0f, 0.0f, 0.0f);
	if (list.intersects(ray, record, 0.001f, FLT_MAX)) {
		Material* material = record.material;
		vec3 attenuataion = vec3(); 
		Ray scatteredRay = Ray();
		if (depth < 50 && material->scatter(ray, attenuataion, scatteredRay, record)) {
			return  attenuataion * trace(scatteredRay, list, depth + 1);
		}

		return vec3(0.0f, 0.0f, 0.0f);
	}
	else {
		vec3 unit = ray.direction();
		unit.normalize();
		float t = 0.5f * (unit.y() + 1.0f);
		return (1.0 - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

int main() {
	srand((unsigned)time(0));
	GeometryList list = GeometryList();
	
	for (int i = 0; i < 10; i++) {
		float x, y, z;
		x = (uniform() * 2.0f) - 1.0f;
		y = 0.0f;
		z = uniform() * -1.0f + 0.5;
		float radius = 0.05;
		
		list.push(new Sphere3D(vec3(x, y, z), radius, new Metal(vec3(0.8f, 0.8f, 0.8f), 0.0f)));
	}

	list.push(new Sphere3D(vec3(0, 0, -2), 0.5f, new Lambert(vec3(0.8f, 0.3f, 0.3f))));
	list.push(new Sphere3D(vec3(-1, 0, -2), 0.5f, new Metal(vec3(0.8f, 0.3f, 0.9f), 0.2f)));
	list.push(new Sphere3D(vec3(1, 0, -2), 0.5f, new Metal(vec3(0.8f, 0.8f, 0.8f), 0.0f)));
	list.push(new Sphere3D(vec3(0, -100.5, -2), 100.0f, new Lambert(vec3(0.8, 0.8, 0.0))));
	
	rgb sphereColor(1.0f, 0.0f, 0.0f);
	constexpr int width = 300, height = 300;
	
	std::ofstream fout;
	fout.open("rt.ppm");
	vec3 bleft = vec3(-2.0f, -1.0f, -1.0f);
	vec3 origin = vec3(0.0f, 0.0f, 0.0f);
	vec3 screen = vec3(0.0f, 0.0f, -1.0f);
	vec3 verticle = vec3(0.0f, 2.0f, 0.0f);
	vec3 horizonatal = vec3(4.0f, 0.0f, 0.0f);

	int samplespp = 100;

	float **red, **green, **blue;
	red = new float*[height];
	green = new float*[height];
	blue = new float*[height];
	for (int i = 0; i < height; i++) {
		red[i] = new float[width];
		green[i] = new float[width];
		blue[i] = new float[width];
	}

	fout << "P3\n" << width << "\n" << height << "\n" << "255\n";
	for (int i = height - 1; i >= 0; i--) {
		//system("CLS");
		//std::cout<< (int)((float) (height -1 - i) / (float) height * 100.0f )<< "% complete...\n";
		for (int j = 0; j < width; j++) {
			rgb col(0.0f, 0.0f, 0.0f);
			for (int k = 0; k < samplespp; k++) {
				float x = (((float)j +uniform())/ (float)width);
				float y = (((float)i +uniform())/ (float)height);
				pos3 p = bleft + x * horizonatal + y * verticle;
				Ray ray = Ray(origin, p - origin);
				col = col + trace(ray, list, 0);
			}

			col = col * 1.0f/(float)samplespp;
			col = vec3(sqrt(col.x()), sqrt(col.y()), sqrt(col.z()));
			fout << col <<"\n";
			//red[i][j] = col.x();
			//green[i][j] = col.y();
			//blue[i][j] = col.z();

		}
	}

	//drawBMP("image.bmp", width, height, red, green, blue);

	fout.close();

}