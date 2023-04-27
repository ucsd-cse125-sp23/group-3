#pragma once

#include "graphic2D.h"

class UI {
private:
	graphic2D* character;

public:
	UI();
	~UI();

	void draw(const glm::mat4& viewProjMtx, StaticShader shader);
	void update();
};
