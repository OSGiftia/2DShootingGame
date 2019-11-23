#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 800 + 100;
	
	const float SPRITE_WIDTH = 0.5f;
	const float SPRITE_HEIGHT = 0.5f;

	const int IDEAL_ENEMY_NUM = 10;
}

enum Direction{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Vector2 {
	int x, y;
	Vector2() : x(0), y(0) {}
	Vector2(int x, int y) : x(x), y(y) {}
	Vector2 zero() {
		return Vector2(0, 0);
	}
};

#endif
