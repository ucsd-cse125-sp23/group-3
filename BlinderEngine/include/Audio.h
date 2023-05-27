#pragma once
#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
#include "../../shared/GlobalVariables.h"
#include "../../shared/GameData.h"

class Audio {
public:
	static SoLoud::Soloud gSoloud;
	static SoLoud::Wav gwave;
	static SoLoud::Wav bobSkill;

	static const char* bgm_wav;
	static const char* win_wav;
	static const char* lose_wav;
	static const char* bob_skill_wav;

	static void init();

	static void deinit();

	// load wav
	static void loadBgm();
	static void loadWin();
	static void loadLose();

	// player
	static void playBgm();
	static void playEnd(GameState);

	// skill
	static void playSkillAudio(GameData*);
	static void playskill(glm::mat4);
};
