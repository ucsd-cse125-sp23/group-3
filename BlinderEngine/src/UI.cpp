
#include "UI.h"

UI::UI() {
	UI::win_width = 800;
	UI::win_height = 600;
	//assigned_id = -1;
	character = new graphic2D(UI::char_sizeX, UI::char_sizeY * UI::win_width / UI::win_height,
		UI::char_posiX, UI::char_posiY, true);
	character->bindTexture(UI::char_png);

	skill = new graphic2D(UI::skill_sizeX, UI::skill_sizeY * UI::win_width / UI::win_height,
		UI::char_posiX + UI::char_sizeX, UI::char_posiY, true);
	//skill->bindTexture(UI::skill_png);

	skill_frame = new graphic2D(UI::skill_sizeX, UI::skill_sizeY * UI::win_width / UI::win_height,
		UI::char_posiX + UI::char_sizeX, UI::char_posiY, true);
	//skill_frame->bindTexture(UI::skill_frame_png);

	skill_cd = new graphic2D(UI::skill_sizeX, UI::skill_sizeY * UI::win_width / UI::win_height,
		UI::char_posiX + UI::char_sizeX, UI::char_posiY, true);
	skill_cd->bindTexture(UI::skill_cd_png);

	time = new graphic2D(UI::time_sizeX, UI::time_sizeY * UI::win_width / UI::win_height,
		UI::time_posiX, -1 + UI::char_sizeY * UI::win_width / UI::win_height, true);
	time->bindTexture(UI::time_png);

	time_bar = new graphic2D(UI::time_bar_sizeX, UI::time_bar_sizeY * UI::win_width / UI::win_height - (UI::time_sizeY * UI::win_width / UI::win_height)/5,
		UI::time_bar_posiX + UI::time_sizeX / 4, -1 + UI::char_sizeY * UI::win_width / UI::win_height + (UI::time_sizeY * UI::win_width / UI::win_height) /5.4, true);
	time_bar->bindTexture(UI::time_bar_png);
	time_bar_len = time_bar->getSizeY();
	time_bar_s = new graphic2D(UI::time_bar_sizeX, UI::time_bar_sizeY * UI::win_width / UI::win_height - (UI::time_sizeY * UI::win_width / UI::win_height) / 5,
		UI::time_bar_posiX + UI::time_sizeX / 4, -1 + UI::char_sizeY * UI::win_width / UI::win_height + (UI::time_sizeY * UI::win_width / UI::win_height) / 5.4, true);
	time_bar_s->bindTexture(UI::time_bar_cut);

	minimap_dark = new Minimap(UI::mnmap_sizeX * UI::win_height / UI::win_width, UI::mnmap_sizeY,
		0.99 - UI::mnmap_sizeX * UI::win_height / UI::win_width, UI::mnmap_posiY, UI::minimap_dark_png);
	minimap_light = new Minimap(UI::mnmap_sizeX * UI::win_height / UI::win_width, UI::mnmap_sizeY,
		0.99 - UI::mnmap_sizeX * UI::win_height / UI::win_width, UI::mnmap_posiY, UI::minimap_light_png);

	level = new graphic2D(UI::level_sizeX * UI::win_height / UI::win_width, UI::level_sizeY,
		0.99 - (UI::mnmap_sizeX + UI::level_sizeX) * UI::win_height / UI::win_width, UI::level_posiY, true);
	level->bindTexture(UI::insec_png);

	level_bar = new graphic2D(UI::level_bar_sizeX * UI::win_height / UI::win_width - UI::level_sizeX * 0.1 * UI::win_height / UI::win_width, UI::level_bar_sizeY,
		0.99 - (UI::mnmap_sizeX + UI::level_sizeX * 0.86) * UI::win_height / UI::win_width, UI::level_bar_posiY + UI::level_sizeY / 5, true);
	level_bar->bindTexture(UI::level_bar_png);
	level_bar_len = level_bar->getSizeX();
	level_bar_s = new graphic2D(UI::level_bar_sizeX * UI::win_height / UI::win_width - UI::level_sizeX * 0.1 * UI::win_height / UI::win_width, UI::level_bar_sizeY,
		0.99 - (UI::mnmap_sizeX + UI::level_sizeX * 0.86) * UI::win_height / UI::win_width, UI::level_bar_posiY + UI::level_sizeY / 5, true);
	level_bar_s->bindTexture(UI::level_bar_cut);

	shorter_timer = false;
	shorter_level = false;
}

UI::~UI() {
	delete character;
	delete skill;
	delete skill_cd;
	delete time;
	delete time_bar;
	delete time_bar_s;
	delete minimap_dark;
	delete minimap_light;
	delete level;
	delete level_bar;
	delete level_bar_s;
}

