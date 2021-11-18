#pragma once
/*********************************************************
* Summary: Data structure for the city nodes and operator overloads used for
* sorting.
*
* Author: Nathanael Cook
* Created: Nov 2021
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

class Intersection {
public:
	Intersection() {
		distance = -0.1;
		id = 0;
		parent = 0;
	}
	Intersection(double x, unsigned char y, unsigned char z) {
		distance = x;
		id = y;
		parent = z;
	}

	double distance;
	unsigned char id;
	unsigned char parent;

	bool operator<=(Intersection val) {
		return distance >= val.distance;
	}
	bool operator>=(Intersection val) {
		return distance <= val.distance;
	}
	bool operator<=(Intersection* val) {
		return distance >= val->distance;
	}
	bool operator>=(Intersection* val) {
		return distance <= val->distance;
	}
	bool operator() (Intersection lhs, Intersection rhs) {
		return lhs.distance > rhs.distance;
	}
	bool operator() (Intersection* lhs, Intersection* rhs) {
		return lhs->distance > rhs->distance;
	}
};
