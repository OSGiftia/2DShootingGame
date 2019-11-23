#include "player.h"
#include "graphics.h"

namespace player_constants {
	const float WALK_SPEED = 0.3f;
}

Player::Player() {
	//
}

Player::Player(Graphics &graphics, float x, float y) : Sprite(graphics, "source/Player.png", 0, 0, 100, 100, 100, 100) {
	graphics.loadImage("source/Player.png");
	//Player::loadUlt(graphics);
	Player::loadLaser(graphics);
}

void Player::draw(Graphics &graphics) {
	Sprite::draw(graphics, _x, _y);
}

/*void Player::loadUlt(Graphics &masterspark) {
	_masterspark = SDL_CreateTextureFromSurface(masterspark.getRenderer(), masterspark.loadImage("source/Player.png"));
}

void Player::drawUlt(Graphics &masterspark) {
	SDL_Rect sourceRect = { 0, 0, 200, 200 };
	SDL_Rect destRect = { _x + 85, _y + 36, 200, 200 };
	masterspark.blitSurface(_masterspark, &sourceRect, &destRect);
}*/

void Player::loadLaser(Graphics &laser) {
	_laser = SDL_CreateTextureFromSurface(laser.getRenderer(), laser.loadImage("source/Laser.png"));
}

void Player::drawLaser(Graphics &laser) {
	SDL_Rect sourceRect = { 0, 22, 1400, 6 };
	SDL_Rect destRect = { _x + 85, _y + 43, 1400, 5 };
	laser.blitSurface(_laser, &sourceRect, &destRect);
}

void Player::moveLeft() {
	_dx = -player_constants::WALK_SPEED;
	_direction = LEFT;
	if (highSpeed == true) {
		_dx *= 2;
	}
	if (crossMoving == true) {
		_dx /= 1.4142;
	}
}

void Player::moveRight() {
	_dx = player_constants::WALK_SPEED;
	_direction = RIGHT;
	if (highSpeed == true) {
		_dx *= 2;
	}
	if (crossMoving == true) {
		_dx /= 1.4142;
	}
}

void Player::moveUp() {
	_dy = -player_constants::WALK_SPEED;
	_direction = UP;
	if (highSpeed == true) {
		_dy *= 2;
	}
	if (crossMoving == true) {
		_dy /= 1.4142;
	}
}

void Player::moveDown() {
	_dy = player_constants::WALK_SPEED;
	_direction = DOWN;
	if (highSpeed == true) {
		_dy *= 2;
	}
	if (crossMoving == true) {
		_dy /= 1.4142;
	}
}

void Player::stopMovingHoriz() {
	_dx = 0.0f;
}

void Player::stopMovingVerti() {
	_dy = 0.0f;
}

void Player::resetLocation() {
	_x = 100;
	_y = 100;
	_dx = 0;
	_dy = 0;
}

void Player::update(float elaspedTime) {
	float _posNewX = _x + _dx * elaspedTime, _posNewY = _y + _dy * elaspedTime;
	if (_posNewX >= 0 && _posNewX <= 1180) {
		_x += _dx * elaspedTime;
	}
	if (_posNewY >= 0 && _posNewY <= 700) {
		_y += _dy * elaspedTime;
	}
	
}

int Player::getHealth() {
	return health;
}

bool Player::loseHealth(int delta) {
	health -= delta;
	if (health > 3) {
		health = 3;
	}
	return (health <= 0);
}

Vector2 Player::getLocation() {
	return Vector2(_x, _y);
}
