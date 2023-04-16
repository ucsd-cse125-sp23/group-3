#include "Player.h"

Player::Player(int id): id(id), character(Character::NOT_SELECTED), speed(1), insecurity(0), awareness(0), seeAliceLocation(false) {}

void Player::setCharacter(Character charChoice) {
    character = charChoice;
}

void Player::setInsesurityLevel(int num) {
    insecurity = num;
}

void Player::setAwarenessLevel(int num) {
    awareness = num;
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

int Player::getInsesurityLevel() {
    return insecurity;
}

int Player::getAwarenessLevel() {
    return awareness;
}

bool Player::getSeeAliceLocation() {
    return seeAliceLocation;
}