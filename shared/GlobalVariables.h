#pragma once

#define NUM_OBSTACLE 22
#define GAME_LENGTH 300000
#define LISTEN_TICK 10
#define TICK_TIME 40
#define CAMERA_SPEED 0.05f
#define TURNING_RATIO 5.0f
#define NUM_EVENT_TYPES 6

//enum class Character
//{
//	ALICE = 0,
//	BOB = 1,
//	CAROL = 2,
//	DAVE = 3
//};

enum class GameState
{
	READY = 0,
	LOADING = 1,
	IN_GAME = 2,
	WIN = 3,
	LOSE = 4
};

enum class EventType
{
	NOEVENT = 0,
	FORWARD = 1,
	TURN_LEFT = 2,
	TURN_RIGHT = 3,
	ATTACK = 5,
	READY = 6
};