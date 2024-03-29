#include "Game.h"

Game::Game()
	:mIsRunning(true)
{}

bool Game::PreInitialize()
{
	// 
	SDL_Log("Pre-initializing Game...");
	SDL_Log("> Initializing SDL...");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, SDL_GetError());
		return false;
	}
	SDL_Log("> Creating Window...");
	SDL_Log("> > Window: \"Snake\", SDL_WINDOWPOS_CENTERED, 1080x720, No Flags");
	this->mWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, 0);
	if (!this->mWindow) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, SDL_GetError());
		return false;
	}
	SDL_Log("> Creating Renderer...");
	this->mRenderer = SDL_CreateRenderer(this->mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!this->mRenderer) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,  SDL_GetError());
		return false;
	}
	SDL_Log("Pre-drawing Screen...");
	SDL_Log("> Setting Up Renderer...");
	SDL_SetRenderDrawColor(this->mRenderer, 0, 0, 0, 255);
	SDL_Log("> Cleaning Renderer...");
	SDL_RenderClear(this->mRenderer);
	SDL_Log("> Drawing Renderer...");
	SDL_RenderPresent(this->mRenderer);

	SDL_Log("Updating Objects List...");
	SDL_Log("> Creating Object <Snake<AI_Test1>>...");
	test_snake_ai = GMOSnake("AI_Test1");
    test_snake_ai.AddBehaviors(std::make_shared<GBSnakeMoveBasicExample<GMOSnake>>(GBSnakeMoveBasicExample<GMOSnake>("BasicMove")));
	test_snake_ai.AddBehaviors(std::make_shared<GBSnakeMoveUserControl<GMOSnake>>(GBSnakeMoveUserControl<GMOSnake>("TextMove")));

    SDL_Log("> Creating Object List <Food>...");
    srand(static_cast<unsigned int>(time(nullptr)));
    bool occupied[216][144];
    for (int i = 0; i < 216; ++i) {
        for (int j = 0; j < 144; ++j) {
            occupied[i][j] = false;
        }
    }
    const int gridWidth = 216;
    const int gridHeight = 144;
    for (int i = 0; i < 100; ++i) {
        int x, y;
        do {
            x = (rand() % gridWidth) * 5;   // Random x coordinate (multiple of 5)
            y = (rand() % gridHeight) * 5;  // Random y coordinate (multiple of 5)
        } while (occupied[x / 5][y / 5]);
        this->foods.push_back(GOFood(x, y));     // Add food to the vector
    }

	SDL_Log("Pre-initializing Objects...");
	SDL_Log("> Pre-initializing Object <%s>...", test_snake_ai.GetName().c_str());
	test_snake_ai.PreInitialize(this->mRenderer);
    for (auto& food : this->foods) {
        SDL_Log("> Pre-initializing Object <%s>...", food.GetName().c_str());
        food.PreInitialize(this->mRenderer);
    }
	return true;
}

bool Game::Initialize()
{
	SDL_Log("Initializing Game...");
	SDL_Log("> Initializing SDL_image...");
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, IMG_GetError());
		return false;
	}
	SDL_Log("> Initializing SDL_mixer...");
	if (!(Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG)) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, Mix_GetError());
		return false;
	}
	SDL_Log("> Initializing SDL_ttf...");
	if (TTF_Init()) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, TTF_GetError());
	}
	SDL_Log("> Starting SDL_mixer...");
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 32768) < 0) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, Mix_GetError());
		return 1;
	}
	SDL_Log("> Setting Up SDL_mixer...");
	Mix_Volume(-1, 64);
	Mix_VolumeMusic(32);
	SDL_Log("Initializing Objects...");
	SDL_Log("> Initializing Object <%s>...", test_snake_ai.GetName().c_str());
	test_snake_ai.InitializeBehaviors();
    for (auto& food : this->foods) {
        SDL_Log("> Initializing Object <%s>...", food.GetName().c_str());
        food.InitializeBehaviors();
    }
	return true;
}

void Game::RunLoop()
{
	while (this->mIsRunning) {
		this->ProcessesInput();
		this->UpdateGame();
		this->GenerateOutput();
	}
}

void Game::ShutDown()
{
	SDL_Log("Shutting Down Game...");
	SDL_Log("> Doing Destruction of Renderer...");
	SDL_DestroyRenderer(this->mRenderer);
	SDL_Log("> Doing Destruction of Window...");
	SDL_DestroyWindow(this->mWindow);
	SDL_Log("> Stopping SDL_mixer...");
	Mix_CloseAudio();
	SDL_Log("> Closing SDL_image...");
	IMG_Quit();
	SDL_Log("> Closing SDL_mixer...");
	Mix_Quit();
	SDL_Log("> Closing SDL_ttf...");
	TTF_Quit();
	SDL_Log("> Closing SDL...");
	SDL_Quit();
}

void Game::ProcessesInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			this->mIsRunning = false;
			break;
		}
		test_snake_ai.HandleBehaviorsEvent(event);
	}
}

void Game::UpdateGame()
{
	test_snake_ai.UpdateBehaviors();
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(this->mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(this->mRenderer);
	test_snake_ai.UpdateRenderer();
    for (auto& food : this->foods) {
        food.UpdateRenderer();
    }
	SDL_RenderPresent(this->mRenderer);
}
