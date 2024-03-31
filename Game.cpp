#include "Game.h"

Game::Game()
	:mIsRunning(true)
{}

bool Game::PreInitialize()
{
	SDL_Log("Pre-initializing Game...");
	SDL_Log("> Initializing SDL...");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, SDL_GetError());
		return false;
	}
	SDL_Log("> Creating Window...");
	SDL_Log("> > Window: \"Snake\", SDL_WINDOWPOS_CENTERED, 3840x2160, SDL_WINDOW_FULLSCREEN");
	this->mWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 3840, 2160, SDL_WINDOW_FULLSCREEN);
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
    test_snake_ai.AddBehaviors(std::make_shared<GBSnakeMoveBasicExample<GMOSnake>>(GBSnakeMoveBasicExample<GMOSnake>("SideMove")));
    test_snake_ai.AddBehaviors(std::make_shared<GBSnakeMoveUserControl<GMOSnake>>(GBSnakeMoveUserControl<GMOSnake>("TestMove")));
    test_snake_ai.AddBehaviors(std::make_shared<GBSnakeCheckDeath<GMOSnake>>(GBSnakeCheckDeath<GMOSnake>("BasicCheck")));
    test_snake_ai.AddBehaviors(std::make_shared<GBSnakeCheckFood<GMOSnake>>(GBSnakeCheckFood<GMOSnake>("FoodCheck", &this->foods, occupied)));

    SDL_Log("> Creating Object List <Food>...");
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < 768; ++i) {
        for (int j = 0; j < 432; ++j) {
            occupied[i][j] = false;
        }
    }
    for (int i = 0; i < 1000; ++i) {
        int x, y;
        do {
            x = (rand() % gridWidth) * 5;
            y = (rand() % gridHeight) * 5;
        } while (occupied[x / 5][y / 5]);
        occupied[x / 5][y / 5] = true;
        this->foods.push_back(GOFood(x, y));
    }

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
            x = (rand() % gridWidth) * 5;
            y = (rand() % gridHeight) * 5;
        } while (occupied[x / 5][y / 5]);
        this->foods.push_back(GOFood(x, y));
    }

	SDL_Log("Pre-initializing Objects...");
    SDL_Log("> Pre-initializing Object List Foods...");
    for (auto& food : this->foods) {
        food.PreInitialize(this->mRenderer);
    }
    SDL_Log("> Pre-initializing Object <%s>...", test_snake_ai.GetName().c_str());
    test_snake_ai.PreInitialize(this->mRenderer);
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
    SDL_Log("> Initializing Object List Food...");
    for (auto& food : this->foods) {
        food.InitializeBehaviors();
    }
    SDL_Log("> Initializing Object <%s>...", test_snake_ai.GetName().c_str());
    test_snake_ai.InitializeBehaviors();
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