void UI::draw(const glm::mat4& viewProjMtx, StaticShader shader, int playerID, int cd_remain) {
	character->draw(shader,1.0f);
	skill->draw(shader, 1.0f);
	skill_cd->draw(shader, 0.6 * (float)cd_remain/(float)SKILL_CD);
	skill_frame->draw(shader, 1.0f);
	if (shorter_timer) {
		time_bar_s->draw(shader, 1.0f);
	}
	else {
		time_bar->draw(shader, 1.0f);
	}
	time->draw(shader, 1.0f);
	if (playerID != 0) {			// not Alice
		if (!minimap_dark->showAlice()) {
			minimap_dark->draw(viewProjMtx, shader);
		}else if (minimap_light->showAlice()) {
			minimap_light->draw(viewProjMtx, shader);
		}
	}
	if (shorter_level) {
		level_bar_s->draw(shader, 1.0f);
	}
	else {
		level_bar->draw(shader, 1.0f);
	}
	//std::cout << "level\n" << level->getPosiX() << " " << level->getPosiY() << "\n";
	level->draw(shader, 1.0f);
}

void UI::setSize(const int& width, const int& height, int playerId) {
	UI::win_height = height;
	UI::win_width = width;
	character->setposition(UI::char_sizeX, UI::char_sizeY * width / height);
	character->update();

	skill->setposition(UI::skill_sizeX, UI::skill_sizeY * width / height);
	skill->update();

	skill_frame->setposition(UI::skill_sizeX, UI::skill_sizeY * width / height);
	skill_frame->update();

	skill_cd->setposition(UI::skill_sizeX, UI::skill_sizeY * width / height);
	skill_cd->update();

	time->setposition(UI::time_sizeX, UI::time_sizeY * width / height,
		UI::time_posiX, -1 + UI::char_sizeY * width / height);
	time->update();

	time_bar->setposition(UI::time_bar_sizeX, UI::time_sizeY * width / height - (UI::time_sizeY * width / height) / 5,
		UI::time_bar_posiX + UI::time_sizeX / 4, -1 + UI::char_sizeY * width / height + (UI::time_sizeY * width / height) / 5.4);
	time_bar->update();
	time_bar_len = time_bar->getSizeY();
	time_bar_s->setposition(UI::time_bar_sizeX, UI::time_sizeY * width / height - (UI::time_sizeY * width / height) / 5,
		UI::time_bar_posiX + UI::time_sizeX / 4, -1 + UI::char_sizeY * width / height + (UI::time_sizeY * width / height) / 5.4);
	time_bar_s->update();

	minimap_dark->setposition(UI::mnmap_sizeX * height / width, UI::mnmap_sizeY,
		0.99 - UI::mnmap_sizeX * height / width, UI::mnmap_posiY);
	minimap_dark->update();
	minimap_light->setposition(UI::mnmap_sizeX * height / width, UI::mnmap_sizeY,
		0.99 - UI::mnmap_sizeX * height / width, UI::mnmap_posiY);
	minimap_light->update();

	if (playerId == 0) {		// Alice
		level->setposition(UI::level_sizeX * height / width, UI::level_sizeY,
			0.99 - (UI::level_sizeX) * height / width, UI::level_posiY);
	}
	else {
		level->setposition(UI::level_sizeX * height / width, UI::level_sizeY + 0.1,
			0.99 - (UI::mnmap_sizeX + UI::level_sizeX) * height / width, UI::level_posiY - 0.07);
	}
	level->update();
	
	if (playerId == 0) {		// Alice
		level_bar->setposition(UI::level_bar_sizeX * height / width - UI::level_sizeX * 0.19 * height / width, UI::level_bar_sizeY,
			0.99 - (UI::level_sizeX * 0.81) * height / width, UI::level_bar_posiY + UI::level_sizeY / 5);
		level_bar_s->setposition(UI::level_bar_sizeX * height / width - UI::level_sizeX * 0.19 * height / width, UI::level_bar_sizeY,
			0.99 - (UI::level_sizeX * 0.81) * height / width, UI::level_bar_posiY + UI::level_sizeY / 5);
	}
	else {
		level_bar->setposition(UI::level_bar_sizeX * height / width - UI::level_sizeX * 0.1 * height / width, UI::level_bar_sizeY,
			0.99 - (UI::mnmap_sizeX + UI::level_sizeX * 0.86) * height / width, UI::level_bar_posiY + UI::level_sizeY / 5);
		level_bar_s->setposition(UI::level_bar_sizeX * height / width - UI::level_sizeX * 0.1 * height / width, UI::level_bar_sizeY,
			0.99 - (UI::mnmap_sizeX + UI::level_sizeX * 0.86) * height / width, UI::level_bar_posiY + UI::level_sizeY / 5);
	}
	level_bar->update();
	level_bar_s->update();
	level_bar_len = level_bar->getSizeX();
}

