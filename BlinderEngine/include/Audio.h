#pragma once
#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
#include "../../shared/GlobalVariables.h"
#include "../../shared/GameData.h"
#include "Cube.h"
#include "ObsObject.h"

class Audio {
public:
	static SoLoud::Soloud gSoloud;
	static SoLoud::Wav gwave;
	static SoLoud::Wav aliceSkill_l;
	static SoLoud::Wav aliceSkill_m;
	static SoLoud::Wav aliceSkill_s;
	static SoLoud::Wav bobSkill;
	static SoLoud::Wav carolSkill;
	static SoLoud::Wav daveSkill;
	static SoLoud::Wav ah;
	static SoLoud::Wav attacking;
	static SoLoud::Wav storyBgm;
	static SoLoud::Wav bgm_1;
	static SoLoud::Wav bgm_2;
	static SoLoud::Wav bgm_3;
	static SoLoud::Wav base_track;

	static const char* bgm_wav;
	static const char* win_wav;
	static const char* lose_wav;
	static const char* alice_large_det_wav;
	static const char* alice_medium_det_wav;
	static const char* alice_small_det_wav;
	static const char* bob_skill_wav;
	static const char* carol_skill_wav;
	static const char* dave_skill_wav;
	static const char* ah_wav;
	static const char* attacking_wav;
	static const char* storyBgm_wav;
	static const char* base_track_wav;
	static const char* bgm_1_wav;
	static const char* bgm_2_wav;
	static const char* bgm_3_wav;
	static int assign_id;
	static int level_A;

	static bool break_sign[3];
	static int breaking_h[3];

	static void init();
	static void setid(int);
	static void deinit();

	// load wav
	static void loadBgm();
	static void loadWin();
	static void loadLose();

	// player
	static void playStoryBgm();
	static void playBgm();
	static void playEnd(GameState);

	// skill
	static void playSkillAudio(GameData*, const std::vector<Cube*>&, const std::vector<ObsObject*>&);
	static void playHpLow(GameData*);
	static void playskill(glm::mat4);		// only for offline testing

	static void playBreakObs(GameData*);
};
