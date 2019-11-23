#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "globals.h"
#include "graphics.h"

class Graphics;

class Player : public Sprite {
public:
	Player();
	Player(Graphics &graphic, float x, float y);

	void draw(Graphics &graphic);
	void update(float elaspedTime);
	void loadUlt(Graphics &graphics);
	void drawUlt(Graphics &graphics);
	void loadLaser(Graphics &graphics);
	void drawLaser(Graphics &graphics);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMovingHoriz();
	void stopMovingVerti();
	void resetLocation();
	int getHealth();

	bool loseHealth(int delta);

	Vector2 getLocation();

	bool attacking = false;
	bool ultUsing = false;
	bool highSpeed = true;
	bool crossMoving = false;

private:
	float _dx, _dy;

	int health = 3;

	SDL_Texture* _masterspark;
	SDL_Texture* _laser;

	Direction _direction;
};

#endif
