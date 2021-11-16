#pragma once

class Intersection {
public:
	Intersection() {
		distance = 0;
		id = 0;
		parent = 0;
	}
	Intersection(unsigned int x, unsigned char y, unsigned char z) {
		distance = x;
		id = y;
		parent = z;
	}

	float distance;
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
