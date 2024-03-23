#include "Game.h"

Game::Game()
	:mIsRunning(true)
{}

bool Game::PreInitialize()
{
	// 
	SDL_Log("Pre-initialize Game...");
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
	SDL_SetRenderDrawColor(this->mRenderer, 255, 255, 255, 255);
	SDL_Log("> Cleaning Renderer...");
	SDL_RenderClear(this->mRenderer);
	SDL_Log("> Drawing Renderer...");
	SDL_RenderPresent(this->mRenderer);

	SDL_Log("Updating Objects List...");
	SDL_Log("> Creating Object <\"Test 1\">...");
	//std::shared_ptr<GObject> obj_1 = std::make_shared<GObject>(GObject("Test 1"));
	//obj_1->AddBehaviors(*new GBehavior<GObject>("Test 1-1"));
	//obj_1->AddBehaviors(*new GBehavior<GObject>("Test 1-2"));
	//this->mObjects.push_back(obj_1);

	SDL_Log("Pre-initialize Objects...");
	for (auto& item : this->mObjects) {
		SDL_Log("> Pre-initialize Object <%s>...", item->GetName().c_str());
		item->PreInitialize(this->mRenderer);
	}
	return true;
}

bool Game::Initialize()
{
	SDL_Log("Initialize Game...");
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
	SDL_Log("Initialize Objects...");
	for (auto& item : this->mObjects) {
		SDL_Log("> Initialize Object <%s>...", item->GetName().c_str());
		item->InitializeBehaviors();
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
		for (auto& item : this->mObjects) {
			item->HandleBehaviorsEvent(event);
		}
	}
}

void Game::UpdateGame()
{
	for (auto& item : this->mObjects) {
		item->UpdateBehaviors();
	}
}

void Game::GenerateOutput()
{
	SDL_RenderClear(this->mRenderer);
	SDL_RenderPresent(this->mRenderer);
	for (auto& item : this->mObjects) {
		item->UpdateRenderer();
	}
}
