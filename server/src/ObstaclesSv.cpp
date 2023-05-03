#include "ObstaclesSv.h"

#include <iostream>

ObstaclesSv::ObstaclesSv() {
	const char* obs_files[3] = {
		"../BlinderEngine/resources/scene/obs_animal.txt",
		"../BlinderEngine/resources/scene/obs_clown.txt",
		"../BlinderEngine/resources/scene/obs_sculpture.txt"
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
					this->obs_vec.push_back(new ObsObjectSv(id, map_id, type, t_locs[loc] + j, i));
					id++;
				}
				else {
					this->obs_vec.push_back(new ObsObjectSv(id, map_id, type, t_locs[loc] + j, 0.5 + i));
					id++;
				}
			}
		}
		token.Close();
	}
}
ObstaclesSv::~ObstaclesSv() {
	for (auto e : obs_vec) {
		delete e;
	}
}
