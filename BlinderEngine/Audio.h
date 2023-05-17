#pragma once
#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
#include "../../shared/GlobalVariables.h"

class Audio {
public:
	static SoLoud::Soloud gSoloud;
	static SoLoud::Wav gwave;

	static const char* bgm_wav;
	static const char* win_wav;
	static const char* lose_wav;

	static void init();

	static void deinit();

	// load wav
	static void loadBgm();
	static void loadWin();
	static void loadLose();

	// player
	static void playBgm();
	static void playEnd(GameState);
};
