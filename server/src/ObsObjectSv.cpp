#include "ObsObjectSv.h"

ObsObjectSv::ObsObjectSv(int id, int map_id, int type, float posx, float posy) {
	this->id = id;
	this->map_id = map_id;
	this->type = type;
	this->pos = std::pair<float, float>(posx, posy);
}