bool Game::GLPreInitialize()
{
    SDL_Log("[With OpenGL]Pre-initializing Game...");
    SDL_Log("[With OpenGL]> Initializing SDL...");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, SDL_GetError());
        return false;
    }
    SDL_Log("[With OpenGL]> Setting up OpenGL");
    SDL_Log("[With OpenGL]> > Setting up PROFILE MASK: CORE");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_Log("[With OpenGL]> > Setting up Version: 4.6");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_Log("[With OpenGL]> > Setting up Color Depth: 8, 8, 8, 8");
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_Log("[With OpenGL]> > Setting up DOUBLEBUFFER: YES");
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Log("[With OpenGL]> > Setting up ACCELERATED VISUAL: YES");
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_Log("[With OpenGL]> Creating Window...");
    SDL_Log("[With OpenGL]> > Window: \"Snake\", SDL_WINDOWPOS_CENTERED, 3840x2160, SDL_WINDOW_FULLSCREEN");
    this->mWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 3840, 2160, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
    if (!this->mWindow) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, SDL_GetError());
        return false;
    }
    SDL_Log("[With OpenGL]> Creating GLContext...");
    mContext = SDL_GL_CreateContext(mWindow);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Error when initializing glew.");
    }
    glGetError();

    SDL_Log("[With OpenGL]Pre-drawing Screen...");
    SDL_Log("[With OpenGL]> Setting Up Context...");
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    SDL_Log("[With OpenGL]> Cleaning Context...");
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_Log("[With OpenGL]> Drawing Context...");
    SDL_GL_SwapWindow(mWindow);

    SDL_Log("[With OpenGL]Updating Objects List...");
    SDL_Log("[With OpenGL]> Creating Object <Snake<AI_Test1>>...");
    test_snake_ai = GMOSnake("AI_Test1");
    test_snake_ai.AddBehaviors(std::make_shared<GBSnakeMoveBasicExample<GMOSnake>>(GBSnakeMoveBasicExample<GMOSnake>("SideMove")));
    test_snake_ai.AddBehaviors(std::make_shared<GBSnakeMoveUserControl<GMOSnake>>(GBSnakeMoveUserControl<GMOSnake>("TestMove")));
    test_snake_ai.AddBehaviors(std::make_shared<GBSnakeCheckDeath<GMOSnake>>(GBSnakeCheckDeath<GMOSnake>("BasicCheck")));
    test_snake_ai.AddBehaviors(std::make_shared<GBSnakeCheckFood<GMOSnake>>(GBSnakeCheckFood<GMOSnake>("FoodCheck", &this->foods, occupied)));

    SDL_Log("[With OpenGL]> Creating Object List <Food>...");
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < 768; ++i) {
        for (int j = 0; j < 432; ++j) {
            occupied[i][j] = false;
        }
    }
    for (int i = 0; i < 1000; ++i) {
        int x, y;
        do {
            x = (rand() % gridWidth) * 5;
            y = (rand() % gridHeight) * 5;
        } while (occupied[x / 5][y / 5]);
        occupied[x / 5][y / 5] = true;
        this->foods.push_back(GOFood(x, y));
    }

    SDL_Log("[With OpenGL]Pre-initializing Objects...");
    SDL_Log("[With OpenGL]> Pre-initializing Object List Foods...");
    for (auto& food : this->foods) {
        food.GLPreInitialize(this->mRenderer);
    }
    SDL_Log("[With OpenGL]> Pre-initializing Object <%s>...", test_snake_ai.GetName().c_str());
    test_snake_ai.GLPreInitialize(this->mRenderer);
    return true;
}

bool Game::GLInitialize()
{
    SDL_Log("[With OpenGL]Initializing Game...");
    SDL_Log("[With OpenGL]Initializing Shaders...");
    this->mActorShader = new Shader();
    SDL_Log("[With OpenGL]Initializing Objects...");
    SDL_Log("[With OpenGL]> Initializing Object List Food...");
    for (auto& food : this->foods) {
        food.GLInitializeBehaviors();
    }
    SDL_Log("[With OpenGL]> Initializing Object <%s>...", test_snake_ai.GetName().c_str());
    test_snake_ai.GLInitializeBehaviors();
    SDL_Log("[With OpenGL]Loading Shaders");
    if (!this->mActorShader->Load("BasicVertex.glsl", "BasicPixel.glsl")) {
        return false;
    }
    this->mActorShader->SetActive();
    // test
    float vertices[] = {
        -0.5f,  0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f,
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 1, 0
    };
    mObjectVerts = new VertexArray(vertices, 4, indices, 6);
    return true;
}

void Game::GLRunLoop()
{
    while (this->mIsRunning) {
        this->GLProcessesInput();
        this->GLUpdateGame();
        this->GLGenerateOutput();
    }
}

void Game::GLShutDown()
{
    SDL_Log("[With OpenGL]Shutting Down Game...");
    SDL_Log("[With OpenGL]> Doing Destruction of Context...");
    SDL_GL_DeleteContext(this->mContext);
    SDL_Log("[With OpenGL]> Doing Destruction of Window...");
    SDL_DestroyWindow(this->mWindow);
    SDL_Log("[With OpenGL]> Closing SDL...");
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
    for (auto& food : this->foods) {
        food.UpdateRenderer();
    }
    test_snake_ai.UpdateRenderer();
	SDL_RenderPresent(this->mRenderer);
}

void Game::GLProcessesInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            this->mIsRunning = false;
            break;
        }
        test_snake_ai.GLHandleBehaviorsEvent(event);
    }
}

void Game::GLUpdateGame()
{
    test_snake_ai.GLUpdateBehaviors();
}

void Game::GLGenerateOutput()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto& food : this->foods) {
        food.GLUpdateRenderer();
    }
    test_snake_ai.GLUpdateRenderer();
    SDL_GL_SwapWindow(mWindow);
}
