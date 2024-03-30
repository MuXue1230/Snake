#include "sdl_include.h"
#include "Game.h"

enum GameEngin {
    SDL=0,
    OpenGL
};

int main(int args, char** argv)
{
    Game* game = new Game();

    GameEngin engin = OpenGL;

    switch (engin)
    {
    case SDL:
        if (game->PreInitialize() && game->Initialize()) {
            game->RunLoop();
        }
        game->ShutDown();
        break;
    case OpenGL:
        if (game->GLPreInitialize() && game->GLInitialize()) {
            game->GLRunLoop();
        }
        game->GLShutDown();
        break;
    }
    return 0;
}
