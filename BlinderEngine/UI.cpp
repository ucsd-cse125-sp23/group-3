
#include "UI.h"

UI::UI() {
	character = new graphic2D(0, 0, 2, 2, true);
	character->bindTexture("./resources/images/test.png");
}

UI::~UI() {
	delete character;
}

void UI::draw(const glm::mat4& viewProjMtx, StaticShader shader) {
	character->draw(viewProjMtx, shader);
}

void UI::update() {
	character->update();
}



