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
};