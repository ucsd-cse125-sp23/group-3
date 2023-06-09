#include "Player.h"

Player::Player(int id): id(id), character(Character::NOT_SELECTED), speed(1), level(0), seeAliceLocation(false) {}

void Player::setCharacter(Character charChoice) {
    character = charChoice;
}

void Player::setLevel(int num) {
    level = num;
}

void Player::setSeeAliceLocation(bool visible) {
    seeAliceLocation = visible;
}

int Player::getPlayerId() {
    return id;
}

Character Player::getCharacter() {
    return character;
}

int Player::getLevel() {
    return level;
}

bool Player::getSeeAliceLocation() {
    return seeAliceLocation;
}

bool Player::updateByGD(GameData* gd) {
	if (id == 0) {			// Alice
		setLevel(gd->level_A);
	}
	else if (id == 1) {		// Bob
		setLevel(gd->level_B);
	}
	else if (id == 2) {		// Carol
		setLevel(gd->level_C);
	}
	else if (id == 3) {		// Dave
		setLevel(gd->level_D);
	}
	else {
		return false;
	}
	return true;
}