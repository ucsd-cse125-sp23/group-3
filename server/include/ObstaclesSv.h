#pragma once

#include "ObsObjectSv.h"
#include "Tokenizer.h"

#include "MapConstants.h"

#include <vector>

class ObstaclesSv {
public:
	ObstaclesSv();
	~ObstaclesSv();

	// indexed by id
	std::vector<ObsObjectSv*> obs_vec;
	std::vector<glm::mat4> glm_vec;

	void pairUp() { for (int ind = 0; ind < obs_vec.size(); ind++) obs_vec[ind]->pSrc = glm_vec[ind]; };
};