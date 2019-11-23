#include "collectible.h"
#include <iostream>

namespace coll_constant {
	const float MOVE_SPEED = 0.2f;
}

Coll::Coll() {
	//
}

Coll::Coll(Graphics &graphics, int x, int y) : _x(x), _y(y) {
	Coll::load(graphics);
}

void Coll::load(Graphics &graphics) {
	_texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("source/Collectible.png"));
}

void Coll::draw(Graphics &graphics) {
	SDL_Rect sourceRect = {0, 0, 35, 49};
	SDL_Rect destRect = {_x, _y, 35, 49};
	graphics.blitSurface(_texture, &sourceRect, &destRect);
}

void Coll::update(float elapsedTime) {
	switch (_direction)
	{
		case LEFT: {
			//std::cout << "LEFT" << std::endl;
			_x -= elapsedTime * coll_constant::MOVE_SPEED;
			_y += elapsedTime * coll_constant::MOVE_SPEED;
			if (_x <= 0) {
				_direction = DOWN;
			}
			if (_y >= 751) {
				_direction = UP;
			}
		} break;
		case RIGHT: {
			//std::cout << "RIGHT" << std::endl;
			_x += elapsedTime * coll_constant::MOVE_SPEED;
			_y -= elapsedTime * coll_constant::MOVE_SPEED;
			if (_x >= 1245) {
				_direction = UP;
			}
			if (_y <= 0) {
				_direction = DOWN;
			}
		} break;
		case UP: {
			//std::cout << "UP" << std::endl;
			_x -= elapsedTime * coll_constant::MOVE_SPEED;
			_y -= elapsedTime * coll_constant::MOVE_SPEED;
			if (_x <= 0) {
				_direction = RIGHT;
			}
			if (_y <= 0) {
				_direction = LEFT;
			}
		} break;
		case DOWN: {
			//std::cout << "DOWN" << std::endl;
			_x += elapsedTime * coll_constant::MOVE_SPEED;
			_y += elapsedTime * coll_constant::MOVE_SPEED;
			if (_x >= 1245) {
				_direction = LEFT;
			}
			if (_y >= 751) {
				_direction = RIGHT;
			}
		} break;
	}
	//std::cout << elapsedTime << std::endl;
}
