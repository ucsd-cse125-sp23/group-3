#pragma once

#define NUM_OBSTACLE 26
#define GAME_LENGTH 300000
#define LISTEN_TICK 10
#define TICK_TIME 25
#define CAMERA_SPEED 0.5f
#define ALICE_CAMERA_SPEED 0.3f
#define TURNING_RATIO 10.0f
#define NUM_EVENT_TYPES 6
#define ATTACK_RANGE 4
#define ALERT_ALICE 30000
#define MAX_INSECURE 100
#define MAX_AWARENESS 100

#define SMALL_OBS 1000
#define MEDIUM_OBS 3000
#define LARGE_OBS 5000
#define SMALL_ALERT 2
#define MEDIUM_ALERT 5
#define LARGE_ALERT 7
#define SMALL_AWD 10
#define MEDIUM_AWD 20
#define LARGE_AWD 30
#define AWARENESS_THRESHOLD 100

#define SKILL_CD 30000

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
	ATTACK = 4,
	SKILL = 5,
	READY = 6,
	RESTART = 7
};

enum class PlayerStatus
{
	NONE = 0,
	ATTACK = 1,
	SKILL = 2,
	WALK = 3
};

enum class ObstacleState
{
	DESTROYED = 0,
	CURRENTLY_DESTROYING = 1,
	NOT_DESTROYED = 2,
	DETECTED = 3
};