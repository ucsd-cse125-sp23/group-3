#include "Audio.h"


SoLoud::Soloud Audio::gSoloud;
SoLoud::Wav Audio::gwave;
SoLoud::Wav Audio::aliceSkill_l;
SoLoud::Wav Audio::aliceSkill_m;
SoLoud::Wav Audio::aliceSkill_s;
SoLoud::Wav Audio::bobSkill;
SoLoud::Wav Audio::carolSkill;
SoLoud::Wav Audio::daveSkill;
SoLoud::Wav Audio::ah;
const char* Audio::bgm_wav;
const char* Audio::win_wav;
const char* Audio::lose_wav;
const char* Audio::alice_large_det_wav;
const char* Audio::alice_medium_det_wav;
const char* Audio::alice_small_det_wav;
const char* Audio::bob_skill_wav;
const char* Audio::carol_skill_wav;
const char* Audio::dave_skill_wav;
const char* Audio::ah_wav;
int Audio::assign_id;
int Audio::level_A;


void Audio::init(int assign_id) {
	Audio::gSoloud.init();
	Audio::bgm_wav = "resources/audio/LessChaoticUnMastered.wav";
	Audio::win_wav = "resources/audio/WinningSound.wav";
	Audio::lose_wav = "resources/audio/WinningSound.wav";			// TODO: change wav
	Audio::alice_large_det_wav = "resources/audio/LargeDetect.wav";
	Audio::alice_medium_det_wav = "resources/audio/MedObstacle.wav";
	Audio::alice_small_det_wav = "resources/audio/PinObstacle.wav";
	Audio::bob_skill_wav = "resources/audio/StarWars3.wav";
	Audio::carol_skill_wav = "resources/audio/StarWars3.wav";
	Audio::dave_skill_wav = "resources/audio/StarWars3.wav";
	Audio::ah_wav = "resources/audio/ah.wav";				// TODO: change wav
	
	Audio::assign_id = assign_id;
	Audio::level_A = 0;

	Audio::aliceSkill_l.load(Audio::alice_large_det_wav);
	Audio::aliceSkill_m.load(Audio::alice_medium_det_wav);
	Audio::aliceSkill_s.load(Audio::alice_small_det_wav);
	Audio::bobSkill.load(Audio::bob_skill_wav);
	Audio::carolSkill.load(Audio::carol_skill_wav);
	Audio::daveSkill.load(Audio::dave_skill_wav);
	Audio::ah.load(Audio::ah_wav);
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
	Audio::gwave.load(Audio::lose_wav);
}

void Audio::playBgm() {
	Audio::loadBgm();
	int h = Audio::gSoloud.play(Audio::gwave, 0.2);
	bool l = Audio::gSoloud.getLooping(h);
	Audio::gSoloud.setLooping(h, !l);
}

void Audio::playEnd(GameState gs) {
	Audio::gSoloud.stopAll();
	//Audio::init();
	if (gs == GameState::WIN) {
		Audio::loadWin();
	}
	else if (gs == GameState::LOSE) {
		Audio::loadLose();
	}
	int h = Audio::gSoloud.play(Audio::gwave);
	bool l = Audio::gSoloud.getLooping(h);
	Audio::gSoloud.setLooping(h, !l);
}

