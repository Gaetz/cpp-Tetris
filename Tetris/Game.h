#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#if defined(_WIN32) || defined(_WIN64)
#include <gl/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

#include "Shader.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool isFullscreen);
	void load();
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

private:
	bool isRunning;
	SDL_Window* window;
	SDL_GLContext context;

	Shader shader;
	float vertices [12] = { 0.0f, 0.0f,   0.5f, 0.0f,   0.0f, 0.5f,          // Triangle 1
		-0.8f, -0.8f,   -0.3f, -0.8f,   -0.8f, -0.3f };   // Triangle 2
};


#endif // !GAME_H
