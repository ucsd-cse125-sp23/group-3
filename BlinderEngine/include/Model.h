#pragma once
#include "core.h"
#include <vector>

class Model
{
public:
	Model();
	bool loadAssImp(
		const char* path,
		std::vector<unsigned int>& indices,
		std::vector<glm::vec3>& vertices,
		std::vector<glm::vec2>& uvs,
		std::vector<glm::vec3>& normals
	);
};

