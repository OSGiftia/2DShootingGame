#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include "globals.h"
#include "graphics.h"

class Graphics;

class Enemy{
public:
	Enemy();
	Enemy(Graphics &graphics, float x, float y, int currentLevel);

	void load(Graphics &graphics);
	void draw(Graphics &graphics);
	void update(float elapsedTIme);

	void loseHealth();
	bool deathCheck();

	float _x, _y;

private:

	int levelUp;
	int _health = 250;

	SDL_Texture* _texture;
};

#endif
