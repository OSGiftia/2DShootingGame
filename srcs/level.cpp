#include <SDL.h>

#include "level.h"
#include "graphics.h"

Level::Level() {
	//
}

Level::Level(Graphics &graphics, const std::string &filePath, int _width, int _height) : _size(_size.zero()) {
	loadMap(graphics, filePath, _width, _height);
}

Level::~Level() {
	//
}

void Level::loadMap( Graphics &graphics, const std::string &filePath, int _width, int _height) {
	_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	_size = Vector2(_width, _height);
}

void Level::update(int elapsedTime) {
	//
}

void Level::draw(Graphics &graphics, int x, int y) {
	SDL_Rect sourceRect = { 0, 0, _size.x, _size.y };
	SDL_Rect destRect = { x, y, _size.x, _size.y };
	graphics.blitSurface(_backgroundTexture, &sourceRect, &destRect);
}
