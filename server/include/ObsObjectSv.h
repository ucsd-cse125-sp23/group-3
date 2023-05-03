#pragma once
#include "Tokenizer.h"

#include "MapConstants.h"

#include <vector>
#include <utility>

class ObsObjectSv {
public:
	int id;
	int map_id;
	int type; // (1 2 3) (S M L)
	float width;
	float height;
	std::pair<float, float> pos;
	glm::mat4 pSrc;

	ObsObjectSv(int, int, int, float, float);
};
