#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <SDL.h>

#include "globals.h"

class Graphics;
struct SDL_Texture;

class Level {
public:
	Level();
	Level(Graphics &graphics, const std::string &filePath, int _width, int _height);
	~Level();

	void update(int elaspedTime);
	void draw(Graphics &graphics, int x, int y);

private:
	std::string _mapName;
	Vector2 _spawnPoint;
	Vector2 _size;
	SDL_Texture* _backgroundTexture;

	void loadMap(Graphics &graphics, const std::string &filePath, int _width, int _height);
};

#endif 
