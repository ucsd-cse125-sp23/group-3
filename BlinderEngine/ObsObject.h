#pragma once

#include <utility>

class ObsObject {
public:
	int id;
	int map_id;
	int type; // (1 2 3) (S M L)
	float width;
	float height;
	std::pair<float, float> pos;

	ObsObject(int, int, int, float, float);
};
