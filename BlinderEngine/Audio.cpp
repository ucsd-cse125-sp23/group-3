#include "Audio.h"


SoLoud::Soloud Audio::gSoloud;
SoLoud::Wav Audio::gwave;
const char* Audio::bgm_wav;
const char* Audio::win_wav;
const char* Audio::lose_wav;


void Audio::init() {
	Audio::gSoloud.init();
	Audio::bgm_wav = "resources/audio/LessChaoticUnMastered.wav";
	Audio::win_wav = "resources/audio/WinningSound.wav";
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
	int h = Audio::gSoloud.play(Audio::gwave);
	bool l = Audio::gSoloud.getLooping(h);
	Audio::gSoloud.setLooping(h, !l);
}

void Audio::playEnd(GameState gs) {
	Audio::gSoloud.stopAll();
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