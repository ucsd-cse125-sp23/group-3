#include "Obstacles.h"

#include <iostream>

Obstacles::Obstacles() {
	const char* obs_files[3] = {
		"./resources/scene/obs_animal.txt",
		"./resources/scene/obs_clown.txt",
		"./resources/scene/obs_sculpture.txt"
	};

	float sizes[4] = { 0.0, 0.3, 0.5, 1.0 };

	int id = 0;
	for (int map_id = 0; map_id < 3; map_id++) {
		Tokenizer token = Tokenizer();

		token.Open(obs_files[map_id]);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				int type = token.GetInt();
				int loc = -1 * token.GetInt();

				float t_size = sizes[type];
				float t_locs[3] = { t_size / 2.0, 0.5, 1 - t_size / 2.0 };

				if (type == 0) {
					continue;
				}
				else if (type == 3) {
					this->obs_vec.push_back(new ObsObject(id, map_id, type, t_locs[loc] + j, i));
					id++;
				}
				else {
					this->obs_vec.push_back(new ObsObject(id, map_id, type, t_locs[loc] + j, 0.5 + i));
					id++;
				}
			}
		}
		token.Close();
	}
}
Obstacles::~Obstacles() {
	for (auto e : obs_vec) {
		delete e;
	}
}

void Obstacles::draw(const glm::mat4& viewProjMtx, GLuint shader) {
	for (std::vector<Cube*>::iterator it = cubes.begin(); it != cubes.end(); it++) {
		(*it)->draw(viewProjMtx, shader);
	}
}
void Obstacles::obstacleCubes() {
	glm::mat4 id_mat = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};

	for (int ind = 0; ind < obs_vec.size(); ind++) {
		ObsObject* obj = obs_vec[ind];

		glm::vec3 dmin = glm::vec3(0, 0.0f, 0);
		glm::vec3 dmax = glm::vec3(GROUND_SIZE / 40.0f, 1.0f, GROUND_SIZE / 40.0f);

		float min = 0;
		float max = 1;

		if (obj->type == 3) {
			float pos = GROUND_SIZE / 11.0f;
			float size = GROUND_SIZE / 65.0f;
			dmin = glm::vec3(-pos, 0.0f, -size);
			dmax = glm::vec3(pos, 1.0f, size);

			obj->width = pos * 2;
			obj->height = size * 2;
		}
		else if (obj->type == 2) {
			min = -GROUND_SIZE / 28.0f;
			max = GROUND_SIZE / 28.0f;

			dmin = glm::vec3(min, 0.0f, min);
			dmax = glm::vec3(max, 1.0f, max);

			obj->width = max * 2;
			obj->height = max * 2;
		}
		else if (obj->type == 1) {
			min = -GROUND_SIZE / 42.0f;
			max = GROUND_SIZE / 42.0f;

			dmin = glm::vec3(min, 0.0f, min);
			dmax = glm::vec3(max, 1.0f, max);

			obj->width = max * 2;
			obj->height = max * 2;
		}
		cubes.push_back(new Cube(dmin, dmax));
	}
}