void UI::update() {
	character->update();
	skill->update();
	skill_cd->update();
	skill_frame->update();
	time->update();
	time_bar->update();
	time_bar_s->update();
	minimap_dark->update();
	minimap_light->update();
	
	level->update();
	level_bar->update();
	level_bar_s->update();
}

void UI::changeTimebarSizeY(float rate) {
	if (rate < 0.5) {
		shorter_timer = true;
		//time_bar->bindTexture(time_bar_cut);
	}
	else {
		shorter_timer = false;
		//time_bar->bindTexture(time_bar_png);
	}
	time_bar->setposition(time_bar->getSizeX(), time_bar_len * rate);
	time_bar->update();
	time_bar_s->setposition(time_bar->getSizeX(), time_bar_len * rate);
	time_bar_s->update();
}

void UI::changeLevelbarSizeY(float rate) {
	if (rate < 0.5) {
		shorter_level = true;
		//level_bar->bindTexture(level_bar_cut);
	}
	else {
		shorter_level = false;
		//level_bar->bindTexture(level_bar_png);
	}
	level_bar->setposition(level_bar_len * rate, level_bar->getSizeY());
	level_bar->update();
	level_bar_s->setposition(level_bar_len * rate, level_bar->getSizeY());
	level_bar_s->update();
}

void UI::setPlayerPosition(glm::mat4 model) {
	minimap_dark->setPosition(model);
	minimap_dark->update();
	minimap_light->setPosition(model);
	minimap_light->update();
}

void UI::setPlayerAlicePosition(glm::mat4 model) {
	minimap_dark->setAlice(model);
	minimap_light->setAlice(model);
}


void UI::setUiByPlayerID(int id) {
	// TO DO: update skill png

	if (id == 0) {			// Alice
		char_png = "./images/Alice.png";
		level->setposition(UI::level_sizeX * UI::win_height / UI::win_width, UI::level_sizeY,
			0.99 - (UI::level_sizeX) * UI::win_height / UI::win_width, UI::level_posiY);
		level->update();
		level_bar->setposition(UI::level_bar_sizeX * UI::win_height / UI::win_width - UI::level_sizeX * 0.19 * UI::win_height / UI::win_width, UI::level_bar_sizeY,
			0.99 - (UI::level_sizeX * 0.81) * UI::win_height / UI::win_width, UI::level_bar_posiY + UI::level_sizeY / 5);
		level_bar_len = level_bar->getSizeX();
		level_bar->update();
		level_bar_s->setposition(UI::level_bar_sizeX * UI::win_height / UI::win_width - UI::level_sizeX * 0.19 * UI::win_height / UI::win_width, UI::level_bar_sizeY,
			0.99 - (UI::level_sizeX * 0.81) * UI::win_height / UI::win_width, UI::level_bar_posiY + UI::level_sizeY / 5);
		level_bar_s->update();
		skill->bindTexture(alice_skill_png);
		skill->update();
		skill_frame->bindTexture(alice_skill_frame_png);
		skill_frame->update();
	}
	else if (id == 1) {		// Bob
		char_png = "./images/Bob.png";
		level->setposition(UI::level_sizeX * UI::win_height / UI::win_width, UI::level_sizeY + 0.1,
			0.99 - (UI::mnmap_sizeX + UI::level_sizeX) * UI::win_height / UI::win_width, UI::level_posiY - 0.07);
		level->bindTexture(aware_png);
		level->update();
		skill->bindTexture(bob_skill_png);
		skill->update();
		skill_frame->bindTexture(bob_skill_frame_png);
		skill_frame->update();
	}
	else if (id == 2) {		// Carol
		char_png = "./images/Carol.png";
		level->setposition(UI::level_sizeX * UI::win_height / UI::win_width, UI::level_sizeY + 0.1,
			0.99 - (UI::mnmap_sizeX + UI::level_sizeX) * UI::win_height / UI::win_width, UI::level_posiY - 0.07);
		level->bindTexture(aware_png);
		level->update();
		skill->bindTexture(carol_skill_png);
		skill->update();
		skill_frame->bindTexture(carol_skill_frame_png);
		skill_frame->update();
	}
	else if (id == 3) {		// Dave
		char_png = "./images/Dave.png";
		level->setposition(UI::level_sizeX * UI::win_height / UI::win_width, UI::level_sizeY + 0.1,
			0.99 - (UI::mnmap_sizeX + UI::level_sizeX) * UI::win_height / UI::win_width, UI::level_posiY - 0.07);
		level->bindTexture(aware_png);
		level->update();
		skill->bindTexture(dave_skill_png);
		skill->update();
		skill_frame->bindTexture(dave_skill_frame_png);
		skill_frame->update();
	}
	else {
		return;
	}
	character->bindTexture(UI::char_png);
	
}