void Audio::playSkillAudio(GameData* gd, const std::vector<Cube*>& obs, const std::vector<ObsObject*>& pos) {
	float* player_pos = NULL;
	if (Audio::assign_id == 0) {
		player_pos = glm::value_ptr(gd->location_A);
	}
	else if (Audio::assign_id == 1) {
		player_pos = glm::value_ptr(gd->location_B);
	}
	else if (Audio::assign_id == 2) {
		player_pos = glm::value_ptr(gd->location_C);
	}
	else if (Audio::assign_id == 3) {
		player_pos = glm::value_ptr(gd->location_D);
	}
	else {
		// error
		return;
	}

	// Alice skill audio
	if (gd->player_status[0] == (int)PlayerStatus::SKILL && Audio::assign_id == 0) {
		int i;
		for (i = 0; i < gd->obstacle_states.size(); i++) {
			if (gd->obstacle_states[i] == (int)ObstacleState::DETECTED) {
				break;
			}
		}
		if (i < gd->obstacle_states.size()) {
			const float* f = glm::value_ptr(obs[i]->getModel());
			int h = 0;
			if (pos[i]->type == 1) {
				h = Audio::gSoloud.play3d(aliceSkill_s, f[12], f[13], f[14]);
			}
			else if (pos[i]->type == 2) {
				h = Audio::gSoloud.play3d(aliceSkill_m, f[12], f[13], f[14]);
			}
			else if (pos[i]->type == 3) {
				h = Audio::gSoloud.play3d(aliceSkill_l, f[12], f[13], f[14]);
			}
			gSoloud.set3dSourceAttenuation(h, 2, 1.0);
			gSoloud.set3dSourceMinMaxDistance(h, 0.4, 50);
			gSoloud.set3dListenerPosition(player_pos[12], player_pos[13], player_pos[14]);
			gSoloud.update3dAudio();
		}
	}

	// Bob skill audio
	if (gd->player_status[1] == (int)PlayerStatus::SKILL) {
		float* f = glm::value_ptr(gd->location_B);
		int h = Audio::gSoloud.play3d(bobSkill, f[12], f[13], f[14]);
		gSoloud.set3dSourceAttenuation(h, 2, 1.0);
		gSoloud.set3dSourceMinMaxDistance(h, 0.4, 50);
		gSoloud.set3dListenerPosition(player_pos[12], player_pos[13], player_pos[14]);
		gSoloud.update3dAudio();
	}

	// Carol skill audio
	if (gd->player_status[2] == (int)PlayerStatus::SKILL) {
		float* f = glm::value_ptr(gd->location_C);
		int h = Audio::gSoloud.play3d(bobSkill, f[12], f[13], f[14]);
		gSoloud.set3dSourceAttenuation(h, 2, 1.0);
		gSoloud.set3dSourceMinMaxDistance(h, 0.4, 50);
		gSoloud.set3dListenerPosition(player_pos[12], player_pos[13], player_pos[14]);
		gSoloud.update3dAudio();
	}

	// Dave skill audio
	if (gd->player_status[3] == (int)PlayerStatus::SKILL) {
		float* f = glm::value_ptr(gd->location_D);
		int h = Audio::gSoloud.play3d(bobSkill, f[12], f[13], f[14]);
		gSoloud.set3dSourceAttenuation(h, 2, 1.0);
		gSoloud.set3dSourceMinMaxDistance(h, 0.4, 50);
		gSoloud.set3dListenerPosition(player_pos[12], player_pos[13], player_pos[14]);
		gSoloud.update3dAudio();
	}
}

void Audio::playHpLow(GameData* gd) {
	int curr = gd->level_A;
	if (curr > Audio::level_A && Audio::assign_id == 0) {		// Alice low hp
		gSoloud.play(ah, 0.5);
		Audio::level_A = curr;
	}
}

void Audio::playskill(glm::mat4 mat) {
	//Audio::bobSkill.set3dAttenuation(1000.0);
	Audio::bobSkill.load(Audio::bob_skill_wav);
	float* f = glm::value_ptr(mat);
	int h = Audio::gSoloud.play3d(Audio::bobSkill, 0, 0, 0);
	gSoloud.set3dSourceAttenuation(h, 2, 1.0);
	//gSoloud.set3dSourcePosition(h, 0, 0, 0);
	gSoloud.set3dSourceMinMaxDistance(h, 0.4, 50);
	gSoloud.set3dListenerPosition(f[12], f[13], f[14]);
	gSoloud.update3dAudio();
}