#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "graphics.h"
#include "globals.h"

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &_window, &_renderer);
	SDL_SetWindowTitle(_window, "2DPixelShootingGame");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
	if (_spriteSheet.count(filePath) == 0) {
		_spriteSheet[filePath] = IMG_Load(filePath.c_str());
	}
	return _spriteSheet[filePath];
}

void Graphics::blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
	SDL_RenderCopy(_renderer, source, sourceRectangle, destinationRectangle);

}

void Graphics::flip() {
	SDL_RenderPresent(_renderer);
}

void Graphics::clear() {
	SDL_RenderClear(_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
	return _renderer;
}