void UI::restart() {
	// delete old objs
	delete character;
	delete skill;
	delete skill_cd;
	delete time;
	delete time_bar;
	delete time_bar_s;
	delete minimap_dark;
	delete minimap_light;
	delete level;
	delete level_bar;
	delete level_bar_s;

	// reinit new objs
	character = new graphic2D(UI::char_sizeX, UI::char_sizeY * UI::win_width / UI::win_height,
		UI::char_posiX, UI::char_posiY, true);
	character->bindTexture(UI::char_png);

	skill = new graphic2D(UI::skill_sizeX, UI::skill_sizeY * UI::win_width / UI::win_height,
		UI::char_posiX + UI::char_sizeX, UI::char_posiY, true);
	//skill->bindTexture(UI::skill_png);

	skill_frame = new graphic2D(UI::skill_sizeX, UI::skill_sizeY * UI::win_width / UI::win_height,
		UI::char_posiX + UI::char_sizeX, UI::char_posiY, true);
	//skill_frame->bindTexture(UI::skill_frame_png);

	skill_cd = new graphic2D(UI::skill_sizeX, UI::skill_sizeY * UI::win_width / UI::win_height,
		UI::char_posiX + UI::char_sizeX, UI::char_posiY, true);
	skill_cd->bindTexture(UI::skill_cd_png);

	time = new graphic2D(UI::time_sizeX, UI::time_sizeY * UI::win_width / UI::win_height,
		UI::time_posiX, -1 + UI::char_sizeY * UI::win_width / UI::win_height, true);
	time->bindTexture(UI::time_png);

	time_bar = new graphic2D(UI::time_bar_sizeX, UI::time_bar_sizeY * UI::win_width / UI::win_height - (UI::time_sizeY * UI::win_width / UI::win_height) / 5,
		UI::time_bar_posiX + UI::time_sizeX / 4, -1 + UI::char_sizeY * UI::win_width / UI::win_height + (UI::time_sizeY * UI::win_width / UI::win_height) / 5.4, true);
	time_bar->bindTexture(UI::time_bar_png);
	time_bar_len = time_bar->getSizeY();
	time_bar_s = new graphic2D(UI::time_bar_sizeX, UI::time_bar_sizeY * UI::win_width / UI::win_height - (UI::time_sizeY * UI::win_width / UI::win_height) / 5,
		UI::time_bar_posiX + UI::time_sizeX / 4, -1 + UI::char_sizeY * UI::win_width / UI::win_height + (UI::time_sizeY * UI::win_width / UI::win_height) / 5.4, true);
	time_bar_s->bindTexture(UI::time_bar_cut);

	minimap_dark = new Minimap(UI::mnmap_sizeX * UI::win_height / UI::win_width, UI::mnmap_sizeY,
		0.99 - UI::mnmap_sizeX * UI::win_height / UI::win_width, UI::mnmap_posiY, UI::minimap_dark_png);
	minimap_light = new Minimap(UI::mnmap_sizeX * UI::win_height / UI::win_width, UI::mnmap_sizeY,
		0.99 - UI::mnmap_sizeX * UI::win_height / UI::win_width, UI::mnmap_posiY, UI::minimap_light_png);

	level = new graphic2D(UI::level_sizeX * UI::win_height / UI::win_width, UI::level_sizeY,
		0.99 - (UI::mnmap_sizeX + UI::level_sizeX) * UI::win_height / UI::win_width, UI::level_posiY, true);
	level->bindTexture(UI::insec_png);

	level_bar = new graphic2D(UI::level_bar_sizeX * UI::win_height / UI::win_width - UI::level_sizeX * 0.1 * UI::win_height / UI::win_width, UI::level_bar_sizeY,
		0.99 - (UI::mnmap_sizeX + UI::level_sizeX * 0.86) * UI::win_height / UI::win_width, UI::level_bar_posiY + UI::level_sizeY / 5, true);
	level_bar->bindTexture(UI::level_bar_png);
	level_bar_len = level_bar->getSizeX();
	level_bar_s = new graphic2D(UI::level_bar_sizeX * UI::win_height / UI::win_width - UI::level_sizeX * 0.1 * UI::win_height / UI::win_width, UI::level_bar_sizeY,
		0.99 - (UI::mnmap_sizeX + UI::level_sizeX * 0.86) * UI::win_height / UI::win_width, UI::level_bar_posiY + UI::level_sizeY / 5, true);
	level_bar_s->bindTexture(UI::level_bar_cut);

	shorter_timer = false;
	shorter_level = false;
}