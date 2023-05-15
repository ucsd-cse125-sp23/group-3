#pragma once

#include "Event.h"
#include "GameData.h"
#include <iostream>

class Packet {
public:
	static void serialize(GameData* gd, char* buffer);
	static GameData deserializeGameData(char* buffer);

	static void serialize(Event* event, char* buffer);
	static Event deserializeEvent(char* buffer);

	static void serialize(const std::vector<int>& eventRecord, char* buffer);
	static std::vector<int> deserializeEventRecords(char* buffer);

	static void serializeButtonStatus(const std::vector<int>& buttonStatus, char* buffer);
	static std::vector<int> deserializeButtonStatus(char* buffer);

	// Used in serialize and deserialize functions
	static void mat2str(const glm::mat4&, char*& buffer);
	static void vec2str(const std::vector<int>&, char*& buffer, int vec_length);
	static glm::mat4 str2mat(char*& buffer);
	static std::vector<int> str2vec(char*& buffer, int vec_length);
};