#include "Audio.h"


SoLoud::Soloud Audio::gSoloud;
SoLoud::Wav Audio::gwave;
SoLoud::Wav Audio::bobSkill;
const char* Audio::bgm_wav;
const char* Audio::win_wav;
const char* Audio::lose_wav;
const char* Audio::bob_skill_wav;


void Audio::init() {
	Audio::gSoloud.init();
	Audio::bgm_wav = "resources/audio/LessChaoticUnMastered.wav";
	Audio::win_wav = "resources/audio/WinningSound.wav";
	//Audio::lose_wav = "resources/audio/WinningSound.wav";
	Audio::bob_skill_wav = "resources/audio/StarWars3.wav";
}

void Audio::deinit() {
	Audio::gSoloud.deinit();
}

void Audio::loadBgm() {
	Audio::gwave.load(Audio::bgm_wav);
}

void Audio::loadWin() {
	Audio::gwave.load(Audio::win_wav);
}

void Audio::loadLose() {
	Audio::gwave.load(Audio::win_wav);
}

void Audio::playBgm() {
	Audio::loadBgm();
	int h = Audio::gSoloud.play(Audio::gwave);
	bool l = Audio::gSoloud.getLooping(h);
	Audio::gSoloud.setLooping(h, !l);
}

void Audio::playEnd(GameState gs) {
	Audio::gSoloud.stopAll();
	Audio::init();
	if (gs == GameState::WIN) {
		Audio::loadWin();
	}
	else if (gs == GameState::LOSE) {
		return;
		Audio::loadLose();
	}
	int h = Audio::gSoloud.play(Audio::gwave);
	bool l = Audio::gSoloud.getLooping(h);
	Audio::gSoloud.setLooping(h, !l);
}

void Audio::playSkillAudio(GameData* gd) {
	// Alice skill audio
	if (gd->player_status[0] == (int)PlayerStatus::SKILL) {
	

	}

	// Bob skill audio
	if (gd->player_status[1] == (int)PlayerStatus::SKILL) {
		Audio::bobSkill.load(Audio::bob_skill_wav);
		float* f = glm::value_ptr(gd->location_B);
		int h = Audio::gSoloud.play3d(bobSkill, f[12], f[13], f[14]);
	}

	// Carol skill audio
	if (gd->player_status[2] == (int)PlayerStatus::SKILL) {
		

	}

	// Dave skill audio
	if (gd->skill_cd[3] >= 20000) {

	}
	else {

	}
}