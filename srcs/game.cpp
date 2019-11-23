#include <SDL.h>
#include <ctime>
#include <sstream>

#include "game.h"
#include "graphics.h"
#include "input.h"

namespace {
	const float FPS = 60;
	const float FRAME_TIME = 1000 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	memset(enemyAvailable, false, sizeof(enemyAvailable));
	memset(collAvailable, false, sizeof(collAvailable));
	frameCounter = 0;
	insert_coll = 0;
	insert_enemy = 0;
	levelCounter = 0;
	gameover = false;
	gameLoop();
}

Game::~Game() {
	//
}

float Game::min(float x, float y) {
	return (x > y) ? y : x;
}

void Game::gameLoop() {
	srand(time(NULL));
	Graphics graphics;
	Input input;
	SDL_Event event;

	_player = Player(graphics, 100, 100);
	_level = Level(graphics, "source/Background.png", 1280, 800);
	showScore = Level(graphics, "source/Score.png", 600, 100);
	healthBar = Level(graphics, "source/Heart.png", 100, 100);
	death = Level(graphics, "source/Noob.png", 1280, 800);
	for (int num = 0; num <= 9; num++) {
		std::ostringstream tempFilePathA;
		tempFilePathA << "source/" << num << ".png";
		scoreNum.insert(std::pair<int, Level>(num, Level(graphics, tempFilePathA.str(), 100, 100)));
	}
	for (int levelNum = 1; levelNum <= 4; levelNum++) {
		std::ostringstream tempFilePathB;
		tempFilePathB << "source/lvl" << levelNum << ".png";
		loading.insert(std::pair<int, Level>(levelNum, Level(graphics, tempFilePathB.str(), 1280, 800)));
	}

	float LAST_UPDATE_TIME = SDL_GetTicks();

	while (true) {

		if (gameover == true) {
			SDL_Delay(3000);
			return;
		}
		
		if (_enemy.empty() && _coll.empty() && insert_enemy == globals::IDEAL_ENEMY_NUM * levelCounter) {
			insert_coll = 0;
			insert_enemy = 0;
			frameCounter = 0;
			gameover = false;
			memset(enemyAvailable, false, sizeof(enemyAvailable));
			memset(collAvailable, false, sizeof(collAvailable));
			_player.resetLocation();
			_player.loseHealth(-1);
			levelCounter++;
			draw(graphics);
			SDL_Delay(3000);
			if (levelCounter > 3) {
				return;
			}
		}

		init_enemy(graphics);

		input.beginNewFrame();
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyPressedEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyReleasedEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return ;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return ;
		}
		
		if (input.isKeyHeld(SDL_SCANCODE_LSHIFT) == true) {
			_player.highSpeed = false;
		}
		else {
			_player.highSpeed = true;
		}

		if ((input.isKeyHeld(SDL_SCANCODE_LEFT) || input.isKeyHeld(SDL_SCANCODE_RIGHT)) && (input.isKeyHeld(SDL_SCANCODE_UP) || input.isKeyHeld(SDL_SCANCODE_DOWN))) {
			_player.crossMoving = true;
		}
		else {
			_player.crossMoving = false;
		}

		if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
			_player.moveLeft();
		}
		if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
			_player.moveRight();
		}
		if (input.isKeyHeld(SDL_SCANCODE_UP) == true) {
			_player.moveUp();
		}
		if (input.isKeyHeld(SDL_SCANCODE_DOWN) == true) {
			_player.moveDown();
		}
		if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
			_player.stopMovingHoriz();
		}
		if (!input.isKeyHeld(SDL_SCANCODE_UP) && !input.isKeyHeld(SDL_SCANCODE_DOWN)) {
			_player.stopMovingVerti();
		}

		if (input.isKeyHeld(SDL_SCANCODE_Z)) {
			_player.attacking = true;
		}
		else {
			_player.attacking = false;
		}
		/*if (input.isKeyHeld(SDL_SCANCODE_X)) {
			_player.ultUsing = true;
		}
		else{
			_player.ultUsing = false;
		}*/

		const float CURRENT_TIME = SDL_GetTicks();
		float ELAPSED_TIME = CURRENT_TIME - LAST_UPDATE_TIME;
		update(min(ELAPSED_TIME, FRAME_TIME), graphics);
		LAST_UPDATE_TIME = CURRENT_TIME;

		draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();

	_level.draw(graphics, 0, 0);
	_player.draw(graphics);
	if (_player.attacking == true && _player.ultUsing == false) {
		_player.drawLaser(graphics);
	}
	/*if (_player.ultUsing == true) {
		_player.drawUlt(graphics);
	}*/
	
	for (int index_coll = 0; index_coll < globals::IDEAL_ENEMY_NUM * levelCounter; index_coll++) {
		if (collAvailable[index_coll] == true) {
			_coll[index_coll].draw(graphics);
		}
	}

	for (int index_enemy = 0; index_enemy < globals::IDEAL_ENEMY_NUM * levelCounter; index_enemy++) {
		if (enemyAvailable[index_enemy] == true) {
			_enemy[index_enemy].draw(graphics);
		}
	}

	for (int hearts_output = 1; hearts_output <= _player.getHealth(); hearts_output++) {
		healthBar.draw(graphics, hearts_output * 100 - 100, 800);
	}

	showScore.draw(graphics, 605, 800);

	scoreNum[playerScore / 1000].draw(graphics, 955, 800);
	scoreNum[(playerScore % 1000) / 100].draw(graphics, 1030, 800);
	scoreNum[(playerScore % 100) / 10].draw(graphics, 1105, 800);
	scoreNum[playerScore % 10].draw(graphics, 1180, 800);
	
	if (frameCounter == 0) {
		loading[levelCounter].draw(graphics, 0, 0);
	}

	if (gameover == true) {
		death.draw(graphics, 0, 0);
	}

	graphics.flip();
}

