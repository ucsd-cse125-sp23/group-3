#pragma once

#include "Event.h"
#include "GameData.h"
#include <iostream>

class Packet{
public:
	static void serialize(GameData* gd, char* buffer);
	static GameData deserializeGameData(char* buffer);

	static void mat2str(const glm::mat4&, char* &buffer);
	static void vec2str(const vector<int>&, char* &buffer);
	static glm::mat4 str2mat(char* &buffer);
	static vector<int> str2vec(char* &buffer);

	static void serialize(Event* event, char* buffer);
	static Event deserializeEvent(char* buffer);
}