
#include "UI.h"

UI::UI() {
	character = new graphic2D(UI::char_sizeX, UI::char_sizeY * 800 / 600, 
		UI::char_posiX, UI::char_posiY, true);
	character->bindTexture(UI::char_png);

	skill = new graphic2D(UI::skill_sizeX, UI::skill_sizeY * 800 / 600,
		UI::char_posiX + UI::char_sizeX, UI::char_posiY, true);
	skill->bindTexture(UI::skill_png);

	time = new graphic2D(UI::time_sizeX, UI::time_sizeY * 800 / 600,
		UI::time_posiX, -1 + UI::char_sizeY * 800 / 600, true);
	time->bindTexture(UI::time_png);

	time_bar = new graphic2D(UI::time_bar_sizeX, UI::time_bar_sizeY * 800 / 600 - (UI::time_sizeY * 800 / 600)/5,
		UI::time_bar_posiX + UI::time_sizeX / 4, -1 + UI::char_sizeY * 800 / 600 + (UI::time_sizeY * 800 / 600) /5.4, true);
	time_bar->bindTexture(UI::time_bar_png);
	time_bar_len = time_bar->getSizeY();

	minimap = new Minimap(UI::mnmap_sizeX * 600 / 800, UI::mnmap_sizeY,
		0.995 - UI::mnmap_sizeX * 600 / 800, UI::mnmap_posiY);

	level = new graphic2D(UI::level_sizeX * 600 / 800, UI::level_sizeY,
		0.995 - (UI::mnmap_sizeX + UI::level_sizeX) * 600 / 800, UI::level_posiY, true);
	level->bindTexture(UI::level_png);

	level_bar = new graphic2D(UI::level_bar_sizeX * 600 / 800 - UI::level_sizeX * 600 / 800 / 5, UI::level_bar_sizeY,
		0.995 - (UI::mnmap_sizeX + UI::level_sizeX*4/5) * 600 / 800, UI::level_bar_posiY + UI::level_sizeY / 5, true);
	level_bar->bindTexture(UI::level_bar_png);
	level_bar_len = level_bar->getSizeX();
}

UI::~UI() {
	delete character;
	delete skill;
	delete time;
	delete time_bar;
	delete minimap;
	delete level;
	delete level_bar;
}

void UI::draw(const glm::mat4& viewProjMtx, Shader shader) {
	character->draw(viewProjMtx, shader);
	skill->draw(viewProjMtx, shader);
	/*float rate;
	std::cin >> rate;
	changeTimebarSizeY(rate);*/
	time_bar->draw(viewProjMtx, shader);
	time->draw(viewProjMtx, shader);
	minimap->draw(viewProjMtx, shader);

	/*float rate;
	std::cin >> rate;
	changeLevelbarSizeY(rate);*/

	level_bar->draw(viewProjMtx, shader);
	level->draw(viewProjMtx, shader);
}

void UI::setSize(const int& width, const int& height) {
	character->setposition(UI::char_sizeX, UI::char_sizeY * width / height);
	character->update();

	skill->setposition(UI::skill_sizeX, UI::skill_sizeY * width / height);
	skill->update();

	time->setposition(UI::time_sizeX, UI::time_sizeY * width / height, 
		UI::time_posiX, -1 + UI::char_sizeY * width / height);
	time->update();

	time_bar->setposition(UI::time_bar_sizeX, UI::time_sizeY * width / height - (UI::time_sizeY * width / height) / 5,
		UI::time_bar_posiX + UI::time_sizeX / 4, -1 + UI::char_sizeY * width / height + (UI::time_sizeY * width / height) / 5.4);
	time_bar->update();
	time_bar_len = time_bar->getSizeY();

	minimap->setposition(UI::mnmap_sizeX * height / width, UI::mnmap_sizeY,
		0.995 - UI::mnmap_sizeX * height / width, UI::mnmap_posiY);
	minimap->update();

	level->setposition(UI::level_sizeX * height / width, UI::level_sizeY,
		0.995 - (UI::mnmap_sizeX + UI::level_sizeX) * height / width, UI::level_posiY);
	level->update();

	level_bar->setposition(UI::level_bar_sizeX * height / width - UI::level_sizeX * height/width/5, UI::level_bar_sizeY,
		0.995 - (UI::mnmap_sizeX + UI::level_sizeX*4/5) * height / width, UI::level_bar_posiY + UI::level_sizeY / 5);
	level_bar->update();
	level_bar_len = level_bar->getSizeX();
}

void UI::update() {
	character->update();
	skill->update();
	time->update();
	time_bar->update();
	minimap->update();
	level->update();
	level_bar->update();
}

void UI::changeTimebarSizeY(float rate) {
	time_bar->setposition(time_bar->getSizeX(), time_bar_len * rate);
	time_bar->update();
}

void UI::changeLevelbarSizeY(float rate) {
	level_bar->setposition(level_bar_len * rate, level_bar->getSizeY());
	level_bar->update();
}

void UI::setPlayerPosition(glm::mat4 model) {
	minimap->setPosition(model);
	minimap->update();
}
