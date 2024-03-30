#include "sdl_include.h"

#include "Game.h"

int main(int args, char** argv)
{
    Game* game = new Game();

    //if (game->PreInitialize()&&game->Initialize()) {
    //    game->RunLoop();
    //}
    //game->ShutDown();

    if (game->GLPreInitialize()&&game->GLInitialize()) {
        game->GLRunLoop();
    }
    game->GLShutDown();
    return 0;
}