void Game::update(float elapsedTime, Graphics &graphics) {
	_player.update(elapsedTime);
	for (int index_enemy = 0; index_enemy < globals::IDEAL_ENEMY_NUM * levelCounter; index_enemy++) {
		if (enemyAvailable[index_enemy] == true) {
			_enemy[index_enemy].update(elapsedTime);

			if ((_player.attacking) && !(_player.ultUsing) && (_enemy[index_enemy]._x + 94 > _player.getLocation().x + 85) && !((_enemy[index_enemy]._y > _player.getLocation().y + 48) || (_enemy[index_enemy]._y + 137 < _player.getLocation().y + 43))) {
				_enemy[index_enemy].loseHealth();
			}
			if (_enemy[index_enemy].deathCheck() == true) {
				playerScore += 10;
				init_coll(graphics, _enemy[index_enemy]._x, _enemy[index_enemy]._y);
				_enemy.erase(index_enemy);
				enemyAvailable[index_enemy] = false;
			}
			if (!((_enemy[index_enemy]._x + 94 < _player.getLocation().x + 44) || (_enemy[index_enemy]._x > _player.getLocation().x + 64)) && !((_enemy[index_enemy]._y + 139 < _player.getLocation().y + 42) || (_enemy[index_enemy]._y > _player.getLocation().y + 58))) {
				gameover = _player.loseHealth(1);
				_enemy.erase(index_enemy);
				enemyAvailable[index_enemy] = false;
			}
			if (_enemy[index_enemy]._x <= 0) {
				_enemy.erase(index_enemy);
				enemyAvailable[index_enemy] = false;
			}
		}
	}
	_level.update(elapsedTime);
	for (int index_coll = 0; index_coll < globals::IDEAL_ENEMY_NUM * levelCounter; index_coll++) {
		if (collAvailable[index_coll] == true) {
			_coll[index_coll].update(elapsedTime);
			if (!((_coll[index_coll]._x + 35 < _player.getLocation().x + 44) || (_coll[index_coll]._x > _player.getLocation().x + 64)) && !((_coll[index_coll]._y + 49 < _player.getLocation().y + 42) || (_coll[index_coll]._y > _player.getLocation().y + 58))) {
				playerScore += 15;
				_coll.erase(index_coll);
				collAvailable[index_coll] = false;
			}
		}
	}
}

void Game::init_enemy(Graphics &graphics) {
	frameCounter++;
	if (frameCounter % (int)(500 / sqrt(levelCounter)) == 0 && insert_enemy < globals::IDEAL_ENEMY_NUM * levelCounter) {
		_enemy.insert(std::pair<int, Enemy>(insert_enemy, Enemy(graphics, 1280, rand() % 650, levelCounter)));
		enemyAvailable[insert_enemy] = true;
		insert_enemy++;
	}
}

void Game::init_coll(Graphics &graphics, int x, int y) {
	_coll.insert(std::pair<int, Coll>(insert_coll, Coll(graphics, x, y)));
	collAvailable[insert_coll] = true;
	insert_coll++;
}
