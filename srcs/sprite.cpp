#include <SDL.h>
#include <iostream>
#include <vector>

#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite() {
	//
}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY) : _x(posX), _y(posY) {
	_sourceRect.x = sourceX;
	_sourceRect.y = sourceY;
	_sourceRect.w = width;
	_sourceRect.h = height;

	_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));

	if(_spriteSheet == NULL) {
		std::cout << "Fail to load image" << std::endl;
	}
}


Sprite::~Sprite() {
	//
}

void Sprite::update() {
	//
}

void Sprite::draw(Graphics &graphic, int x, int y) {
	SDL_Rect destinationRectangle = { x, y, _sourceRect.w, _sourceRect.h};
	graphic.blitSurface(_spriteSheet, &_sourceRect, &destinationRectangle);
}
