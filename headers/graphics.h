#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();

	SDL_Surface* loadImage(const std::string &filePath);

	// draw a texture to a certain part of the screen
	// source = sprite  sourceRect = certain part of sprite  desRect = certain part of screen
	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle); 
	
	// render everything (in the renderer) to the screen	
	void flip(); 

	// refresh renderer
	void clear(); 
	
	SDL_Renderer* getRenderer() const;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface* > _spriteSheet;
};

#endif
