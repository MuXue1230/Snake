#pragma once
#include "sdl_include.h"
#include "GObject.h"
#include "GMOSnake.h"
#include "GOFood.h"
#include "VertexArray.h"
#include "Shader.h"

#include "GBSnakeCheckDeath.h"
#include "GBSnakeCheckFood.h"
#include "GBSnakeMoveBasicExample.h"
#include "GBSnakeMoveUserControl.h"


class Game
{
public:
	Game();

	/*
	Prepare for the initialization of the game by including:
	- Initialize the video component
	- Create window and renderer
	- Update Objects in the list
	- Pre-initializing all Objects in the list.
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

    bool GLPreInitialize();
    bool GLInitialize();
    void GLRunLoop();
    void GLShutDown();
private:
	void ProcessesInput();
	void UpdateGame();
	void GenerateOutput();

    void GLProcessesInput();
    void GLUpdateGame();
    void GLGenerateOutput();

    // SDL
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

    // OpenGL
    SDL_GLContext mContext;
    VertexArray* mObjectVerts;
    Shader* mActorShader;

	bool mIsRunning;

    const int gridWidth = 768;
    const int gridHeight = 432;
    bool occupied[768][432];

	GMOSnake test_snake_ai;
    std::vector<GOFood> foods;
};

