#pragma once
#include "sdl_include.h"
#include "GObject.h"
#include "GMOSnake.h"

class Game
{
public:
	Game();

	/*
	Prepare for the initialization of the game by including:
	- Initialize the video component
	- Create window and renderer
	- Update Objects in the list
	- Pre-initialize all Objects in the list.
	*/
	bool PreInitialize();
	/*
	Initialize the game, including:
	- Initialize the image component
	- Initialize the mixer component
	- Initialize the font component
	- Start the mixer
	- Set up the mixer volume
	- Initialize all objects in the list
	*/
	bool Initialize();
	void RunLoop();
	void ShutDown();
private:
	void ProcessesInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	bool mIsRunning;

	GMOSnake text_snake_ai;
};

