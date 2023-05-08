#pragma once

#define NUM_OBSTACLE 25
#define GAME_LENGTH 300000
#define LISTEN_TICK 10
#define TICK_TIME 40
#define CAMERA_SPEED 0.3f
#define TURNING_RATIO 4.0f
#define NUM_EVENT_TYPES 6
#define ATTACK_RANGE 2

#define SMALL_OBS 1000
#define MEDIUM_OBS 3000
#define LARGE_OBS 5000
#define SMALL_AWD 1
#define MEDIUM_AWD 3
#define LARGE_AWD 5

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

enum class PlayerStatus
{
	NONE = 0,
	ATTACK = 1,
	SKILL = 2
};

enum class ObstacleState
{
	DESTROYED = 0,
	CURRENTLY_DESTROYING = 1,
	NOT_DESTROYED = 2
};