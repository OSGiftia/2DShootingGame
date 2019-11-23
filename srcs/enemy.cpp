#include "enemy.h"
#include "graphics.h"

namespace enemy_constants {
	const float WALK_SPEED = -0.2f;
}

Enemy::Enemy() {
	//
}

Enemy::Enemy(Graphics &graphics, float x, float y, int currentLevel) : _x(x), _y(y), levelUp(currentLevel) {
	load(graphics);
}

void Enemy::load(Graphics &graphics) {
	_texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("source/Enemy.png"));
}

void Enemy::draw(Graphics &graphics) {
	SDL_Rect sourceRect = { 0, 0, 94, 137 };
	SDL_Rect destRect = { _x, _y, 94, 137 };
	graphics.blitSurface(_texture, &sourceRect, &destRect);
}

void Enemy::update(float elapsedTime) {
	_x += elapsedTime * enemy_constants::WALK_SPEED * sqrt(levelUp);
}

void Enemy::loseHealth() {
	_health -= 1;
}

bool Enemy::deathCheck() {
	return (_health <= 0) ? true : false;
}
