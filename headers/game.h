#ifndef GAME_H
#define GAME_H

#include <map>

#include "player.h"
#include "level.h"
#include "enemy.h"
#include "collectible.h"

class Graphics;

class Game{
public:
	Game();
	~Game();

	float min(float x, float y);

private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime, Graphics &graphics);
	void init_enemy(Graphics &graphics);
	void init_coll(Graphics &graphics, int x, int y);

	Player _player;

	Level _level;
	Level healthBar;
	Level showScore;
	Level death;

	std::map <int, Level> scoreNum;

	std::map <int, Level> loading;

	std::map <int, Enemy> _enemy;
	bool enemyAvailable[globals::IDEAL_ENEMY_NUM * globals::IDEAL_ENEMY_NUM + 10];

	std::map <int, Coll> _coll;
	bool collAvailable[globals::IDEAL_ENEMY_NUM * globals::IDEAL_ENEMY_NUM + 10];

	int frameCounter = 0;
	int insert_enemy = 0, insert_coll = 0;
	int levelCounter = 0;
	int playerScore = 0;

	bool collInitCall = false;
	bool gameover = false;
	Vector2 positionCache;

};

#endif
