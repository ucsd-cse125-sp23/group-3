#define NUM_OBSTACLE 22
#define GAME_LENGTH 300

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
	FORWARD = 0,
	BACKWARD = 1,
	TURN_RIGHT = 2,
	TURN_LEFT = 3,
	ATTACK = 4
};