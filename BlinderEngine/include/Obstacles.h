#pragma once

#include "ObsObject.h"
#include "Tokenizer.h"

#include "Cube.h"
#include "MapConstants.h"

#include <vector>

class Obstacles {
public:
	Obstacles();
	~Obstacles();

	// indexed by id
	std::vector<ObsObject*> obs_vec;
	std::vector<Cube*> cubes;
	void draw(const glm::mat4& viewProjMtx, GLuint shader, std::vector<int> os, std::vector<glm::mat4>& sobs_pos, std::vector<glm::mat4>& mobs_pos, std::vector<glm::mat4> &lobs_pos);
	void obstacleCubes();
};