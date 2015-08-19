#include <iostream>
#include "vec3f.h"
#include <stdlib.h>
#include "elevation.h"

Elevation::Elevation(int w, int l) {
	this->w = w;
	this->l = l;
			
	hs = new float*[l];
	colorMap = new Color*[l];
		
	for(int i = 0; i < l; i++) {
		hs[i] = new float[w];
	}
			
	for(int i = 0; i < l; i++) {
		colorMap[i] = new Color[w];
	}
			
	normals = new Vec3f*[l];
	for(int i = 0; i < l; i++) {
		normals[i] = new Vec3f[w];
	}
			
	computedNormals = false;
}
		
Elevation::~Elevation() {
	for(int i = 0; i < l; i++) {
		delete[] hs[i];
	}
	delete[] hs;
			
	for(int i = 0; i < l; i++) {
		delete[] colorMap[i];
	}
			
	delete[] colorMap;
			
	for(int i = 0; i < l; i++) {
		delete[] normals[i];
	}
	delete[] normals;
}
		
int Elevation:: width() {
	return w;
}
		
int Elevation::length() {
	return l;
}
		
//Sets the height at the position (x, z) to y
void Elevation::setHeight(int x, int z, float y) {
	hs[z][x] = y;
	computedNormals = false;
}
		
//Get the height at postion (x, z)
float Elevation::getHeight(int x, int z) {
	return hs[z][x];
}
		
//set the color value at position (x,z)
void Elevation::setColor(int x, int z, float value){	
	if(value>0.5){
		colorMap[z][x] =(Color){0.7f, 0.3f, 0.0f};
	}
	else if(value>0.30){
		colorMap[z][x] = (Color){0.3f, 0.7f, 0.0f};
	}
	else{
		colorMap[z][x] = (Color){0.0f, 0.3f, 0.7f};
	}	
}
		
//Get the color value at position (x,z)
Color Elevation::getColor(int x, int z){
	return colorMap[z][x];
}
		
//Computes the normals, if not yet computed
void Elevation::computeNormals() {
	if (computedNormals) {
		return;
	}
			
//Compute the rough version of the normals
	Vec3f** normals2 = new Vec3f*[l];
	for(int i = 0; i < l; i++) {
		normals2[i] = new Vec3f[w];
	}
	
	for(int z = 0; z < l; z++) {
		for(int x = 0; x < w; x++) {
			Vec3f sum(0.0f, 0.0f, 0.0f);
					
			Vec3f out;
			if (z > 0) {
				out = Vec3f(0.0f, hs[z - 1][x] - hs[z][x], -1.0f);
			}
			Vec3f in;
			if (z < l - 1) {
				in = Vec3f(0.0f, hs[z + 1][x] - hs[z][x], 1.0f);
			}
			Vec3f left;
			if (x > 0) {
				left = Vec3f(-1.0f, hs[z][x - 1] - hs[z][x], 0.0f);
			}
			Vec3f right;
			if (x < w - 1) {
				right = Vec3f(1.0f, hs[z][x + 1] - hs[z][x], 0.0f);
			}
				
			if (x > 0 && z > 0) {
				sum += out.cross(left).normalize();
			}
			if (x > 0 && z < l - 1) {
				sum += left.cross(in).normalize();
			}
			if (x < w - 1 && z < l - 1) {
				sum += in.cross(right).normalize();
			}
			if (x < w - 1 && z > 0) {
				sum += right.cross(out).normalize();
			}
				
			normals2[z][x] = sum;
		}
	}
			
	//Smooth out the normals
	const float FALLOUT_RATIO = 0.5f;
	for(int z = 0; z < l; z++) {
		for(int x = 0; x < w; x++) {
			Vec3f sum = normals2[z][x];
					
			if (x > 0) {
				sum += normals2[z][x - 1] * FALLOUT_RATIO;
			}
			if (x < w - 1) {
				sum += normals2[z][x + 1] * FALLOUT_RATIO;
			}
			if (z > 0) {
				sum += normals2[z - 1][x] * FALLOUT_RATIO;
			}
			if (z < l - 1) {
				sum += normals2[z + 1][x] * FALLOUT_RATIO;
			}
					
			if (sum.magnitude() == 0) {
				sum = Vec3f(0.0f, 1.0f, 0.0f);
			}
			normals[z][x] = sum;
		}
	}
			
	for(int i = 0; i < l; i++) {
		delete[] normals2[i];
	}
	delete[] normals2;
			
	computedNormals = true;
}
		
//Returns the normal at (x, z)
Vec3f Elevation::getNormal(int x, int z) {
	if (!computedNormals) {
		computeNormals();
	}
	return normals[z][x];
}
