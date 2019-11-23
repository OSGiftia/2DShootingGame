#ifndef COLL_H
#define COLL_H

#include <SDL.h>

#include "graphics.h"
#include "globals.h"

class Graphics;

class Coll {
public:
	Coll();
	Coll(Graphics &graphics, int x, int y);
	
	void load(Graphics &graphics);
	void draw(Graphics &graphics);
	void update(float elapsedTIme);

	float _x, _y;

private:
	SDL_Texture* _texture;

	Direction _direction = UP;

};

#endif // !COLL_H
