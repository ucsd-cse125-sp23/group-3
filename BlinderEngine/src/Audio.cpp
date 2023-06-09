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
SoLoud::Wav Audio::attacking;
SoLoud::Wav Audio::storyBgm;
SoLoud::Wav Audio::base_track;
SoLoud::Wav Audio::bgm_1;
SoLoud::Wav Audio::bgm_2;
SoLoud::Wav Audio::bgm_3;

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
const char* Audio::attacking_wav;
const char* Audio::storyBgm_wav;
const char* Audio::base_track_wav;
const char* Audio::bgm_1_wav;
const char* Audio::bgm_2_wav;
const char* Audio::bgm_3_wav;
int Audio::assign_id;
int Audio::level_A;
bool Audio::break_sign[3];
int Audio::breaking_h[3];


void Audio::init() {
	Audio::gSoloud.init();
	//Audio::bgm_wav = "resources/audio/MoreChaoticMix.wav";
	Audio::win_wav = "resources/audio/WinningSound.wav";
	Audio::lose_wav = "resources/audio/LosingSound.wav";			
	Audio::alice_large_det_wav = "resources/audio/LargeDetect.wav";
	Audio::alice_medium_det_wav = "resources/audio/MedObstacle.wav";
	Audio::alice_small_det_wav = "resources/audio/PinObstacle.wav";
	Audio::bob_skill_wav = "resources/audio/Bob_skill.wav";
	Audio::carol_skill_wav = "resources/audio/Carol_skill.wav";
	Audio::dave_skill_wav = "resources/audio/David_skill.wav";
	Audio::ah_wav = "resources/audio/ah.wav";				
	Audio::attacking_wav = "resources/audio/attacking.wav";
	//Audio::storyBgm_wav = "resources/audio/LessChaoticUnMastered.wav";
	Audio::base_track_wav = "resources/audio/BasetrackMixing-6.wav";
	Audio::bgm_1_wav = "resources/audio/Layer1.wav";
	Audio::bgm_2_wav = "resources/audio/Layer2Mixed.wav";
	Audio::bgm_3_wav = "resources/audio/Layer3Mixed.wav";

	/*Audio::assign_id = assign_id;
	Audio::level_A = 0;
	for (int i = 0; i < 3; i++) {
		Audio::break_sign[i] = false;
		Audio::breaking_h[i] = 0;
	}*/
	
	Audio::aliceSkill_l.load(Audio::alice_large_det_wav);
	Audio::aliceSkill_m.load(Audio::alice_medium_det_wav);
	Audio::aliceSkill_s.load(Audio::alice_small_det_wav);
	Audio::bobSkill.load(Audio::bob_skill_wav);
	Audio::carolSkill.load(Audio::carol_skill_wav);
	Audio::daveSkill.load(Audio::dave_skill_wav);
	Audio::ah.load(Audio::ah_wav);
	Audio::attacking.load(Audio::attacking_wav);
	Audio::base_track.load(Audio::base_track_wav);
	Audio::bgm_1.load(Audio::bgm_1_wav);
	Audio::bgm_2.load(Audio::bgm_2_wav);
	Audio::bgm_3.load(Audio::bgm_3_wav);
}

void Audio::setid(int id) {
	Audio::assign_id = id;
	Audio::level_A = 0;
	for (int i = 0; i < 3; i++) {
		Audio::break_sign[i] = false;
		Audio::breaking_h[i] = 0;
	}
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

void Audio::playStoryBgm() {
	Audio::gSoloud.stopAll();
	int h = Audio::gSoloud.play(Audio::base_track, 0.2);
	bool l = Audio::gSoloud.getLooping(h);
	Audio::gSoloud.setLooping(h, !l);
}

void Audio::playBgm() {
	Audio::gSoloud.stopAll();
	//int h = Audio::gSoloud.play(Audio::gwave, 0.2);
	int h = Audio::gSoloud.play(Audio::base_track);
	bool l = Audio::gSoloud.getLooping(h);
	Audio::gSoloud.setLooping(h, !l);

	int h1= Audio::gSoloud.play3d(Audio::bgm_1, -30.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	bool l1 = Audio::gSoloud.getLooping(h1);
	Audio::gSoloud.setLooping(h1, !l1);
	gSoloud.set3dSourceAttenuation(h1, 2, 1.0);
	gSoloud.set3dSourceMinMaxDistance(h1, 0.4, 100);

	int h2 = Audio::gSoloud.play3d(Audio::bgm_2, -30.0f, 0.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	bool l2 = Audio::gSoloud.getLooping(h2);
	Audio::gSoloud.setLooping(h2, !l2);
	gSoloud.set3dSourceAttenuation(h2, 2, 1.0);
	gSoloud.set3dSourceMinMaxDistance(h2, 0.4, 100);


	int h3 = Audio::gSoloud.play3d(Audio::bgm_3, 60.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	bool l3 = Audio::gSoloud.getLooping(h3);
	Audio::gSoloud.setLooping(h3, !l3);
	gSoloud.set3dSourceAttenuation(h3, 2, 1.0);
	gSoloud.set3dSourceMinMaxDistance(h3, 0.4, 100);

	gSoloud.update3dAudio();
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
				h = Audio::gSoloud.play3d(aliceSkill_l, f[12], f[13], f[14], 0.0f, 0.0f, 0.0f, 15.0f);
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

void Audio::playBreakObs(GameData* gd) {
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
	for (int i = 1; i <= 3; i++) {
		if (gd->player_status[i] != (int)PlayerStatus::ATTACK) {
			if (Audio::break_sign[i - 1] == true) {
				Audio::gSoloud.stop(breaking_h[i - 1]);
			}
			Audio::break_sign[i - 1] = false;
		}
		else {
			if (Audio::break_sign[i - 1] == true) {
				continue;
			}
			else {
				// play sound
				float* f = NULL;
				if (i == 1) {
					f = glm::value_ptr(gd->location_B);
				}
				else if (i == 2) {
					f = glm::value_ptr(gd->location_C);
				}
				else if (i == 3) {
					f = glm::value_ptr(gd->location_D);
				}
				Audio::breaking_h[i-1] = Audio::gSoloud.play3d(attacking, f[12], f[13], f[14]);
				gSoloud.set3dSourceAttenuation(Audio::breaking_h[i-1], 2, 1.0);
				gSoloud.set3dSourceMinMaxDistance(Audio::breaking_h[i-1], 0.4, 50);
				gSoloud.set3dListenerPosition(player_pos[12], player_pos[13], player_pos[14]);
				gSoloud.update3dAudio();

				bool l = Audio::gSoloud.getLooping(Audio::breaking_h[i-1]);
				Audio::gSoloud.setLooping(Audio::breaking_h[i-1], !l);
				Audio::break_sign[i - 1] = true;
			}
		}

	}

}