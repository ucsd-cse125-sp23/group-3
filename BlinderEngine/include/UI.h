#pragma once

#include "graphic2D.h"
#include "Minimap.h"
#include "DaeObject.h"
#include "core.h"


class UI {
public:
	const double char_sizeX = 0.2;
	const double char_sizeY = 0.2;
	const double char_posiX = -0.995;
	const double char_posiY = -0.995;
	const char* char_png = "./images/Alice.png";

	const double skill_sizeX = 0.17;
	const double skill_sizeY = 0.17;
	//const double skill_posiX = -0.995;
	const double skill_posiY = -0.995;
	const char* alice_skill_png = "./images/Alice_skill.png";
	const char* alice_skill_frame_png = "./images/Alice_frame.png";
	const char* bob_skill_png = "./images/stop_skill.png";
	const char* bob_skill_frame_png = "./images/stop_frame.png";
	const char* carol_skill_png = "./images/Light_skill.png";
	const char* carol_skill_frame_png = "./images/Light_frame.png";
	const char* dave_skill_png = "./images/pass_skill.png";
	const char* dave_skill_frame_png = "./images/pass_frame.png";
	const char* skill_cd_png = "./images/oc.png";

	const double time_sizeX = 0.15;
	const double time_sizeY = 0.675;
	const double time_posiX = -0.96;
	//const double time_posiY = -0.8;
	const char* time_png = "./images/timebar-fillempty.png";

	const double time_bar_sizeX = time_sizeX / 1.8;
	const double time_bar_sizeY = time_sizeY;
	const double time_bar_posiX = time_posiX;
	//const double time_bar_posiY = -0.8;
	const char* time_bar_png = "./images/timebar-fill.png";
	const char* time_bar_cut = "./images/timebar-fill-cut.png";

	const double mnmap_sizeX = 0.3 * 2 / sqrt(3);
	const double mnmap_sizeY = 0.3;
	//const double mnmap_posiX = 0.695;
	const double mnmap_posiY = 0.68;
	//const char* minimap_png = "./images/test2.png";
	const char* minimap_dark_png = "./images/map_dark.png";
	const char* minimap_light_png = "./images/map_light.png";

	const double level_sizeX = 0.675;
	const double level_sizeY = 0.15;
	//const double level_posiX = 0.2;
	const double level_posiY = 0.8;
	const char* insec_png = "./images/Insecurity-empty.png";
	const char* aware_png = "./images/awareness-empty.png";

	const double level_bar_sizeX = level_sizeX;
	const double level_bar_sizeY = level_sizeY / 2;
	//const double level_bar_posiX = 0.2;
	const double level_bar_posiY = 0.8;
	const char* level_bar_png = "./images/awarenessinsecurity-fill.png";
	const char* level_bar_cut = "./images/awarenessinsecurity-fill-cut.png";

private:
	graphic2D* character;
	graphic2D* skill;
	graphic2D* skill_frame;
	graphic2D* skill_cd;
	graphic2D* time;
	graphic2D* time_bar;
	graphic2D* time_bar_s;
	float time_bar_len;
	bool shorter_timer;
	Minimap* minimap_dark;
	Minimap* minimap_light;
	graphic2D* level;
	graphic2D* level_bar;
	graphic2D* level_bar_s;
	float level_bar_len;
	bool shorter_level;
	int win_height;
	int win_width;
	//int assigned_id;
public:
	UI();
	~UI();

	void draw(const glm::mat4& viewProjMtx, StaticShader shader, int playerID, int cd_remain);
	void setSize(const int& width, const int& height, int playerId);
	void update();
	void changeTimebarSizeY(float rate);
	void changeLevelbarSizeY(float rate);
	void setPlayerPosition(glm::mat4 model);
	void setUiByPlayerID(int);
	void setPlayerAlicePosition(glm::mat4 model);
	void restart();
};
