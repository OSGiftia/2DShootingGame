#ifndef SPRITE_H
#define SPRITE_H

#include <SDL_image.h>
#include <string>

class Graphics;

class Sprite {
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);

	virtual ~Sprite();
	virtual void update();

	void draw(Graphics &graphic, int x, int y);

protected:
	float _x, _y;
private:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;

};

#endif
