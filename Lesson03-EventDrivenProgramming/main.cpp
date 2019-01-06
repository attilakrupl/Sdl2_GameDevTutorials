#include "types/drkrWindow.h"

int main( int argc, char* argv[] )
{
    drkrWindow lWindow;
    if( !lWindow.init() )
    {
        printf( "Failed to initialize!\n" );
        return -1;
    }

    if( !lWindow.loadMedia() )
    {
        printf( "Failed to load media!\n" );
        return -1;
    }

    bool lQuitGame = false;
    SDL_Event lEvent;

    while( !lQuitGame )
    {
        while( SDL_PollEvent( &lEvent ) != 0 )
        {
            if( lEvent.type == SDL_QUIT )
            {
                lQuitGame = true;
            }
        }
    }
    lWindow.close();
    return 0;
}